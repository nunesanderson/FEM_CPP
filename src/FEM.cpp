#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;
using std::string;

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Matrix.h"
#include "Matrix.cpp"
#include "../include/FEM.h"
#include "../include/Material_constants.h"
#include "../include/ShapeFunctions.h"
#include "../include/PostProcessing.h"
#include "../include/fileNames.h"

int FEM::getPositionInVector(int i, vector<int> this_vector)
{
    Messages msg;
    auto it = std::find(this_vector.begin(), this_vector.end(), i);
    if (it == this_vector.end())
    {
        msg.logMessage("ID " + to_string(i) + " not found in vector.");
    }
    else
    {
        int index = std::distance(this_vector.begin(), it);
        return index;
    }
}

void FEM::run()
{

    // Reads the mesh
    Mesh mesh(this->mesh_path + "/" + this->mesh_file_name);

    // Memory allocation for both sides of the equation
    Matrix<double> left_side(mesh.numNodes, mesh.numNodes);
    Matrix<double> right_side(1, mesh.numNodes);

    //Sets the variables to be able to run 1,2 and 3-D cases
    int numElemIntegrate;
    int elemCounterGLobal;
    int numElemBC;
    vector<vector<int>> ElemNodesIntegrate;
    vector<vector<int>> ElemNodesBC;
    if (this->dimensions == 1)
    {
        numElemBC = mesh.numElements0D;
        numElemIntegrate = mesh.numElements1D;
        ElemNodesIntegrate = mesh.elemNodes1D;
        ElemNodesBC = mesh.elemNodes0D;
        elemCounterGLobal = mesh.numElements0D;
    }
    else if (this->dimensions == 2)
    {
        numElemBC = mesh.numElements1D;
        ElemNodesBC = mesh.elemNodes1D;
        numElemIntegrate = mesh.numElements2D;
        ElemNodesIntegrate = mesh.elemNodes2D;
        elemCounterGLobal = mesh.numElements1D;
    }

    //Array to save the material properties
    Matrix<double> materialPropertyPerElem(1, numElemIntegrate);

    // Material constants
    Material_constants material;

    //Shape functions
    NodalShapeFunctions shapeFuntions;

    // Material property
    double matVacuumProperty = 1;
    if (this->formulationName == "magnetostatics")
    {
        matVacuumProperty = 1 / material.mu0;
    }
    else if (this->formulationName == "electrostatics")
    {
        matVacuumProperty = material.eps0;
    }
    else
    {
        throw std::invalid_argument("Formulation not found.");
    }

    // Tags to plot different colors
    Matrix<int> physTagsPlot(1, numElemIntegrate);

    Messages msg;

    // ====================
    // Integration procedure
    //  ====================
    time_t start, end;
    time(&start);
    msg.logMessage("Integration process");

#pragma omp parallel for default(none) shared(left_side, elemCounterGLobal, right_side, shapeFuntions, material, mesh, materialPropertyPerElem, numElemIntegrate, elemCounterGLobal, numElemBC, ElemNodesIntegrate, ElemNodesBC)
    for (size_t elemCounter = 0; elemCounter < numElemIntegrate; elemCounter++)
    {

        int thisPhysID = mesh.physicalTags.mat[0][elemCounterGLobal];

        physTagsPlot.mat[0][elemCounter] = thisPhysID;
        int posIDlist = getPositionInVector(thisPhysID, this->setup_phys_region_ID);

        // Material property
        double matProperty = matVacuumProperty * this->setup_phys_region_relative_property[posIDlist];
        materialPropertyPerElem.mat[0][elemCounter] = matProperty;

        // Excitation
        double excitation = this->setup_phys_region_excitation[posIDlist];

        //Nodes per element
        int nodesPerElement = ElemNodesIntegrate[elemCounter].size();

        // TODO: Check dimensions
        int dimensions = this->dimensions;

        //Element type
        int thisElemtype = mesh.elemTypes.mat[0][elemCounterGLobal];

        // Matrix with nodes coordinates
        Matrix<double> coordJac(nodesPerElement, dimensions);
        for (size_t i = 0; i < nodesPerElement; i++)
        {
            int globalNodeID = ElemNodesIntegrate[elemCounter][i] - 1;

            for (size_t j = 0; j < dimensions; j++)
            {
                coordJac.mat[i][j] = mesh.nodesCoordinates.mat[globalNodeID][j];
            }
        }
        shapeFuntions.GetGradNodalShapeFunction(thisElemtype);

        // Jacobian calculattion
        Matrix<double> Jac = shapeFuntions.gradShapeFunction * coordJac;
        Jac.calcDet();
        double detJac = Jac.detVal;
        Matrix<double> invJac = Jac.Inverse();
        Matrix<double> invJacGradN = invJac * shapeFuntions.gradShapeFunction;
        Matrix<double> invJacGradNTrans = invJacGradN.Transpose();

        Matrix<double> local_left_side(nodesPerElement, nodesPerElement);
        Matrix<double> local_right_side(1, nodesPerElement);
        local_left_side.SetValue(0.0);
        local_right_side.SetValue(0.0);

        // Integral points
        GaussLegendrePoints gaussPoints(thisElemtype);

        //Left side integration
        // [InvJacobian*gradN].T*[InvJacobian*gradN]*det(Jacobian)*Integdudv*prop.material
        for (size_t i = 0; i < gaussPoints.pointsCoordinates.rows; i++)
        {
            local_left_side = local_left_side + invJacGradNTrans * invJacGradN * detJac * gaussPoints.weights.mat[0][i] * matProperty;
        }

        //Left side assembling
        for (size_t i = 0; i < nodesPerElement; i++)
        {
            for (size_t j = 0; j < nodesPerElement; j++)
            {
                int this_row = ElemNodesIntegrate[elemCounter][i] - 1;
                int this_col = ElemNodesIntegrate[elemCounter][j] - 1;
                left_side.mat[this_row][this_col] = left_side.mat[this_row][this_col] + local_left_side.mat[i][j];
            }
        }

        //Right side integration
        // [N]*Js*Det[Jacbian]*Integdudv
        for (size_t i = 0; i < gaussPoints.pointsCoordinates.rows; i++)
        {
            shapeFuntions.GetNodalShapeFunctions(thisElemtype, gaussPoints.pointsCoordinates.mat[i][0], gaussPoints.pointsCoordinates.mat[i][1], gaussPoints.pointsCoordinates.mat[i][2]);

            local_right_side = local_right_side + shapeFuntions.shapeFunction * detJac * gaussPoints.weights.mat[0][i] * excitation;
        }

        for (size_t i = 0; i < nodesPerElement; i++)
        {
            int this_row = ElemNodesIntegrate[elemCounter][i] - 1;
            right_side.mat[0][this_row] = right_side.mat[0][this_row] + local_right_side.mat[0][i];
        }

        elemCounterGLobal++;
    }

    time(&end);
    double dif = difftime(end, start);
    msg.logMessage("Elasped time is seconds:" + to_string(dif));
    msg.logMessage("Integration process: Done");

    // ====================
    // Boundary conditions
    //  ====================
    for (size_t i = 0; i < numElemBC; i++)
    {

        // Get the physical ID of each BC element
        int this_phys_ID = mesh.physicalTags.mat[0][i];

        // Checks if a there is a BC applied to this element
        auto it = std::find(this->setup_phys_BC_ID.begin(), this->setup_phys_BC_ID.end(), this_phys_ID);

        // If there is
        if (it != this->setup_phys_BC_ID.end())
        {
            // Gets the BC value
            int index = std::distance(this->setup_phys_BC_ID.begin(), it);
            double BCVal = this->setup_phys_BC_val[index];

            //Apply over the nodes
            for (size_t j = 0; j < ElemNodesBC[i].size(); j++)
            {
                int this_node = ElemNodesBC[i][j] - 1;
                left_side.SetLineValue(this_node, 0.0);
                left_side.mat[this_node][this_node] = 1.0;
                right_side.mat[0][this_node] = BCVal;
            }
        }
    }
    // ====================
    // Linear system
    //  ====================
    left_side.SolveLinearSystem(left_side, right_side);

    // ====================
    // Write solution files
    //  ====================
    right_side.writeToFile(this->mesh_path + directoryNameResults, fileNamesolutionResults);
    right_side.write2DVectorToFile(mesh.elemNodes2D, this->mesh_path + directoryNameResults, fileNameTriangulationFile);
    right_side.write2DVectorToFile(mesh.elemNodes1D, this->mesh_path + directoryNameResults, fileNameElemNodes1D);
    mesh.nodesCoordinates.writeToFile(this->mesh_path + directoryNameResults, fileNameNodesCoordinates);
    physTagsPlot.writeToFile(this->mesh_path + directoryNameResults, fileName2DPhysTags);
    materialPropertyPerElem.writeToFile(this->mesh_path + directoryNameResults, fileNameMaterialProperty);
    PostProcessing postProcess(this->mesh_path, mesh_file_name, right_side);
    postProcess.getGradLine(0.085, 0.085, 0, 0.1, 100);
    postProcess.getGradDomain();
}
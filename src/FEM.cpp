#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

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
    GetMesh mesh(this->mesh_path);

    // Memory allocation for both sides of the equation
    Matrix<double> left_side(mesh.numNodes, mesh.numNodes);
    Matrix<double> right_side(1, mesh.numNodes);

    // Material constants
    Material_constants material;

    //Shape functions
    NodalShapeFunctions shapeFuntions;
    // left_side.write2DVectorToFile(mesh.elemNodes,"/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/examples/01_Simple_mesh","triangulation");
    


    int elemCounterGLobal = mesh.numElements1D;
    for (size_t elemCounter = 0; elemCounter < mesh.numElements2D; elemCounter++)
    {
        int thisPhysID = mesh.physicalTags.mat[0][elemCounterGLobal];
        int posIDlist = getPositionInVector(thisPhysID, this->setup_phys_region_ID);

        // Material property
        double matProperty = 1 / (material.mu0 * this->setup_phys_region_perm_rel[posIDlist]);
        cout<<matProperty<<endl;

        // Excitation
        double excitation = this->setup_phys_region_excitation[posIDlist];

        //Nodes per element
        int nodesPerElement = mesh.elemNodes[elemCounterGLobal].size();

        // TODO: Check dimensions
        int dimensions = 2;

        //Element type
        int thisElemtype = mesh.elemTypes.mat[0][elemCounterGLobal];

        // Matrix with nodes coordinates
        Matrix<double> coordJac(nodesPerElement, dimensions);
        for (size_t i = 0; i < nodesPerElement; i++)
        {
            int globalNodeID = mesh.elemNodes[elemCounterGLobal][i] - 1;
            for (size_t j = 0; j < dimensions; j++)
            {
                coordJac.mat[i][j] = mesh.nodesCoordinates.mat[globalNodeID][j];
            }
        }

        //GradN Matrix
        shapeFuntions.GetGradNodalShapeFunction(thisElemtype);

        // Jacobian calculattion
        Matrix<double> Jac = shapeFuntions.gradShapeFunction * coordJac;
        Jac.calcDet();
        double detJac = Jac.detVal;

        Matrix<double> invJacGradN = Jac.Inverse() * shapeFuntions.gradShapeFunction;
        Matrix<double> invJacGradNTrans = invJacGradN.Transpose();

        Matrix<double> local_left_side(nodesPerElement, nodesPerElement);
        Matrix<double> local_right_side(1, nodesPerElement);
        local_left_side.SetValue(0.0);
        local_right_side.SetValue(0.0);

        // Integral points
        GaussLegendrePoints gaussPoints(thisElemtype);

        //Left side integration
        for (size_t i = 0; i < gaussPoints.pointsCoordinates.rows; i++)
        {
            local_left_side = local_left_side + invJacGradNTrans * invJacGradN * detJac * gaussPoints.weights.mat[0][i] * matProperty;
        }

        //Left side assembling
        for (size_t i = 0; i < nodesPerElement; i++)
        {
            for (size_t j = 0; j < nodesPerElement; j++)
            {
                int this_row = mesh.elemNodes[elemCounterGLobal][i] - 1;
                int this_col = mesh.elemNodes[elemCounterGLobal][j] - 1;

                left_side.mat[this_row][this_col] = left_side.mat[this_row][this_col] + local_left_side.mat[i][j];
            }
        }

        //Right side integration
        for (size_t i = 0; i < gaussPoints.pointsCoordinates.rows; i++)
        {
            shapeFuntions.GetNodalShapeFunctions(thisElemtype, gaussPoints.pointsCoordinates.mat[i][0], gaussPoints.pointsCoordinates.mat[i][1], gaussPoints.pointsCoordinates.mat[i][2]);

            local_right_side = local_right_side + shapeFuntions.shapeFunction * detJac * gaussPoints.weights.mat[0][i] * excitation;
        }

        for (size_t i = 0; i < nodesPerElement; i++)
        {
             int this_row = mesh.elemNodes[elemCounterGLobal][i] - 1;
             right_side.mat[0][this_row]=right_side.mat[0][this_row]+local_right_side.mat[0][i];
        }
    


        elemCounterGLobal++;
    }

    //Boundary conditions
    for (size_t i = 0; i < mesh.numElements1D; i++)
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
            for (size_t j = 0; j < mesh.elemNodes[i].size(); j++)
            {
                int this_node=mesh.elemNodes[i][j]-1;
                left_side.SetLineValue(this_node,0.0);
                left_side.mat[this_node][this_node]=1.0;
                right_side.mat[0][this_node]=BCVal;
            }
        }
     }

    left_side.SolveLinearSystem(left_side,right_side);
    right_side.writeToFile("/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/examples/03_simple_mesh","new_results");



}

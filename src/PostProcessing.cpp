#include <iostream>
#include <string>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Gmsh_interface.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
#include "../include/PostProcessing.h"
#include "../include/ShapeFunctions.h"
#include "../include/fileNames.h"

PostProcessing::PostProcessing(string filesPath, string meshFileName, Matrix<double> &thisSolution)
{
    Mesh mesh(filesPath + "/" + meshFileName);
    this->meshData = mesh;
    this->solution = thisSolution;
    this->filePath = filesPath;
}

void PostProcessing::getGradLine(double x_start, double x_end, double y_start, double y_end, int numberPoints)
{

    Matrix<double> pointsCoordinates(numberPoints,2 );
    Matrix<double> ans(numberPoints,2) ;
    double dx = (x_end - x_start) / (numberPoints + 1);
    double dy = (y_end - y_start) / (numberPoints + 1);
    double x = x_start;
    double y = y_start;
    for (size_t i = 0; i < numberPoints; i++)
    {
        pointsCoordinates.mat[i][0] = x;
        pointsCoordinates.mat[i][1] = y;
        cout<<"x="<<x<<"y="<<y<<endl;
        Matrix<double> thisPointAns = this->getGradPoint(x, y);
        ans.mat[i][0] = thisPointAns.mat[0][0];
        ans.mat[i][1] = thisPointAns.mat[0][1];

        x = x + dx;
        y = y + dy;
    }

    pointsCoordinates.writeToFile(this->filePath+directoryNameResults, fileNameLineCoordinates);
    ans.writeToFile(this->filePath+directoryNameResults, fileNameLineResults);
}

Matrix<double> PostProcessing::getGradPoint(double x, double y)
{
    // TODO: Check dimensions
    int dimensions = 2;

    // Matrix grad Pot to return
    Matrix<double> gradPot(1, dimensions);

    //Shape functions
    NodalShapeFunctions shapeFuntions;

    int elemCounterGLobal = this->meshData.numElements1D;
    for (size_t elemCounter = 0; elemCounter < this->meshData.numElements2D; elemCounter++)
    {
        //Nodes per element
        int nodesPerElement = this->meshData.elemNodes2D[elemCounter].size();

        //Element type
        int thisElemtype = this->meshData.elemTypes.mat[0][elemCounterGLobal];

        //Simmetry factor
        double symFactor = 1.0;
        if (true)
        {
            symFactor = 0;
            for (size_t i = 0; i < nodesPerElement; i++)
            {
                int globalNodeID = this->meshData.elemNodes2D[elemCounter][i] - 1;
                symFactor = +this->meshData.nodesCoordinates.mat[globalNodeID][0];
            }
            symFactor = symFactor / nodesPerElement;
            symFactor = 1 / symFactor;
        }

        // Matrix with nodes coordinates
        Matrix<double> coordJac(nodesPerElement, dimensions);
        for (size_t i = 0; i < nodesPerElement; i++)
        {
            int elemCounterGLobal = this->meshData.numElements1D;
            int globalNodeID = this->meshData.elemNodes2D[elemCounter][i] - 1;

            for (size_t j = 0; j < dimensions; j++)
            {
                coordJac.mat[i][j] = this->meshData.nodesCoordinates.mat[globalNodeID][j];
            }
        }
        shapeFuntions.GetGradNodalShapeFunction(thisElemtype);

        // Jacobian calculattion
        Matrix<double> Jac = shapeFuntions.gradShapeFunction * coordJac;
        Matrix<double> JacTrans = Jac.Transpose();

        Jac.calcDet();
        double detJac = Jac.detVal;
        Matrix<double> invJac = JacTrans.Inverse();
        Matrix<double> ptXY(2, 1);
        ptXY.mat[0][0] = x;
        ptXY.mat[1][0] = y;

        Matrix<double> ptCoord(2, 1);
        ptCoord.mat[0][0] = coordJac.mat[0][0];
        ptCoord.mat[1][0] = coordJac.mat[0][1];

        Matrix<double> ptUV = invJac * (ptXY - ptCoord);

        shapeFuntions.GetNodalShapeFunctions(thisElemtype, ptUV.mat[0][0], ptUV.mat[1][0], 0);

        bool thisElement = true;
        for (size_t i = 0; i < shapeFuntions.shapeFunction.cols; i++)
        {
            if (shapeFuntions.shapeFunction.mat[0][i] < 0 || shapeFuntions.shapeFunction.mat[0][i] > 1)
            {
                thisElement = false;
            }
        }

        if (thisElement)
        {

            // Potentials at the nodes of the elements
            Matrix<double> potentials(nodesPerElement, 1);
            for (size_t i = 0; i < nodesPerElement; i++)
            {
                int nodeID = this->meshData.elemNodes2D[elemCounter][i] - 1;
                potentials.mat[i][0] = this->solution.mat[0][nodeID];
            }
            potentials.print_matrix();
            cout << elemCounterGLobal << endl;
            Matrix<double> invJac2 = Jac.Inverse();
            gradPot = invJac2 * shapeFuntions.gradShapeFunction * potentials;
            gradPot.print_matrix();
        }

        elemCounterGLobal++;
    }

    return gradPot;
}

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <limits>
#include <vector>
#include <numeric>
using namespace std;

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/ShapeFunctions.h"
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
Messages msg;


void NodalShapeFunctions::GetGradNodalShapeFunction(int ElemType, double u, double v, double p)
{

    switch (ElemType)
    {
    case 1: //First order line
        gradNodalLineFirstOrder();
        break;

    case 2: //First order triangle
        gradNodalTriangleFirstOrder();
        break;

    case 4: //First order tetrahedral
        gradNodalTetrahedralFirstOrder();
        break;

    case 5: //First order hexahedral
        gradNodalHexahedralFirstOrder(u, v, p);
        break;

    case 8: //Second order line
        gradNodalLineSecondOrder(u);
        break;

    case 9: //Second order triangle
        gradNodalTriangleSecondOrder(u, v);
        break;

    case 11: //Second order tetrahedral
        gradNodalTetrahedralSecondOrder(u, v, p);
        break;
    default:
        msg.NotImplementedElement(ElemType, "GetGradNodalShapeFunction");
    }
}

void NodalShapeFunctions::gradNodalLineFirstOrder()
{
    Matrix<double> ans(3, 2);

    ans.mat[0][0] = -0.5;
    ans.mat[0][1] = 0.5;
    ans.mat[1][0] = 0.0;
    ans.mat[1][1] = 0.0;
    ans.mat[2][0] = 0.0;
    ans.mat[2][1] = 0.0;

    this->gradShapeFunction = ans;
}

void NodalShapeFunctions::gradNodalLineSecondOrder(double u)
{
    Matrix<double> ans(3, 3);
    ans.mat[0][0] = (-1.0 + 2.0 * u) / 2.0;
    ans.mat[0][1] = (1.0 + 2 * u) / 2.0;
    ans.mat[0][2] = -2 * u;
    ans.mat[1][0] = 0.0;
    ans.mat[1][1] = 0.0;
    ans.mat[1][2] = 0.0;
    ans.mat[2][0] = 0.0;
    ans.mat[2][1] = 0.0;
    ans.mat[2][2] = 0.0;

    this->gradShapeFunction = ans;
}
void NodalShapeFunctions::gradNodalTriangleFirstOrder()
{
    /*ref:
	Ida&Bastos, pg 315, table 8.4*/

    Matrix<double> ans(2, 3);
    ans.mat[0][0] = -1.0;
    ans.mat[0][1] = 1.0;
    ans.mat[0][2] = 0.0; //gradNu
    ans.mat[1][0] = -1.0;
    ans.mat[1][1] = 0.0;
    ans.mat[1][2] = 1.0; //gradNv

    this->gradShapeFunction = ans;
}
void NodalShapeFunctions::gradNodalTriangleSecondOrder(double u, double v)
{
    Matrix<double> ans(3, 6);
    double t = 1.0 - u - v;

    //gradNu
    ans.mat[0][0] = 1.0 - 4.0 * t;
    ans.mat[0][1] = 4.0 * (t - u);
    ans.mat[0][2] = -1.0 + 4.0 * u;
    ans.mat[0][3] = 4.0 * v;
    ans.mat[0][4] = 0.0;
    ans.mat[0][5] = -4.0 * v;

    //gradNv
    ans.mat[1][0] = 1.0 - 4.0 * t;
    ans.mat[1][1] = -4.0 * u;
    ans.mat[1][2] = 0.0;
    ans.mat[1][3] = 4.0 * u;
    ans.mat[1][4] = -1.0 + 4.0 * v;
    ans.mat[1][5] = 4.0 * (t - v);
    this->gradShapeFunction = ans;
}
void NodalShapeFunctions::gradNodalTetrahedralFirstOrder()
{

    /*ref:
	Ida&Bastos, pg 319, table 8.9
	First order tetrahedral element*/

    Matrix<double> ans(3, 4);
    ans.mat[0][0] = -1.0;
    ans.mat[0][1] = 1.0;
    ans.mat[0][2] = 0.0;
    ans.mat[0][3] = 0.0;
    ans.mat[1][0] = -1.0;
    ans.mat[1][1] = 0.0;
    ans.mat[1][2] = 1.0;
    ans.mat[1][3] = 0.0;
    ans.mat[2][0] = -1.0;
    ans.mat[2][1] = 0.0;
    ans.mat[2][2] = 0.0;
    ans.mat[2][3] = 1.0;

    this->gradShapeFunction = ans;
}
void NodalShapeFunctions::gradNodalTetrahedralSecondOrder(double u, double v, double p)
{
    Matrix<double> ans(3, 10);
    double t = 1.0 - u - v - p;

    //gradNu
    ans.mat[0][0] = 1.0 - 4.0 * t;
    ans.mat[0][1] = 4.0 * (t - u);
    ans.mat[0][2] = -1.0 + 4.0 * u;
    ans.mat[0][3] = 4.0 * v;
    ans.mat[0][4] = 0.0;
    ans.mat[0][5] = -4.0 * v;
    ans.mat[0][6] = -4.0 * p;
    ans.mat[0][7] = 4.0 * p;
    ans.mat[0][8] = 0.0;
    ans.mat[0][9] = 0.0;

    //gradNv
    ans.mat[1][0] = 1.0 - 4.0 * t;
    ans.mat[1][1] = -4.0 * u;
    ans.mat[1][2] = 0.0;
    ans.mat[1][3] = 4.0 * u;
    ans.mat[1][4] = -1.0 + 4.0 * v;
    ans.mat[1][5] = 4.0 * (t - v);
    ans.mat[1][6] = -4.0 * p;
    ans.mat[1][7] = 0.0;
    ans.mat[1][8] = 4.0 * p;
    ans.mat[1][9] = 0.0;

    //gradNp
    ans.mat[2][0] = 1.0 - 4.0 * t;
    ans.mat[2][1] = -4.0 * u;
    ans.mat[2][2] = 0.0;
    ans.mat[2][3] = 0.0;
    ans.mat[2][4] = 0.0;
    ans.mat[2][5] = -4.0 * v;
    ans.mat[2][6] = 4.0 * (t - p);
    ans.mat[2][7] = 4.0 * u;
    ans.mat[2][8] = 4.0 * v;
    ans.mat[2][9] = -1.0 + 4.0 * p;

    this->gradShapeFunction = ans;
}
void NodalShapeFunctions::gradNodalHexahedralFirstOrder(double u, double v, double p)
{

    /*ref:
	Ida&Bastos, pg 319, table 8.9*/

    Matrix<double> ans(3, 8);

    double a1 = 1.0 + u;
    double a2 = 1.0 - u;
    double b1 = 1.0 + v;
    double b2 = 1.0 - v;
    double c1 = 1.0 + p;
    double c2 = 1.0 - p;
    double k = 1.0 / 8.0;

    ans.mat[0][0] = -b2 * c2;
    ans.mat[0][1] = b2 * c2;
    ans.mat[0][2] = b1 * c2;
    ans.mat[0][3] = -b1 * c2;
    ans.mat[1][0] = -a2 * c2;
    ans.mat[1][1] = -a1 * c2;
    ans.mat[1][2] = a1 * c2;
    ans.mat[1][3] = a2 * c2;
    ans.mat[2][0] = -a2 * b2;
    ans.mat[2][1] = -a1 * b2;
    ans.mat[2][2] = -a1 * b1;
    ans.mat[2][3] = -a2 * b1;

    ans.mat[0][4] = -b2 * c1;
    ans.mat[0][5] = b2 * c1;
    ans.mat[0][6] = b1 * c1;
    ans.mat[0][7] = -b1 * c1;
    ans.mat[1][4] = -a2 * c1;
    ans.mat[1][5] = -a1 * c1;
    ans.mat[1][6] = a1 * c1;
    ans.mat[1][7] = a2 * c1;
    ans.mat[2][4] = a2 * b2;
    ans.mat[2][5] = a1 * b2;
    ans.mat[2][6] = a1 * b1;
    ans.mat[2][7] = a2 * b1;

    this->gradShapeFunction = ans;
}

/* ------------------------------------------------------------------------
Nodal shape functions
[N1 N2...Nn]
---------------------------------------------------------------------------*/
void NodalShapeFunctions::GetNodalShapeFunctions(int ElemType, double u, double v, double p)
{

    switch (ElemType)
    {
    case 1: //First order line
        nodalLineFirstOrder(u);
        break;

    case 2: //First order triangle
        nodalTriangleFirstOrder(u, v);
        break;

    case 4: //First order tetrahedral
        nodalTetrahedralFirstOrder(u, v, p);
        break;

    case 5: //First order hexahedral
        nodalHexahedralFirstOrder(u, v, p);
        break;

    case 8: //Second order line
        nodalLineSecondOrder(u);
        break;

    case 9: //Second order triangle
        nodalTriangleSecondOrder(u, v);
        break;

    case 11: // Second order tetrahedral
        nodalTetrahedralSecondOrder(u, v, p);
        break;

    default:
        msg.NotImplementedElement(ElemType, "GetNodalShapeFunction");
    }
}

void NodalShapeFunctions::nodalLineFirstOrder(double u)
{
    Matrix<double> ans(1, 2);
    ans.mat[0][0] = 0.5 * (1.0 - u);
    ans.mat[0][1] = 0.5 * (1.0 + u);
    shapeFunction = ans;
}

/*
Second order line
0    2    1
*----*----*
*/
void NodalShapeFunctions::nodalLineSecondOrder(double u)
{
    Matrix<double> ans(1, 3);

    ans.mat[0][0] = -u * (1.0 - u) / 2.0;
    ans.mat[0][1] = u * (1.0 + u) / 2.0;
    ans.mat[0][2] = (1.0 - u * u);
    shapeFunction = ans;
}

void NodalShapeFunctions::nodalTriangleFirstOrder(double u, double v)
{
    // Ref Ida&Bastos, pg 319, table 8.9
    Matrix<double> ans(1, 3);

    ans.mat[0][0] = 1.0 - u - v;
    ans.mat[0][1] = u;
    ans.mat[0][2] = v;

    shapeFunction = ans;
}

void NodalShapeFunctions::nodalTriangleSecondOrder(double u, double v)
{
    // Ref Ida&Bastos, pg 316, table 8.5
    Matrix<double> ans(1, 6);

    double t = 1.0 - u - v;
    ans.mat[0][0] = -t * (1.0 - 2.0 * t);
    ans.mat[0][1] = 4.0 * u * t;
    ans.mat[0][2] = -u * (1.0 - 2.0 * u);
    ans.mat[0][3] = 4.0 * u * v;
    ans.mat[0][4] = -v * (1.0 - 2.0 * v);
    ans.mat[0][5] = 4.0 * v * t;

    shapeFunction = ans;
}

void NodalShapeFunctions::nodalTetrahedralFirstOrder(double u, double v, double p)
{
    // Ref Ida&Bastos, pg 315, table 8.7
    Matrix<double> ans(1, 4);

    ans.mat[0][0] = 1.0 - u - v - p;
    ans.mat[0][1] = u;
    ans.mat[0][2] = v;
    ans.mat[0][3] = p;

    shapeFunction = ans;
}
void NodalShapeFunctions::nodalTetrahedralSecondOrder(double u, double v, double p)
{
    Matrix<double> ans(1, 10);
    double t = 1.0 - u - v - p;

    ans.mat[0][0] = -t * (1.0 - 2.0 * t);
    ans.mat[0][1] = 4.0 * u * t;
    ans.mat[0][2] = -u * (1.0 - 2.0 * u);
    ans.mat[0][3] = 4.0 * u * v;
    ans.mat[0][4] = -v * (1.0 - 2.0 * v);
    ans.mat[0][5] = 4.0 * v * t;
    ans.mat[0][6] = 4.0 * p * t;
    ans.mat[0][7] = 4.0 * u * p;
    ans.mat[0][8] = 4.0 * v * p;
    ans.mat[0][9] = -p * (1.0 - 2.0 * p);

    shapeFunction = ans;
}
void NodalShapeFunctions::nodalHexahedralFirstOrder(double u, double v, double p)
{
    //Ref Ida&Bastos, pg 321, table 8.12
    Matrix<double> ans(1, 8);

    double a1 = 1.0 + u;
    double a2 = 1.0 - u;
    double b1 = 1.0 + v;
    double b2 = 1.0 - v;
    double c1 = 1.0 + p;
    double c2 = 1.0 - p;
    ans.mat[0][0] = a2 * b2 * c2 / 8.0;
    ans.mat[0][1] = a1 * b2 * c2 / 8.0;
    ans.mat[0][2] = a1 * b1 * c2 / 8.0;
    ans.mat[0][3] = a2 * b1 * c2 / 8.0;
    ans.mat[0][4] = a2 * b2 * c1 / 8.0;
    ans.mat[0][5] = a1 * b2 * c1 / 8.0;
    ans.mat[0][6] = a1 * b1 * c1 / 8.0;
    ans.mat[0][7] = a2 * b1 * c1 / 8.0;
    shapeFunction = ans;
}

/* ------------------------------------------------------------------------
Gauss Points
u	v	p
point 1
point 2
.
.
.
point n
---------------------------------------------------------------------------*/

GaussLegendrePoints::~GaussLegendrePoints() {}

GaussLegendrePoints::GaussLegendrePoints(int ElemType)
{

    switch (ElemType)
    {
    case 1: //First order line
        lineOnePoint();
        break;

    case 2: //First order triangle
        triangleOnePointsInside();
        break;

    case 4: //First order tetrahedral
        tetrahedralFourPoinst();
        break;

    case 5: //First order hexahedral
        hexahedralEightPoinstInside();
        break;

    case 8: //Second order line
        lineTwoPoints();
        break;

    case 9: //Second order triangle
        triangleThreePointsInside();
        break;

    case 11: //Second order tetrahedral
        tetrahedralFourPoinst();
        break;

    default:
        msg.NotImplementedElement(ElemType, "GaussLegendrePoints");
    }
}

void GaussLegendrePoints::lineTwoPoints()
{

    double k = sqrt(1.0 / 3.0);

    Matrix<double> ans(2, 3);
    ans.mat[0][0] = -k;
    ans.mat[0][1] = 0.0;
    ans.mat[0][2] = 0.0;
    ans.mat[1][0] = k;
    ans.mat[1][1] = 0.0;
    ans.mat[1][2] = 0.0;

    Matrix<double> ans_weights(1, 2);
    ans_weights.mat[0][0] = 1.0;
    ans_weights.mat[0][1] = 1.0;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::lineOnePoint()
{
    Matrix<double> ans(1, 3);
    ans.mat[0][0] = 0.0;
    ans.mat[0][1] = 0.0;
    ans.mat[0][2] = 0.0;

    Matrix<double> ans_weights(1, 1);
    ans_weights.mat[0][0] = 2.0;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::triangleOnePointsInside()
{
    Matrix<double> ans(1, 3);
    ans.mat[0][0] = 1.0 / 3.0;
    ans.mat[0][1] = 1.0 / 3.0;
    ans.mat[0][2] = 0.0;

    Matrix<double> ans_weights(1, 1);
    ans_weights.mat[0][0] = 0.5;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::triangleThreePointsInside()
{

    double one_six = 1.0 / 6.0;
    double two_three = 2.0 / 3.0;

    Matrix<double> ans(3, 3);
    ans.mat[0][0] = one_six;
    ans.mat[0][1] = one_six;
    ans.mat[0][2] = 0;
    ans.mat[1][0] = two_three;
    ans.mat[1][1] = one_six;
    ans.mat[1][2] = 0;
    ans.mat[2][0] = one_six;
    ans.mat[2][1] = two_three;
    ans.mat[2][2] = 0;

    Matrix<double> ans_weights(1, 3);
    ans_weights.mat[0][0] = 1.0 / 6.0;
    ans_weights.mat[0][1] = 1.0 / 6.0;
    ans_weights.mat[0][2] = 1.0 / 6.0;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::triangleSevenPointsInside()
{
    double a = 0.470142064;
    double b = 0.10128650;

    Matrix<double> ans(7, 3);
    ans.mat[0][0] = 1.0 / 3.0;
    ans.mat[0][1] = 1.0 / 3.0;
    ans.mat[0][2] = 0;
    ans.mat[1][0] = a;
    ans.mat[1][1] = a;
    ans.mat[1][2] = 0;
    ans.mat[2][0] = 1.0 - 2.0 * a;
    ans.mat[2][1] = a;
    ans.mat[2][2] = 0;
    ans.mat[3][0] = a;
    ans.mat[3][1] = 1.0 - 2.0 * a;
    ans.mat[3][2] = 0;
    ans.mat[4][0] = b;
    ans.mat[4][1] = b;
    ans.mat[4][2] = 0;
    ans.mat[5][0] = 1.0 - 2.0 * b;
    ans.mat[5][1] = b;
    ans.mat[5][2] = 0;
    ans.mat[6][0] = b;
    ans.mat[6][1] = 1.0 - 2 * b;
    ans.mat[6][2] = 0;

    Matrix<double> ans_weights(1, 7);
    ans_weights.mat[0][0] = 9.0 / 80.0;
    ans_weights.mat[0][1] = 0.066197076;
    ans_weights.mat[0][1] = 0.066197076;
    ans_weights.mat[0][2] = 0.066197076;
    ans_weights.mat[0][4] = 0.062969590;
    ans_weights.mat[0][5] = 0.062969590;
    ans_weights.mat[0][6] = 0.062969590;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::triangleFourPointsInside()
{
    Matrix<double> ans(4, 3);
    ans.mat[0][0] = 0.333333333333333;
    ans.mat[0][1] = 0.333333333333333;
    ans.mat[0][2] = 0;
    ans.mat[1][0] = 0.6;
    ans.mat[1][1] = 0.2;
    ans.mat[1][2] = 0;
    ans.mat[2][0] = 0.2;
    ans.mat[2][1] = 0.6;
    ans.mat[2][2] = 0;
    ans.mat[3][0] = 0.2;
    ans.mat[3][1] = 0.2;
    ans.mat[3][2] = 0;

    Matrix<double> ans_weights(1, 4);
    ans_weights.mat[0][0] = -0.28125;
    ans_weights.mat[0][1] = 0.260416666666;
    ans_weights.mat[0][2] = 0.260416666666;
    ans_weights.mat[0][3] = 0.260416666666;

    pointsCoordinates = ans;
    weights = ans_weights;
}
void GaussLegendrePoints::tetrahedralOnePoint()
{

    double k = 1.0 / 4.0;

    Matrix<double> ans(1, 3);
    ans.mat[0][0] = k;
    ans.mat[0][1] = k;
    ans.mat[0][2] = k;

    Matrix<double> ans_weights(1, 1);
    ans_weights.mat[0][0] = 1.0 / 6.0;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::tetrahedralFourPoinst()
{
    double a = 0.1381966;
    double b = 0.5854102;

    Matrix<double> ans(4, 3);
    ans.mat[0][0] = a;
    ans.mat[0][1] = a;
    ans.mat[0][2] = a;
    ans.mat[1][0] = a;
    ans.mat[1][1] = a;
    ans.mat[1][2] = b;
    ans.mat[2][0] = a;
    ans.mat[2][1] = b;
    ans.mat[2][2] = a;
    ans.mat[3][0] = b;
    ans.mat[3][1] = a;
    ans.mat[3][2] = a;

    double k = 1.0 / 24.0;

    Matrix<double> ans_weights(1, 4);
    ans_weights.mat[0][0] = k;
    ans_weights.mat[0][1] = k;
    ans_weights.mat[0][2] = k;
    ans_weights.mat[0][3] = k;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::tetrahedralFivePoinst()
{
    double a = 1.0 / 4.0;
    double b = 1.0 / 6.0;
    double c = 1.0 / 2.0;

    Matrix<double> ans(5, 3);
    ans.mat[0][0] = a;
    ans.mat[0][1] = a;
    ans.mat[0][2] = a;
    ans.mat[1][0] = b;
    ans.mat[1][1] = b;
    ans.mat[1][2] = b;
    ans.mat[2][0] = b;
    ans.mat[2][1] = b;
    ans.mat[2][2] = c;
    ans.mat[3][0] = b;
    ans.mat[3][1] = c;
    ans.mat[3][2] = b;
    ans.mat[4][0] = c;
    ans.mat[4][1] = b;
    ans.mat[4][2] = b;

    double k = 3.0 / 40.0;

    Matrix<double> ans_weights(1, 5);
    ans_weights.mat[0][0] = -2.0 / 15.0;
    ans_weights.mat[0][1] = k;
    ans_weights.mat[0][2] = k;
    ans_weights.mat[0][3] = k;
    ans_weights.mat[0][4] = k;

    pointsCoordinates = ans;
    weights = ans_weights;
}

void GaussLegendrePoints::hexahedralEightPoinstInside()
{
    double r_3 = 1.0 / sqrt(3.0);

    Matrix<double> ans(8, 3);
    ans.mat[0][0] = r_3;
    ans.mat[0][1] = r_3;
    ans.mat[0][2] = r_3;
    ans.mat[1][0] = -r_3;
    ans.mat[1][1] = r_3;
    ans.mat[1][2] = r_3;
    ans.mat[2][0] = r_3;
    ans.mat[2][1] = -r_3;
    ans.mat[2][2] = r_3;
    ans.mat[3][0] = -r_3;
    ans.mat[3][1] = -r_3;
    ans.mat[3][2] = r_3;
    ans.mat[4][0] = r_3;
    ans.mat[4][1] = r_3;
    ans.mat[4][2] = -r_3;
    ans.mat[5][0] = -r_3;
    ans.mat[5][1] = r_3;
    ans.mat[5][2] = -r_3;
    ans.mat[6][0] = r_3;
    ans.mat[6][1] = -r_3;
    ans.mat[6][2] = -r_3;
    ans.mat[7][0] = -r_3;
    ans.mat[7][1] = -r_3;
    ans.mat[7][2] = -r_3;

    double k = 1.0;
    Matrix<double> ans_weights(1, 7);
    ans_weights.mat[0][0] = k;
    ans_weights.mat[0][1] = k;
    ans_weights.mat[0][2] = k;
    ans_weights.mat[0][3] = k;
    ans_weights.mat[0][4] = k;
    ans_weights.mat[0][5] = k;
    ans_weights.mat[0][6] = k;

    pointsCoordinates = ans;
    weights = ans_weights;
}

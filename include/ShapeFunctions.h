#include <string>
#include <vector>
using namespace std;
using std::string;

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Matrix.h"


#ifndef _SHAPE_FUNCTIONS_INCLUDED_
#define _SHAPE_FUNCTIONS_INCLUDED_

class NodalShapeFunctions
{
public:
	/**
	Nodal shape functions
	@param ElemType: element type
	@param u,v,p: local coordinates
	@return 2D Matrix
	[N1 N2...Nn]
	*/
	void GetNodalShapeFunctions(int ElemType, double u, double v, double p);
	Matrix<double> shapeFunction;
	int ElementType;

	/**
	Gradient of nodal shape functions
	@param ElemType: element type
	@param u,v,p: local coordinates
	@return 2D Matrix
	[dN1/du		dN2/du	... dNn/du,
	dN1/dv		dN2/dv	... dNn/dv,
	dN1/dp		dN2/dp	... dNn/dp]
	*/
	void GetGradNodalShapeFunction(int ElemType, double u = 0, double v = 0, double p = 0);
	Matrix<double> gradShapeFunction;


private:
	void nodalLineFirstOrder(double u);
	void nodalLineSecondOrder(double u);

	void nodalTriangleFirstOrder(double u, double v);
	void nodalTriangleSecondOrder(double u, double v);

	void nodalTetrahedralFirstOrder(double u, double v, double p);
	void nodalTetrahedralSecondOrder(double u, double v, double p);

	void nodalHexahedralFirstOrder(double u, double v, double p);

	// Gradient of nodal shape functions
	void gradNodalLineFirstOrder();
	void gradNodalLineSecondOrder(double u);

	void gradNodalTriangleFirstOrder();
	void gradNodalTriangleSecondOrder(double u, double v);

	void gradNodalTetrahedralFirstOrder();	/**
	Gradient of nodal shape functions
	@param ElemType: element type
	@param u,v,p: local coordinates
	@return 2D Matrix
	[dN1/du		dN2/du	... dNn/du,
	dN1/dv		dN2/dv	... dNn/dv,
	dN1/dp		dN2/dp	... dNn/dp]
	*/
	void gradNodalTetrahedralSecondOrder(double u, double v, double p);

	void gradNodalHexahedralFirstOrder(double u, double v, double p);
};

class GaussLegendrePoints
{
public:
	/**
	Gauss points
	@param ElemType: element type
	*/
	GaussLegendrePoints(int ElemType);

	/**
	Local coordinates
	@return 2D Matrix
	[u1	v1 p1,
	u2	v2 p2,
	un	vn pn]
	*/
	Matrix<double> pointsCoordinates;

	/**
	Weight for each point
	@return 2D Matrix
	[W1 w2 ... Wn]
	*/
	Matrix<double> weights;

	int ElementType;

	~GaussLegendrePoints();

private:
	void lineTwoPoints();
	void lineOnePoint();

	void triangleOnePointsInside();
	void triangleThreePointsInside();
	void triangleFourPointsInside();
	void triangleSevenPointsInside();

	void tetrahedralOnePoint();
	void tetrahedralFourPoinst();
	void tetrahedralFivePoinst();

	void hexahedralEightPoinstInside();
};

#endif
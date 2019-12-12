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





class ShapeFunctions
{
public:
    /**
    @param ElemType: element type
    @param u,v,p: local coordinates
    @return 2D Matrix
    [N1 N2...Nn]
    */
    ShapeFunctions(int ElemType, double u, double v, double p);
    Matrix<double> shapeFunction;
    int ElementType;

    ~ShapeFunctions();

private:
    void nodalLineFirstOrder(double u);
    void nodalLineSecondOrder(double u);

    void nodalTriangleFirstOrder(double u, double v);
    void nodalTriangleSecondOrder(double u, double v);

    void nodalTetrahedralFirstOrder(double u, double v, double p);
    void nodalTetrahedralSecondOrder(double u, double v, double p);

    void nodalHexahedralFirstOrder(double u, double v, double p);
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
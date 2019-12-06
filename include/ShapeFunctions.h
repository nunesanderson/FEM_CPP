#include <string>
#include<vector>
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
    ShapeFunctions(int ElemType, double u, double v, double p);
    Matrix<double> shapeFunction;


	~ShapeFunctions();

private:
	// Nodal shape functions
	void nodalLineFirstOrder(double u);
};
#endif
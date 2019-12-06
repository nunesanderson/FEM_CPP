
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

ShapeFunctions::~ShapeFunctions() {}

ShapeFunctions::ShapeFunctions(int ElemType, double u, double v, double p)
{
    nodalLineFirstOrder(u);

}

void ShapeFunctions::nodalLineFirstOrder(double u) {
	Matrix<double> ans(1, 2);
	ans.mat[0][0] = 0.5 * (1.0 - u);
	ans.mat[0][1] = 0.5 * (1.0 + u);
	shapeFunction=ans;
}
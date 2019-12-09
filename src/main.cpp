#include <iostream>
#include <string>
#include <time.h>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
// #include "ShapeFunctions.cpp"
#include "../include/ShapeFunctions.h"

using namespace std;

int main()
{

    // Reference matrix
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

    cout << "It should print:" << endl;
    ans.print_matrix();



    cout << "but it prints:" << endl;
    GaussLegendrePoints points(9);
    points.pointsCoordinates.print_matrix();


    Messages msg;

    return 0;
}
#include <iostream>
#include <string>
#include <time.h>
#include <typeinfo>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
// #include "ShapeFunctions.cpp"
#include "../include/ShapeFunctions.h"
#include "../include/Gmsh_interface.h"
#include "../include/PerformanceTestes.h"

using namespace std;

int main()
{

    string path("/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/examples/1_Actuator/rele.msh");
    GetMesh data(path);
    data.elemNodes;

    Matrix<double> mat1(2, 3);
    mat1.mat[0][0] = 1;
    mat1.mat[0][1] = 2;
    mat1.mat[0][2] = 3;
    mat1.mat[1][0] = 4;
    mat1.mat[1][1] = 5;
    mat1.mat[1][2] = 6;


    Matrix<double> mat2(3, 2);
    mat2.mat[0][0] = 1;
    mat2.mat[1][1] = 2;
    mat2.mat[2][0] = 3;
    mat2.mat[0][1] = 4;
    mat2.mat[1][0] = 5;
    mat2.mat[2][1] = 6;


    Matrix<double> ans=mat1*mat2;
    mat1.print_matrix();
    mat2.print_matrix();
    ans.print_matrix();
    ans.calcDet();
    cout<<ans.detVal<<endl;



    return 0;
}
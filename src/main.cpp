#include<iostream>
#include<string>


/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
// #include "ShapeFunctions.cpp"
#include "../include/ShapeFunctions.h"

using namespace std;

int main(){




    ShapeFunctions test(1,0,0,0);
    test.shapeFunction.print_matrix();
    
    // shape.GetNodalShapeFunction(1,0,0,0);




 
 


    Messages msg;
    msg.logMessage("Lines: "+std::to_string(test.shapeFunction.rows));


    return 0;
}
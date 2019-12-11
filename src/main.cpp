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

using namespace std;

int main()
{

    string path("/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/examples/1_Actuator/rele.msh");
    GetMesh data(path);
    data.elemNodes;
    for (auto i = data.elemNodes[0].begin(); i != data.elemNodes[0].end(); i++)
    {
        cout << *i << endl;
    }

    // data.nodesCoordinates.print_matrix();
    cout<<"Nodes: "<<data.numNodes<<endl;
    cout<<"Elements: "<<data.numElemments<<endl;

    return 0;
}
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using std::string;

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Matrix.h"

#ifndef _GET_MESH_INCLUDED_
#define _GET_MESH_INCLUDED_

class GetMesh
{
private:
    template <typename T>
    vector<T> split(string str, string delimiter);
    vector<int> elemTypes1D;
    vector<int> elemTypes2D;

public:
    GetMesh(string filePath);
    Matrix<double> nodesCoordinates;
    Matrix<int> elemTypes;
    Matrix<int> physicalTags;
    Matrix<int> elementaryTags;
    int numElemments;
    int numNodes;
    int numElements1D;
    int numElements2D;
    // It uses vector<vector<int>> because the number
    // of nodes may vary in meshes with different elements
    vector<vector<int>> elemNodes;

    ~GetMesh();

private:
};
#endif

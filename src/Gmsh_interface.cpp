
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
using namespace std;
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Gmsh_interface.h"
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
template <typename T>
vector<T> Mesh::split(string s, string delimiter)
{

    vector<T> list;

    //add a delimiter at the end of the string
    if (s.find(delimiter))
        s.replace(s.end(), s.end() - 1, delimiter);

    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        if (std::is_integral<T>::value)
        {
            list.push_back(stoi(token));
        }
        else if (std::is_floating_point<T>::value)
        {
            list.push_back(stod(token));
        }
        else
        {
            throw std::invalid_argument("Template type not implemented.");
        }

        s.erase(0, pos + delimiter.length());
    }

    return list;
}

Mesh::~Mesh(void)
{
}

Mesh::Mesh()
{
}

Mesh::Mesh(string filePath)
{
    // 1: 2-node line
    // 15: 1- node point
    // 2: 3-node triangle.
    // 8: 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
    this->elemTypes0D = {15};
    this->elemTypes1D = {1, 8};
    this->elemTypes2D = {2};
    string line;
    ifstream myfile(filePath);
    Messages messages;
    Matrix<double> nodesCoord;
    string delimiter = " ";

    int lineCounter = 0;

    int startNodes = 0;
    int startElem = 0;

    int numNodes = 0;
    int numElem = 0;

    bool ReadNodes = false;
    bool ReadElem = false;

    int coordCounter = 0;
    int elemCounter = 0;

    this->numElements0D = 0;
    this->numElements1D = 0;
    this->numElements2D = 0;

    if (myfile.is_open())
    {

        while (getline(myfile, line))
        {

            // Find the Nodes block begining
            if (line == "$Nodes")
                startNodes = lineCounter;

            // Allocates the coordinates array
            if (lineCounter == startNodes + 1 && startNodes > 0)
            {
                numNodes = stoi(line);
                this->nodesCoordinates.Alloc(numNodes, 3);
            }

            // Check whether needs to read the coordinates
            if (lineCounter == startNodes + 2 && startNodes > 0)
                ReadNodes = true;

            if (line == "$EndNodes")
                ReadNodes = false;

            // Redas the coordinates
            if (ReadNodes)
            {
                vector<double> list = this->split<double>(line, delimiter);
                this->nodesCoordinates.mat[coordCounter][0] = list[1];
                this->nodesCoordinates.mat[coordCounter][1] = list[2];
                this->nodesCoordinates.mat[coordCounter][2] = list[3];
                coordCounter++;
            }

            // Find the Elements block begining
            if (line == "$Elements")
                startElem = lineCounter;

            // Allocates the arrays
            if (lineCounter == startElem + 1 && startElem > 0)
            {
                numElem = stoi(line);
                this->elemTypes.Alloc(1, numElem);
                this->physicalTags.Alloc(1, numElem);
                this->elementaryTags.Alloc(1, numElem);
            }

            // Check whether needs to read the elements
            if (lineCounter == startElem + 2 && startElem > 0)
                ReadElem = true;

            if (line == "$EndElements")
                ReadElem = false;

            // Reads the coordinates
            if (ReadElem)
            {
                vector<int> list = this->split<int>(line, delimiter);
                this->elemTypes.mat[0][elemCounter] = list[1];
                this->physicalTags.mat[0][elemCounter] = list[3];
                this->elementaryTags.mat[0][elemCounter] = list[4];
                elemCounter++;

                // Check the element dimensions and insert at the corret vector
                if (std::find(elemTypes1D.begin(), elemTypes1D.end(), list[1]) != elemTypes1D.end())
                {
                    this->elemNodes1D.push_back(std::vector<int>(list.begin() + 5, list.end()));
                    numElements1D++;
                }
                else if (std::find(elemTypes2D.begin(), elemTypes2D.end(), list[1]) != elemTypes2D.end())
                {
                    this->elemNodes2D.push_back(std::vector<int>(list.begin() + 5, list.end()));
                    numElements2D++;
                }
                else if (std::find(elemTypes0D.begin(), elemTypes0D.end(), list[1]) != elemTypes0D.end())
                {
                    this->elemNodes0D.push_back(std::vector<int>(list.begin() + 5, list.end()));
                    numElements0D++;
                }
            }

            lineCounter++;
        }
        myfile.close();
        this->numElemments = elemCounter;
        this->numNodes = coordCounter;
    }
    else
    {
        messages.logMessage("Unable to open this file:" + filePath);
    }
}
Mesh Mesh::operator=(Mesh meshData)
{
    this->elementaryTags = meshData.elementaryTags;
    this->elemNodes1D = meshData.elemNodes1D;
    this->elemNodes2D = meshData.elemNodes2D;
    this->elemTypes1D = meshData.elemTypes1D;
    this->elemTypes2D = meshData.elemTypes2D;
    this->elemTypes = meshData.elemTypes;
    this->nodesCoordinates = meshData.nodesCoordinates;
    this->numElements1D = meshData.numElements1D;
    this->numElements2D = meshData.numElements2D;
    this->numElemments = meshData.numElemments;
    this->numNodes = meshData.numNodes;
    this->physicalTags = meshData.physicalTags;

    return *this;
}

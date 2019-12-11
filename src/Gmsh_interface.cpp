
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
vector<T> GetMesh::split(string s, string delimiter)
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

GetMesh::~GetMesh(void)
{
}
GetMesh::GetMesh(string filePath)
{
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

    if (myfile.is_open())
    {

        while (getline(myfile, line))
        {

            // Find the Nodes block begining
            if (line == "$Nodes\r")
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

            if (line == "$EndNodes\r")
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
            if (line == "$Elements\r")
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

            if (line == "$EndElements\r")
                ReadElem = false;

            // Redas the coordinates
            if (ReadElem)
            {
                vector<int> list = this->split<int>(line, delimiter);
                this->elemTypes.mat[0][elemCounter] = list[1];
                this->physicalTags.mat[0][elemCounter] = list[3];
                this->elementaryTags.mat[0][elemCounter] = list[4];
                this->elemNodes.push_back(std::vector<int>(list.begin(), list.end()));
                elemCounter++;
            }

            lineCounter++;
        }
        myfile.close();
        this->numElemments=elemCounter;
        this->numNodes=coordCounter;

    }
    else
    {
        messages.logMessage("Unable to open this file:" + filePath);
    }

    // nodesCoord.print_matrix();
}

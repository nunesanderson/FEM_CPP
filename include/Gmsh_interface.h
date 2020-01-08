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

class Mesh
{
private:
  template <typename T>
  vector<T> split(string str, string delimiter);
  vector<int> elemTypes1D;
  vector<int> elemTypes2D;

public:
  /**
 * Reads the mesh from a .msh file
 * .msh mesh version is 2.x
 * 
 * @param filePath: file path (with name) of the .msh file
 */
  Mesh(string filePath);
  Mesh();
  //operator overloading: =Mesh
  Mesh operator=(Mesh meshData);

  /// Access the nodes coordinates
  Matrix<double> nodesCoordinates;

  /// Access the element types
  Matrix<int> elemTypes;

  /// Access the physical ID tags
  Matrix<int> physicalTags;

  ///Access the elementary tags
  Matrix<int> elementaryTags;

  /// Total number of elements
  int numElemments;

  ///Access the number of nodes
  int numNodes;
  ///Access the number of 1D elements
  int numElements1D;

  ///Access the number of 2D elements
  int numElements2D;

  /**
 * Nodes of each 1D element
 * It uses vector<vector<int>> because the number
* of nodes may vary in meshes with different element types
 */
  vector<vector<int>> elemNodes2D;

  /**
 * Nodes of each 2D element
 * It uses vector<vector<int>> because the number
* of nodes may vary in meshes with different element types
 */
  vector<vector<int>> elemNodes1D;

  // TODO: check how to implement the destructor
  ~Mesh();

private:
};
#endif

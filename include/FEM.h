/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Gmsh_interface.h"

#ifndef _FEM_INCLUDED_
#define _FEM_INCLUDED_

class FEM
{
private:

/**
 * Gets the position in a vector
 * 
 * @param value: value to find
 * @param this_vector: the vector to search
 */ 
    int getPositionInVector(int i, vector<int> this_vector);

public:
    ///Specify the .msh file path
    string mesh_path;

    //Formulation name
    string formulationName;

    //Symmetry
    string Symmetry;

    /// Specify the .msh file name
    string mesh_file_name;

    ///Specify physical regions ID
    vector<int> setup_phys_region_ID;

    ///Specify physical regions material property
    vector<double> setup_phys_region_relative_property;

    /// Specify physical regions excitations
    vector<double> setup_phys_region_excitation;

    ///Specify the physical boundary conditions ID
    vector<int> setup_phys_BC_ID;

    /// Specify the boundary condition values for each ID
    vector<double> setup_phys_BC_val;

    ///Acess the solution
    Matrix<double> solution;

    ///Runs the Finite Element Method
    void run();
};

#endif
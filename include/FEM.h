
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Gmsh_interface.h"

#ifndef _FEM_INCLUDED_
#define _FEM_INCLUDED_

class FEM
{
private:
    int getPositionInVector(int,vector<int> );
public:
    string mesh_path;

    vector<int> setup_phys_region_ID;
    vector<double> setup_phys_region_perm_rel;
    vector<double> setup_phys_region_excitation;
    vector<int> setup_phys_BC_ID;
    vector<double> setup_phys_BC_val;

    Matrix<double> solution;
    void run();
};

#endif
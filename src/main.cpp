#include <iostream>
#include <string>
#include <time.h>
#include <typeinfo>
#include <iostream>
#include <cstring>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Messages.h"
#include "../include/Matrix.h"
#include "Matrix.cpp"
#include "../include/ShapeFunctions.h"
#include "../include/Gmsh_interface.h"
#include "../include/FEM.h"
#include <lapacke.h>
using namespace std;

int main()
{

    FEM run_FEM;
    run_FEM.mesh_path = "/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/examples/02_relay";
    run_FEM.mesh_file_name = "rele.msh";

    run_FEM.setup_phys_region_ID = {30, 31, 32, 33};
    run_FEM.setup_phys_region_perm_rel = {1000.0, 1.0, 1.0, 1000.00};
    run_FEM.setup_phys_region_excitation = {0.0, 100000000, 0.0, 0.0};
    run_FEM.setup_phys_BC_ID = {34};
    run_FEM.setup_phys_BC_val = {1.0};

    // run_FEM.mesh_path = "/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/examples/01_simple_mesh";
    // run_FEM.mesh_file_name= "simple_mesh.msh";
    // run_FEM.setup_phys_region_ID = {1, 2};
    // run_FEM.setup_phys_region_perm_rel = {1.0, 1.0};
    // run_FEM.setup_phys_region_excitation = {0.0, 100000000};
    // run_FEM.setup_phys_BC_ID = {3};
    // run_FEM.setup_phys_BC_val = {2.0};
    run_FEM.run();

   
}
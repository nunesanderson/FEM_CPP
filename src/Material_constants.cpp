#define _USE_MATH_DEFINES
#include <cmath>
/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Material_constants.h"


Material_constants::Material_constants()
{
this->mu0=4*M_PI*pow(10,-7);
this->eps0=8.8541878128*pow(10,-12);
}

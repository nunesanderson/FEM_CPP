#ifndef _MATERIAL_CONSTANTS_INCLUDED_
#define _MATERIAL_CONSTANTS_INCLUDED_

class Material_constants
{
private:
public:
    /// Set vacuum constants
    Material_constants();

    /// Access the vacuum permeability $\mu_0$
    double mu0;

    /// Access the vacuum permitivity $\eps_0$
    double eps0;
};

#endif

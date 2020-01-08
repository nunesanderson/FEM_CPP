/* -------------------------------------------------------------------
   File "CoreSta.pro"

   This file defines the problem dependent data structures for the
   static core-inductor problem.
   
   To compute the solution: 
       getdp CoreSta -msh Core.msh -solve MagSta_a_2D

   To compute post-results: 
       getdp CoreSta -msh Core.msh -pos Map_a
   ------------------------------------------------------------------- */

Group {
Air    = Region[ {32} ];
Core   = Region[ {30,33} ];
Ind_pos    = Region[31];
//Ind_neg    = Region[];
SurfaceGe0  = Region[ 34];

  DomainCC_Mag = Region[ {Air, Core, Ind_pos} ];
  DomainC_Mag  = Region[ {} ];
  DomainS_Mag  = Region[ {Ind_pos} ]; // Stranded inductor
  DomainInf    = Region[ {} ];
  Domain_Mag   = Region[ {DomainCC_Mag, DomainC_Mag} ];
}

Function {

  mu0 = 4.e-7 * Pi;
  murCore = 1000.;

  nu [ Region[{Air,Ind_pos}] ]  = 1. / mu0;
  nu [ Core ]  = 1. / (murCore * mu0);


}

Constraint {

  { Name MagneticVectorPotential_2D;
    Case {
      { Region SurfaceGe0 ; Value 0.; }
    }
  }

  { Name SourceCurrentDensityZ;
    Case {
	  { Region Ind_pos; Value 100000000.0; }
    }
  }
}

Include "Jacobian_Lib.pro"
Include "Integration_Lib.pro"
Include "MagSta_a_2D.pro"

e = 1.e-5;
p1 = {0.085,0,0};
p2 = {0.085,0.1,0};

PostOperation {

  { Name Map_a; NameOfPostProcessing MagSta_a_2D;
    Operation {
      Print[ az, OnElementsOf Domain_Mag, File "CoreSta_a.pos" ];
	  Print[ b, OnElementsOf Domain_Mag, File "CoreSta_b.pos" ];
	  Print[ b, OnLine{{List[p1]}{List[p2]}} {100}, File "b_line.pos",File  "b_line.dat", Format SimpleTable ];
	  /*
	  Print[ b, OnElementsOf Domain_Gap, File "Gap_b.pos" ];
	  Print[ az, OnLine{{List[p3]}{List[p4]}} {1000}, File "az_line" ];*/
  
    }
  }

}

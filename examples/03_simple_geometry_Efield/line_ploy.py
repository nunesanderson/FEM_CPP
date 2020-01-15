import numpy as np
import os
from os import listdir
from os.path import isfile, join
import matplotlib.pyplot as plt
import matplotlib.tri as mtri
from matplotlib import RcParams


## =============================================================================
## Plot font
## =============================================================================
#
fig, ax = plt.subplots(figsize=(6*0.9,5*0.9))
latex_style_times = RcParams({'font.family': 'serif',
               'font.serif': ['cmr10'],
               'text.usetex': True, 'font.size': 15})

# =============================================================================
# Reads the data
# =============================================================================
file_name="results/line_results.txt"
dir_path = os.path.dirname(os.path.realpath(__file__))
path=os.path.join(dir_path,file_name)
results=np.loadtxt(path)

file_name="results/line_coordinates.txt"
dir_path = os.path.dirname(os.path.realpath(__file__))
path=os.path.join(dir_path,file_name)
coordinates=np.loadtxt(path)

getdp=np.loadtxt("/home/anderson/Anderson/Drive/1_Study/2_C++/3_FEM_C++/tests_external_programs/02_Efield/femm_results.txt")

# =============================================================================
# Plot
# =============================================================================
plt.close('all')
plt.plot(coordinates[:,0], results[:,0],'k',label="Implemented")
plt.plot(getdp[:,0], getdp[:,1],'b',label="GetDP")  
ax.ticklabel_format(style='sci',scilimits=(0,0),axis='both')
plt.style.use(latex_style_times)
plt.title('By along the air gap')
plt.ylabel(r'By [T]')
plt.xlabel(r'Distance [m]')
plt.grid(b=True, which='both')
plt.legend()
plt.tight_layout()
plt.savefig("line_plot.pdf")
plt.show()
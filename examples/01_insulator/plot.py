import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as mtri
import matplotlib.cm as cm
import matplotlib.lines as mlines

def newline(p1, p2):
    ax = plt.gca()
    l = mlines.Line2D([p1[0],p2[0]], [p1[1],p2[1]],color='k',linewidth=2)
    ax.add_line(l)
    return l


plt.close("all")
z=np.loadtxt('results/solution.txt')
coord=np.loadtxt('results/nodes_coordinates.txt')
phys_ID=np.loadtxt('results/2D_phys_tags.txt')
triangulation=np.loadtxt('results/triangulation.txt')
triangulation1D=np.loadtxt('results/elem_nodes_1D.txt')
grad_domain=np.loadtxt('results/grad_domain.txt')

x=coord[:,0]
y=coord[:,1]
triangulation=triangulation-1
cmap = cm.get_cmap(name='jet', lut=None)
triang = mtri.Triangulation(x, y, triangulation)    

n_levels=30
fig, axs = plt.subplots(nrows=1, ncols=1)
levels = np.arange(0., max(z),max(z)/n_levels)

#Equipotencial lines
#tcf=axs.tricontour(triang, z,n_levels,levels=levels)

#Potential distribution
#tcf=axs.tricontourf(triang, z,n_levels,cmap=cmap)
#fig.colorbar(tcf)

#Mesh
tcf=plt.tripcolor(triang, 'k-',alpha=0.4, lw=0.8,facecolors=grad_domain,cmap=cmap)
fig.colorbar(tcf)

#Geometry lines
triangulation1D=triangulation1D-1
for k in range(0,len(triangulation1D)):
    p1 = [coord[ int(triangulation1D[k,0]),0],coord[int(triangulation1D[k,0]),1]]
    p2 = [coord[ int(triangulation1D[k,1]),0],coord[int(triangulation1D[k,1]),1]]
    newline(p1,p2)
plt.tight_layout()
plt.savefig("fields_plot.pdf")
plt.show()

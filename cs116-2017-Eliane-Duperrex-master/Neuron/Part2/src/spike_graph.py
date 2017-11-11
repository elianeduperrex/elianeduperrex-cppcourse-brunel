import numpy as np
import matplotlib.pyplot as pl
from matplotlib.gridspec import GridSpec

data = np.genfromtxt('../res/times_spike.txt') 

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()

fig = pl.figure()

gs = GridSpec(4,1)
ax0 = pl.subplot(gs[:-1, :])
ax0.scatter(data1[0],data1[1],alpha=0.8, edgecolors='black', color='grey');
pl.axis([0, 400, 0, 30])
pl.title('Graph d (g=6, v_ext/v_thr=4)', fontsize=16, color='black', fontstyle='italic')
pl.ylabel('neuron (each line is a neuron)', color='grey')
ax = pl.gca()
ax.set_xticklabels([])
ax.set_yticklabels([])

pl.subplots_adjust(hspace=0.0)
ax1 = pl.subplot(gs[-1, :])
data = data.transpose()
n, bins, patches = pl.hist(data[0], 300, normed=0, alpha=0.75, color='grey')
ax1.set_xlim([0,400])
pl.xlabel('time [ms]', color = 'grey')

pl.show();





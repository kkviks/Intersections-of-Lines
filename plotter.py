import numpy as np
import os
import random
import pylab as pl
import matplotlib
from matplotlib import collections as mc

lines = []
c = []

dirname = os.path.dirname(__file__)
filename = os.path.join(dirname, './input.txt')
f = open(filename, "r")

x = f.readline()

while True:
    x = f.readline()
    if not x:
        break
    x = x.split()
    lines.append([(float(x[0]), float(x[1])), (float(x[2]), float(x[3]))])
    # c.append((0, 0, 0, 1))
    c.append((random.random(), random.random(), random.random(), 1))

lc = mc.LineCollection(lines, colors = c, linewidths = 1.5)
fig, ax = pl.subplots()
ax.add_collection(lc)
ax.autoscale()
ax.margins(0.05)

f.close()

filename = os.path.join(dirname, './output.txt')
f = open(filename, "r")

while True:
    x = f.readline()
    if not x:
        break
    x = x.split()
    pl.plot(float(x[0]), float(x[1]), 'ro', markersize = 4)

matplotlib.pyplot.show()

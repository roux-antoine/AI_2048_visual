
import matplotlib.pyplot as plt
from matplotlib import colors as mcolors
import numpy as np
import pandas as pd
# from os import listdir
import os
from os.path import isfile, join


#########@
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', '#FFA500', '#FFC0CB', '#808080', '#00FF00']
# blue, green, red, cyan, magenta, yellow, black, orange, pink, gray, lime

#########
mypath = os.getcwd()
filenames = [f for f in os.listdir(mypath) if isfile(join(mypath, f))]
statsFilenames = []
for filename in filenames:
    if '.csv' in filename:
        statsFilenames.append(filename)


for idx, filename in enumerate(statsFilenames):
    stats = pd.read_csv(filename)

    # print(stats)
    # print(stats.columns)

    plt.plot(stats["Best fitnesses"], '-', color=colors[idx], label=filename)
    plt.plot(stats["Average fitnesses"], '--', color=colors[idx], label=filename)
plt.legend()
plt.show()

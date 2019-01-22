
import matplotlib.pyplot as plt
from matplotlib import colors as mcolors
import numpy as np
import pandas as pd
import os
from os.path import isfile, join


#########@
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', '#FFA500', '#FFC0CB', '#808080', '#00FF00']
# blue, green, red, cyan, magenta, yellow, black, orange, pink, gray, lime

#########
# mypath = os.getcwd()
# filenames = [f for f in os.listdir(mypath) if isfile(join(mypath, f))]
# statsFilenames = []
# for filename in filenames:
#     if '.csv' in filename:
#         statsFilenames.append(filename)
#
#
# for idx, filename in enumerate(statsFilenames):
#     stats = pd.read_csv(filename)
#
#     # print(stats)
#     # print(stats.columns)
#
#     # plt.plot(stats["Best fitnesses"], '-', color=colors[idx], label=filename)
#     # plt.plot(stats["Average fitnesses"], '--', color=colors[idx], label=filename)
# # plt.legend()
# # plt.xlim(0, 15)
# # plt.show()


##########
avg_16_1 = pd.read_csv('16-1_1_stats.csv')["Average fitnesses"]
for k in range(2, 9):
    avg_16_1 += pd.read_csv('16-1_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_16_1 = avg_16_1 / 8

avg_16_9_1_0_0 = pd.read_csv('16-9-1-0-0_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_16_9_1_0_0 += pd.read_csv('16-9-1-0-0_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_16_9_1_0_0 = avg_16_9_1_0_0 / 4

avg_16_9_1_1_0 = pd.read_csv('16-9-1-1-0_1_stats.csv')["Average fitnesses"]
for k in range(1, 6):
    avg_16_9_1_1_0 += pd.read_csv('16-9-1-1-0_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_16_9_1_1_0 = avg_16_9_1_1_0 / 5

plt.plot(avg_16_1, label='avg_16_1')
plt.plot(avg_16_9_1_0_0, label='avg_16_9_1_0_0')
plt.plot(avg_16_9_1_1_0, label='avg_16_9_1_1_0')

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('evolution of average final score with network structure')
plt.show()

#################

for k in range(1, 9):
    avg = pd.read_csv('16-1_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Structure 16-1')
plt.show()

#################

for k in range(1, 5):
    avg = pd.read_csv('16-9-1-0-0_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Structure 16-9-1-0-0')
plt.show()

#################

for k in range(1, 6):
    avg = pd.read_csv('16-9-1-1-0_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Structure 16-9-1-1-0')
plt.show()


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

avg_12 = pd.read_csv('12gen_1_stats.csv')["Average fitnesses"]
for k in range(2, 10):
    avg_12 += pd.read_csv('12gen_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_12 = avg_12 / 9

avg_24 = pd.read_csv('24gen_1_stats.csv')["Average fitnesses"]
for k in range(2, 11):
    avg_24 += pd.read_csv('24gen_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_24 = avg_24 / 10

avg_36 = pd.read_csv('36gen_1_stats.csv')["Average fitnesses"]
for k in range(2, 11):
    avg_36 += pd.read_csv('36gen_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_36 = avg_36 / 10

plt.plot(avg_12, label='12 gen')
plt.plot(avg_24, label='24 gen')
plt.plot(avg_36, label='36 gen')

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('evolution of average final score with number of generations')
plt.show()

#################

for k in range(1, 10):
    avg = pd.read_csv('12gen_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('12 gen')
plt.show()

#################@

for k in range(1, 11):
    avg = pd.read_csv('24gen_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('24 gen')
plt.show()

#################@

for k in range(1, 11):
    avg = pd.read_csv('36gen_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('36 gen')
plt.show()

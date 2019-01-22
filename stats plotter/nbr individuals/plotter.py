
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

avg_8 = pd.read_csv('8_1_stats.csv')["Average fitnesses"]
for k in range(2, 2):
    avg_8 += pd.read_csv('8_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_8 = avg_8 / 1

avg_16 = pd.read_csv('16_1_stats.csv')["Average fitnesses"]
for k in range(2, 2):
    avg_16 += pd.read_csv('16_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_16 = avg_16 / 1

avg_32 = pd.read_csv('32_1_stats.csv')["Average fitnesses"]
for k in range(2, 2):
    avg_32 += pd.read_csv('32_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_32 = avg_32 / 1

avg_64 = pd.read_csv('64_1_stats.csv')["Average fitnesses"]
for k in range(2, 2):
    avg_64 += pd.read_csv('64_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_64 = avg_64 / 1

avg_128 = pd.read_csv('128_1_stats.csv')["Average fitnesses"]
for k in range(2, 3):
    avg_128 += pd.read_csv('128_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_128 = avg_128 / 2

avg_256 = pd.read_csv('256_1_stats.csv')["Average fitnesses"]
for k in range(2, 3):
    avg_256 += pd.read_csv('256_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_256 = avg_256 / 2


plt.plot(avg_8, label='8')
plt.plot(avg_16, label='16')
plt.plot(avg_32, label='32')
plt.plot(avg_64, label='64')
plt.plot(avg_128, label='128')
plt.plot(avg_256, label='256')

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('evolution of average final score with generation size')
plt.show()

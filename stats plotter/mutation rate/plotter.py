
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

avg_01 = pd.read_csv('01_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_01 += pd.read_csv('01_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_01 = avg_01 / 4

avg_02 = pd.read_csv('02_1_stats.csv')["Average fitnesses"]
for k in range(2, 7):
    avg_02 += pd.read_csv('02_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_02 = avg_02 / 6

avg_03 = pd.read_csv('03_1_stats.csv')["Average fitnesses"]
for k in range(2, 8):
    avg_03 += pd.read_csv('03_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_03 = avg_03 / 7

avg_04 = pd.read_csv('04_1_stats.csv')["Average fitnesses"]
for k in range(2, 7):
    avg_04 += pd.read_csv('04_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_04 = avg_04 / 6

avg_05 = pd.read_csv('05_1_stats.csv')["Average fitnesses"]
for k in range(2, 6):
    avg_05 += pd.read_csv('05_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_05 = avg_05 / 5

avg_06 = pd.read_csv('06_1_stats.csv')["Average fitnesses"]
for k in range(2, 6):
    avg_06 += pd.read_csv('06_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_06 = avg_06 / 5


plt.plot(avg_01, label='0.1')
plt.plot(avg_02, label='0.2')
plt.plot(avg_03, label='0.3')
plt.plot(avg_04, label='0.4')
plt.plot(avg_05, label='0.5')
plt.plot(avg_06, label='0.6')
plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('evolution of average final score with mutation rate')
plt.show()

#################

for k in range(1, 5):
    avg = pd.read_csv('01_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Mutation rate 0.1')
plt.show()

#################

for k in range(1, 7):
    avg = pd.read_csv('02_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Mutation rate 0.2')
plt.show()

#################

for k in range(1, 8):
    avg = pd.read_csv('03_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Mutation rate 0.3')
plt.show()

#################

for k in range(1, 7):
    avg = pd.read_csv('04_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Mutation rate 0.4')
plt.show()

#################

for k in range(1, 6):
    avg = pd.read_csv('05_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Mutation rate 0.5')
plt.show()

#################

for k in range(1, 6):
    avg = pd.read_csv('06_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Mutation rate 0.6')
plt.show()

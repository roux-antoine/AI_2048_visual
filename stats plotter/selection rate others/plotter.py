
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

############################

avg_0 = pd.read_csv('12_gen_0_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_0 += pd.read_csv('12_gen_0_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_0 = avg_0 / 4

avg_005 = pd.read_csv('12_gen_005_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_005 += pd.read_csv('12_gen_005_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_005 = avg_005 / 4

avg_01 = pd.read_csv('12_gen_01_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_01 += pd.read_csv('12_gen_01_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_01 = avg_01 / 4

avg_03 = pd.read_csv('12_gen_03_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_03 += pd.read_csv('12_gen_03_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_03 = avg_03 / 4

avg_0 = (pd.read_csv('12_gen_0_1_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_0_2_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_0_3_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_0_4_stats.csv')["Average fitnesses"]) / 4
avg_005 = (pd.read_csv('12_gen_005_1_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_005_2_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_005_3_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_005_4_stats.csv')["Average fitnesses"]) / 4
avg_01 = (pd.read_csv('12_gen_01_1_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_01_2_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_01_3_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_01_4_stats.csv')["Average fitnesses"]) / 4
avg_03 = (pd.read_csv('12_gen_03_1_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_03_2_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_03_3_stats.csv')["Average fitnesses"] + pd.read_csv('12_gen_03_4_stats.csv')["Average fitnesses"]) / 4

plt.plot(avg_0, label='0')
plt.plot(avg_005, label='0.05')
plt.plot(avg_01, label='0.1')
plt.plot(avg_03, label='0.3')
plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('evolution of average final score with others individuals selection rate')
plt.show()

############################

avg_0 = pd.read_csv('0_1_stats.csv')["Average fitnesses"]
for k in range(2, 6):
    avg_0 += pd.read_csv('0_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_0 = avg_0 / 5

avg_005 = pd.read_csv('005_1_stats.csv')["Average fitnesses"]
for k in range(2, 6):
    avg_005 += pd.read_csv('005_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_005 = avg_005 / 5

avg_01 = pd.read_csv('01_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_01 += pd.read_csv('01_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_01 = avg_01 / 4

avg_03 = pd.read_csv('03_1_stats.csv')["Average fitnesses"]
for k in range(2, 5):
    avg_03 += pd.read_csv('03_' + str(k) + '_stats.csv')["Average fitnesses"]
avg_03 = avg_03 / 4

plt.plot(avg_0, label='0')
plt.plot(avg_005, label='0.05')
plt.plot(avg_01, label='0.1')
plt.plot(avg_03, label='0.3')
plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('evolution of average final score with others individuals selection rate')
plt.show()

############################

for k in range(1, 6):
    avg = pd.read_csv('0_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Selection rate others 0')
plt.show()

#################

for k in range(1, 6):
    avg = pd.read_csv('005_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Selection rate others 0.05')
plt.show()

#################

for k in range(1, 5):
    avg = pd.read_csv('01_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Selection rate others 0.1')
plt.show()

#################

for k in range(1, 5):
    avg = pd.read_csv('03_'+ str(k) + '_stats.csv')["Average fitnesses"]
    plt.plot(avg, label=k)

plt.legend()
plt.grid()
plt.xlabel('generation')
plt.ylabel('average final score')
plt.title('Selection rate others 0.3')
plt.show()

#################

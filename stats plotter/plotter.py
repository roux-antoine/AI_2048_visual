
# import math
# import copy
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


stats = pd.read_csv("titi.csv")


print(stats)
print(stats.columns)

plt.plot(stats["Best fitnesses"])
plt.plot(stats["Average fitnesses"])
plt.show()


# import math
# import copy
import matplotlib.pyplot as plt
import numpy as np

def decipher(filename):
    currentFile = open(filename, "r")
    count = 0
    for line in currentFile:
        if count == 0 or count == 2 or count== 3 :
            count += 1
        elif count == 1 :
            maxFitnessesStr = [ x for x in line.split(" ") ]
            maxFitnessesStr.pop()
            maxFitnesses = []
            for k in maxFitnessesStr :
                maxFitnesses.append(int(k))
            count+=1

        elif count == 4 :
            avgFitnessesStr = [ x for x in line.split(" ") ]
            avgFitnessesStr.pop()
            avgFitnesses = []
            for k in avgFitnessesStr :
                avgFitnesses.append(int(k))
            count+=1

    currentFile.close()
    return maxFitnesses, avgFitnesses

###########################################################################


if __name__ == '__main__':
    [maxFitnesses, avgFitnesses] = decipher("1.txt")

    generations = np.linspace(1, len(maxFitnesses), len(maxFitnesses))
    plt.plot(generations, maxFitnesses)
    plt.plot(generations, avgFitnesses)
    plt.grid()
    plt.show()

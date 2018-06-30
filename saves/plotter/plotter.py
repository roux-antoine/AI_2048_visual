
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

    nbrV1 = 7
    nbrV2 = 5

    maxFitnessesV1 = []
    avgFitnessesV1 = []
    for k in range (1, nbrV1 + 1):
        [a, b] = decipher("v1_" + str(k) +".txt")
        maxFitnessesV1.append(a)
        avgFitnessesV1.append(b)

    avgMaxFitnessesV1 = []
    avgAvgFitnessesV1 = []

    for k in range(len(maxFitnessesV1[0])) :
        avgMaxFitnessesV1.append(0)
        avgAvgFitnessesV1.append(0)
        for i in range(0, nbrV1) :
            avgMaxFitnessesV1[k] += maxFitnessesV1[i][k] / nbrV1
            avgAvgFitnessesV1[k] += avgFitnessesV1[i][k] / nbrV1

    maxFitnessesV2 = []
    avgFitnessesV2 = []
    for k in range (1, nbrV2 + 1):
        [a, b] = decipher("v2_" + str(k) +".txt")
        maxFitnessesV2.append(a)
        avgFitnessesV2.append(b)

    avgMaxFitnessesV2 = []
    avgAvgFitnessesV2 = []

    for k in range(len(maxFitnessesV1[0])) :
        avgMaxFitnessesV2.append(0)
        avgAvgFitnessesV2.append(0)
        for i in range(0, nbrV2) :
            avgMaxFitnessesV2[k] += maxFitnessesV2[i][k] / nbrV2
            avgAvgFitnessesV2[k] += avgFitnessesV2[i][k] / nbrV2


    generations = np.linspace(1, len(maxFitnessesV1[0]), len(maxFitnessesV1[0]))


    plt.figure()
    plt.plot(generations, maxFitnessesV1[0], 'b', label = 'maxFitness')
    plt.plot(generations, avgFitnessesV1[0], 'r', label = 'avgFitness')
    for k in range(1, nbrV1):
        plt.plot(generations, maxFitnessesV1[k], 'b')
        plt.plot(generations, avgFitnessesV1[k], 'r')
    plt.grid()
    plt.title("version 1 (without bias)")
    plt.xlabel("generations")
    plt.ylabel("fitness")
    plt.legend()


    plt.figure()
    plt.plot(generations, maxFitnessesV2[0], 'b', label = 'maxFitness')
    plt.plot(generations, avgFitnessesV2[0], 'r', label = 'avgFitness')
    for k in range(1, nbrV2):
        plt.plot(generations, maxFitnessesV2[k], 'b')
        plt.plot(generations, avgFitnessesV2[k], 'r')
    plt.grid()
    plt.title("version 2 (with bias)")
    plt.xlabel("generations")
    plt.ylabel("fitness")
    plt.legend()

    plt.figure()
    plt.plot(generations, avgMaxFitnessesV1, 'g', label = 'maxFitness v1')
    plt.plot(generations, avgAvgFitnessesV1, 'g', label = 'avgFitness v1')
    plt.plot(generations, avgMaxFitnessesV2, 'k', label = 'maxFitness v2')
    plt.plot(generations, avgAvgFitnessesV2, 'k', label = 'avgFitness v2')
    plt.grid()
    plt.title("version 1 and 2")
    plt.xlabel("generations")
    plt.ylabel("fitness")
    plt.legend()


    plt.show()

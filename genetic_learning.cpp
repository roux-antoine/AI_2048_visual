#include <iostream>
#include <vector>
#include <math.h>

#include "learning.hpp"
#include "ia.hpp"

class GeneticLearning : public Learning {
private:
  std::vector<IA> generation;
  std::vector<float> fitnesses;
  int nbGeneration;
  int nbIndiv;
  int nbEvalPerIndiv;
  double selectionRate;
  double selectionOthers;
  double mutationProba;

public:
  GeneticLearning() {
    nbGeneration = 10;
    nbIndiv = 10;
    nbEvalPerIndiv = 5;
    selectionRate = 0.3;
    selectionOthers = 0.2;
    mutationProba = 0.01;
  }
  GeneticLearning(int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP) {
    nbGeneration = nbG;
    nbIndiv = nbI;
    nbEvalPerIndiv = nbE;
    selectionRate = selectionR;
    selectionOthers = selectionO;
    mutationProba = mutationP;
  }
  void execute() {
    IA indiv;
    for (int i=0; i<nbIndiv; i++) {
      indiv = IA();
      generation.push_back(indiv);
      fitnesses.push_back(0);
    }
    generationCounter = 0;
    while (generationCounter < nbGeneration) {
      generationCounter += 1;
      std::cout << generationCounter;

    /*# if generationCounter < 5 :
    #     selectionRate = 0.5
    # elif generationCounter < 10:
    #     selectionRate = 0.35
    # else :
    #     selectionRate = 0.2*/

    this.evalutation();
    indexes = myGeneration.select(selectionRate, 0)
    print(indexes)
    print(sum(myGeneration.fitnesses)/nbrOfIndividuals)
    myGeneration.fitnesses = []

    myGeneration.reproduce(indexes)
    text_file = open("Output.txt", "w")
    string = ""
    for k in range(nbrOfIndividuals) :
    for i in range(4) :
    for j in range(4) :
    string += str(myGeneration.individuals[k].fitnessGrid[i][j]) + " "
    string += "\n"
    string += "\n"
  }
  }
  int evalutation() {
    int currentFitness;
    for (int k=0 ; k<sizeOfPopulation ; k++) {
      currentFitness = 0;
      for (int i=0 ; i<nbEvalPerIndiv ; i++) {
        finishedGrid = single_AI(self.individuals[k].grid, self.individuals[k].fitnessGrid) // TODO
        currentFitness += sum(sum(finishedGrid))
      }
      fitnesses.push_back(math::trunc(currentFitness / nbEvalPerIndiv)); // score moyen
    }
  }
  void selection() {
    //assert proportionOfBest + proportionOfOthers < 1

        int nbrOfBest = math::trunc(nbIndiv * selectionRate);
        int nbrOfOthers = math::trunc(nbIndiv * selectionOthers);
        std::vector<int> indexes;

        std::vector<int> listOfFitnesses = fitnesses;

        int currentMaxIndex;
        for (int k=0 ; k<nbrOfBest ; k++) {
          currentMaxIndex = maxIndex(listOfFitnesses);
          indexes.push_back(currentMaxIndex);
          listOfFitnesses[currentMaxIndex] = 0;
        }


        for (int k=0 ; k<nbrOfOthers ; k++) {
            randomlySelected = random.randint(0, self.sizeOfPopulation-1)
            while randomlySelected in indexes : #if already one of the best, try again
                randomlySelected = random.randint(0, self.sizeOfPopulation-1)
            indexes.append(randomlySelected)
          }

        #we delete the individuals not selected
        for k in range(self.sizeOfPopulation) :
            if k not in indexes :
                self.individuals[k] = 0

        return(indexes)
  }
  void reproduction() {
    """ The reproduction phase
            indexes = indexes of the selected
            At the moment : randomly mates the selected to fill up the blanks -> TROP VIOLENT ??
            Doesnt return anything
        """
        assert len(indexes) >= 2

        numberOfMissing = self.sizeOfPopulation - len(indexes)
        indexesOfMissing = []
        for k in range(self.sizeOfPopulation) :
            if k not in indexes :
                indexesOfMissing.append(k)

        for k in indexesOfMissing :
            parent1 = random.choice(indexes)
            parent2 = random.choice(indexes)
            while (parent2 == parent1) :
                parent2 = random.choice(indexes)

            self.individuals[k] = Grid([[0, 0, 0, 0],
                                        [0, 0, 0, 0],
                                        [0, 0, 0, 0],
                                        [0, 0, 0, 0]] ,

                                          [[1, 0, 0, 0],
                                          [0, 0, 0, 0],
                                          [0, 0, 0, 0],
                                          [0, 0, 0, 0]])
            for i in range(4) :
                for j in range(4) :
                    self.individuals[k].fitnessGrid[i][j] = 0.5 * (self.individuals[parent1].fitnessGrid[i,j] + self.individuals[parent2].fitnessGrid[i,j])
  }
  void mutation() {
    for k in indexes :
            if random.randint(1, int(1/probability)) == 1 :
                #in this case we add a small noise to the grid, proportional to the tile values
                for i in range(4) :
                    for j in range(4) :
                        tileValue = self.individuals[k].grid[i,j]
                        self.individuals[k].fitnessGrid[i][j] += random.randint(-0.05 * tileValue, 0.05 * tileValue) #valeurs random....
  }
}

int index(std::vector<int> v, int value) {
  int idx;
  int flag = 0;
  if !(v.empty()) {
    int i=0;
    while ((i<v.size()) && (!flag)) {
      if (v[i] == value) {
        idx = i;
        flag = 1;
      }
      i++;
    }
  }
  if (flag) {return idx;}
  else {return -1;}
}

int maxIndex(std::vector<int> v) {
  int idx;
  int m = v[0];
  if !(v.empty()) {
    for (int i=0 ; i<v.size() ; i++) {
      if (v[i] > m) {
        m = v[i];
        idx = i;
      }
    }
    return idx;
  }
  else {return -1;}
}

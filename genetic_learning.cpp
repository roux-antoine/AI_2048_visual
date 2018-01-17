#include <iostream>
#include <vector>
#include <math.h>

#include "learning.hpp"
#include "AI.hpp"
#include "tools.cpp"

class GeneticLearning : public Learning {
private:
  std::vector<AI> generation;
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
    fitnesses.clear();
    generation.clear();

    AI indiv;
    for (int i=0; i<nbIndiv; i++) {
      indiv = AI();
      generation.push_back(indiv);
      fitnesses.push_back(0);
    }
    generationCounter = 0;
    while (generationCounter < nbGeneration) {
      generationCounter += 1;
      std::cout << generationCounter << std::endl;

      /* if generationCounter < 5 :
      selectionRate = 0.5
      elif generationCounter < 10:
      selectionRate = 0.35
      else :
      selectionRate = 0.2*/

      evalutation();
      indexes = *selection(selectionRate, 0);
      std::cout << indexes << std::endl;
      //print(sum(myGeneration.fitnesses)/nbrOfIndividuals)

      reproduction(indexes&);
      /*text_file = open("Output.txt", "w")
      string = ""
      for k in range(nbrOfIndividuals) :
      for i in range(4) :
      for j in range(4) :
      string += str(myGeneration.individuals[k].fitnessGrid[i][j]) + " "
      string += "\n"
      string += "\n"*/
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
  std::vector<int>& selection() {
    //assert proportionOfBest + proportionOfOthers < 1

    int nbrOfBest = math::trunc(nbIndiv * selectionRate);
    int nbrOfOthers = math::trunc(nbIndiv * selectionOthers);
    std::vector<int> indexes;

    std::vector<int> listOfFitnesses = fitnesses;

    int currentMaxIndex;
    for (int k=0 ; k<nbrOfBest ; k++) {
      currentMaxIndex = maxIndex(listOfFitnesses&);
      indexes.push_back(currentMaxIndex);
      listOfFitnesses[currentMaxIndex] = 0;
    }

    int randomlySelected;
    for (int k=0 ; k<nbrOfOthers ; k++) {
      randomlySelected = my_random(0, nbIndiv-1);
      while (index(indexes&,randomlySelected) != -1 ) {
        //if already one of the best, try again
        randomlySelected = my_random(0, nbIndiv-1);
      }
      indexes.push_back(randomlySelected);
    }

    // we delete the individuals not selected
    for (int k=0 ; k<nbIndiv ; k++) {
      if (index(indexes&, k) == -1) {
        generation[k] = null;
      }
    }

    return indexes&;
  }
  void reproduction(std::vector<int>& indexes) {
    """ The reproduction phase
    indexes = indexes of the selected
    At the moment : randomly mates the selected to fill up the blanks -> TROP VIOLENT ??
    Doesnt return anything
    """
    //assert len(indexes) >= 2

    int numberOfMissing = nbIndiv - indexes->size();
    std::vector<int> indexesOfMissing;
    for (int k=0 ; k<nbIndiv ; k++) {
      if (index(indexes, k) == -1) {
        // if k is not indexes
        indexesOfMissing.push_back(k);
      }
    }

    int k;
    int parent1;
    int parent2;
    for (int idx=0 ; idx<indexesOfMissing.size() ; idx++) {
      k = indexes[idx];
      parent1 = indexes[my_random(0, indexes.size()-1)];
      parent2 = indexes[my_random(0, indexes.size()-1)];


      while (parent2 == parent1) {
        parent2 = indexes[my_random(0, indexes.size()-1)];
      }

      for (int i=0 ; i<generation[k].gridDimension ; i++) {
        for (int j=0 ; j<generation[k].gridDimension ; j++) {
          generation[k].fitnessGrid[i][j] = 0.5 * (generation[parent1].fitnessGrid[i][j] + generation[parent2].fitnessGrid[i][j]);
        }
      }
    }
  }

  void mutation(std::vector<int>& indexes) {
    int k;
    for (int idx=0 ; idx<indexes.size() ; idx++) {
      if (my_random(1, math::trunc(1/mutationProba)) == 1) {
        //in this case we add a small noise to the grid, proportional to the tile values
        for (int i=0 ; i<generation[k].gridDimension ; i++) {
          for (int j=0 ; j<generation[k].gridDimension ; j++) {
            generation[k].fitnessGrid[i][j] += 0.05 * my_random(-1,1) * generation[k].fitnessGrid[i][j]; //valeurs random....
          }
        }
      }
    }
  }
}

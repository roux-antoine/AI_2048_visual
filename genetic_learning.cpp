#include <iostream>
#include <vector>
#include <math.h>

#include "genetic_learning.hpp"

GeneticLearning::GeneticLearning() {
  nbGeneration = 10;
  nbIndiv = 10;
  nbEvalPerIndiv = 5;
  selectionRate = 0.3;
  selectionOthers = 0.2;
  mutationProba = 0.01;
}

GeneticLearning::GeneticLearning(int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP) {
  nbGeneration = nbG;
  nbIndiv = nbI;
  nbEvalPerIndiv = nbE;
  selectionRate = selectionR;
  selectionOthers = selectionO;
  mutationProba = mutationP;
}

void GeneticLearning::execute() {
  fitnesses.clear();
  generation.clear();

  AI indiv;
  for (int i=0; i<nbIndiv; i++) {
    indiv = AI();
    generation.push_back(indiv);
    fitnesses.push_back(0);
  }
  int generationCounter = 0;
  while (generationCounter < nbGeneration) {
    generationCounter += 1;
    std::cout << generationCounter << std::endl;

    /* if generationCounter < 5 :
    selectionRate = 0.5
    elif generationCounter < 10:
    selectionRate = 0.35
    else :
    selectionRate = 0.2*/
    std::cout << "evalutation" << std::endl;
    evalutation();
    std::cout << "selection" << std::endl;
    std::vector<int>* indexes = selection();
    //std::cout << *indexes << std::endl;
    //print(sum(myGeneration.fitnesses)/nbrOfIndividuals)

    std::cout << "reproduction" << std::endl;
    reproduction(indexes);
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

void GeneticLearning::evalutation() {
  int currentFitness;
  for (int k=0 ; k<nbIndiv ; k++) {
    currentFitness = 0;
    for (int i=0 ; i<nbEvalPerIndiv ; i++) {
      Game_AI game(generation[k].gridDimension, generation[k]);
      currentFitness += double_sum(game.grid);
    }
    fitnesses.push_back(trunc(currentFitness / nbEvalPerIndiv)); // score moyen
  }
}

std::vector<int>* GeneticLearning::selection() {
  //assert proportionOfBest + proportionOfOthers < 1
  std::cout << "definitions" << std::endl;
  int nbrOfBest = trunc(nbIndiv * selectionRate);
  int nbrOfOthers = trunc(nbIndiv * selectionOthers);
  std::vector<int>* indexes;

  std::vector<int> listOfFitnesses = fitnesses;
  std::cout << "selection des meilleurs" << std::endl;
  int currentMaxIndex;
  for (int k=0 ; k<nbrOfBest ; k++) {
    currentMaxIndex = max_index(&listOfFitnesses);
    indexes->push_back(currentMaxIndex);
    listOfFitnesses[currentMaxIndex] = 0;
  }
  std::cout << "selection aléatoire" << std::endl;
  int randomlySelected;
  for (int k=0 ; k<nbrOfOthers ; k++) {
    randomlySelected = my_random(0, nbIndiv-1);
    while (index(indexes,randomlySelected) != -1 ) {
      //if already one of the best, try again
      randomlySelected = my_random(0, nbIndiv-1);
    }
    indexes->push_back(randomlySelected);
  }
  std::cout << "suppression des non selectionnes" << std::endl;
  // we delete the individuals not selected
  for (int k=0 ; k<nbIndiv ; k++) {
    if (index(indexes, k) == -1) {
      generation.erase(generation.begin() + k); // to have an iterator
    }
  }

  return indexes;
}

void GeneticLearning::reproduction(std::vector<int>* indexes) {
  /*  The reproduction phase
  indexes = indexes of the selected
  At the moment : randomly mates the selected to fill up the blanks -> TROP VIOLENT ??
  Doesnt return anything
  """*/
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
    k = indexes->at(idx);
    parent1 = indexes->at(my_random(0, indexes->size()-1));
    parent2 = indexes->at(my_random(0, indexes->size()-1));


    while (parent2 == parent1) {
      parent2 = indexes->at(my_random(0, indexes->size()-1));
    }

    for (int i=0 ; i<generation[k].gridDimension ; i++) {
      for (int j=0 ; j<generation[k].gridDimension ; j++) {
        generation[k].fitnessGrid[i][j] = trunc(0.5 * (generation[parent1].fitnessGrid[i][j] + generation[parent2].fitnessGrid[i][j]));
      }
    }
  }
}

void GeneticLearning::mutation(std::vector<int>* indexes) {
  int k;
  for (int idx=0 ; idx<indexes->size() ; idx++) {
    if (my_random(1, trunc(1/mutationProba)) == 1) {
      //in this case we add a small noise to the grid, proportional to the tile values
      for (int i=0 ; i<generation[k].gridDimension ; i++) {
        for (int j=0 ; j<generation[k].gridDimension ; j++) {
          generation[k].fitnessGrid[i][j] += 0.05 * my_random(-1,1) * generation[k].fitnessGrid[i][j]; //valeurs random....
        }
      }
    }
  }
}

AI GeneticLearning::get_best_AI() {
  return generation[max_index(&fitnesses)];
}

int GeneticLearning::get_best_fitness() {
  return fitnesses[max_index(&fitnesses)];
}

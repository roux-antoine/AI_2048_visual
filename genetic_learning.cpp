#include <iostream>
#include <vector>
#include <math.h>

#include "genetic_learning.hpp"

GeneticLearning::GeneticLearning() {
  nbGeneration = 10;
  nbIndiv = 10;
  nbEvalPerIndiv = 30;
  selectionRate = 0.3;
  selectionOthers = 0.0;
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
    indiv = AI(); //il faut remplacer par AI_random -> mais il faut coder AI_random
    generation.push_back(indiv);
    fitnesses.push_back(0);
  }
  int generationCounter = 0;
  while (generationCounter < nbGeneration) {
    generationCounter += 1;
    std::cout << "\nGeneration : " << generationCounter << std::endl;

    std::cout << "   Evaluation" << std::endl;
    evalutation();
    std::cout << "   Selection" << std::endl;
    std::vector<int> indexes = selection(); //indexes is a vector of the numbers of the selected ones

    std::cout << "   Reproduction" << std::endl;
    reproduction(indexes);

    std::cout << "   Mutation" << std::endl;
    mutation();

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

      game.play();

      currentFitness += double_sum(game.grid);
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // score moyen
  }

  int avgFitness = 0;
  for (size_t i = 0; i < nbIndiv; i++) {
    avgFitness += fitnesses[i];
  }
  printf("      avgFitness: %d\n", avgFitness/nbIndiv);

}

std::vector<int> GeneticLearning::selection() {
  //assert proportionOfBest + proportionOfOthers < 1
  // std::cout << "      Definitions" << std::endl;
  int nbrOfBest = trunc(nbIndiv * selectionRate);
  int nbrOfOthers = trunc(nbIndiv * selectionOthers);
  std::vector<int> indexes;

  std::vector<int> listOfFitnesses = fitnesses;

  // std::cout << "      Selection des meilleurs" << std::endl;
  int currentMaxIndex;
  // printf("nbrOfBest : %d\n", nbrOfBest);
  for (int k=0 ; k<nbrOfBest ; k++)
  {
    currentMaxIndex = max_index(listOfFitnesses);
    // printf("current max index %d\n", currentMaxIndex);
    //il faudrait mettre qqch du genre : assert currentMaxIndex < size
    indexes.push_back(currentMaxIndex);
    listOfFitnesses[currentMaxIndex] = 0;
  }

  // std::cout << "      Selection aléatoire" << std::endl;
  int randomlySelected;
  // printf("nbrOfOthers : %d\n", nbrOfOthers);

  for (int k=0 ; k<nbrOfOthers ; k++) {
    randomlySelected = my_random(0, nbIndiv-1);

    while (index(indexes,randomlySelected) != -1 ) {
      //if already one of the best, try again
      randomlySelected = my_random(0, nbIndiv-1);
    }
    indexes.push_back(randomlySelected);
  }
  // C'EST PEUT ETRE PAS LA PEINE DE SUPPRIMER LES NULS, ON REECRIT JUSTE PAR DESSUS DANS LA REPORDUCTION
  // std::cout << "suppression des non selectionnes" << std::endl;
  // // we delete the individuals not selected
  //
  // for (size_t i = 0; i < indexes.size(); i++) {
  //   printf("%d\n", indexes[i]);
  // }
  //
  // for (int k=0 ; k<nbIndiv ; k++) {
  //   if (index(indexes, k) == -1)
  //   //if the individual k is not in the selected ones, we remove it from the generation
  //   {
  //     printf("passage numéro : %d\n", k);
  //     printf("taille de generation : %lu\n", generation.size());
  //     generation.erase(generation.begin() + k); // to have an iterator
  //     //ca segfault probablement car la taille du vecteur diminue lorsqu'on commence à en retirer
  //   }
  // }
  // printf("tout va bien\n" );
  return indexes;
}

void GeneticLearning::reproduction(std::vector<int> indexes) {
  /*  The reproduction phase
  indexes = indexes of the selected
  At the moment : randomly mates the selected to fill up the blanks -> TROP VIOLENT ??
  Doesnt return anything
  */
  //assert len(indexes) >= 2

  int indexesSize = indexes.size();
  int numberOfMissing = nbIndiv - indexesSize;
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
    k = indexesOfMissing.at(idx);
    parent1 = indexes.at(my_random(0, indexesSize-1));
    parent2 = indexes.at(my_random(0, indexesSize-1));

    while (parent2 == parent1) {
      parent2 = indexes.at(my_random(0, indexesSize-1));
    }

    for (int i=0 ; i<generation[k].gridDimension ; i++) {
      for (int j=0 ; j<generation[k].gridDimension ; j++) {
        generation[k].fitnessGrid[i][j] = trunc(0.5 * (generation[parent1].fitnessGrid[i][j] + generation[parent2].fitnessGrid[i][j]));
      }
    }
  }
}

void GeneticLearning::mutation() {
  int k;
  for (int idx=0 ; idx< nbIndiv ; idx++) {
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

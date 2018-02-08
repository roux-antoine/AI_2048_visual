
#include "Genetic_learning.hpp"

GeneticLearning::GeneticLearning()
{
  gridSize =4;
  nbGeneration = 15;
  nbIndiv = 25;
  nbEvalPerIndiv = 30;
  selectionRateBest = 0.3;
  selectionRateOthers = 0.1;
  mutationProba = 0.05;
  nbrOfThreads = 2;

}

GeneticLearning::GeneticLearning(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfT)
{
  gridSize = gridS;
  nbGeneration = nbG;
  nbIndiv = nbI;
  nbEvalPerIndiv = nbE;
  selectionRateBest = selectionR;
  selectionRateOthers = selectionO;
  mutationProba = mutationP;
  nbrOfThreads = nbrOfT;
}


void GeneticLearning::execute(Learning_stats* stats)
{
  fitnesses.clear();
  generation.clear();

  AI_random indiv;
  for (int i=0; i<nbIndiv; i++)
  {
    indiv = AI_random(gridSize);
    generation.push_back(indiv);
    fitnesses.push_back(0);
  }
  int generationCounter = 0;
  while (generationCounter < nbGeneration)
  {
    generationCounter += 1;
    std::cout << "\nGeneration : " << generationCounter << std::endl;

    std::cout << "   Evaluation" << std::endl;
    //we choose the method to evaluate the individuals
    if (nbrOfThreads > 0)
    {
      evaluation_thread(nbrOfThreads);
    }
    else
    {
      evaluation();
    }

    std::cout << "  (Saving stats)" << std::endl;
    stats->appendBestFitness(getBestFitness());
    stats->appendAverageFitness(getAverageFitness());
    stats->appendBestFitnessGrids(getBestAI().fitnessGrid);

    std::cout << "   Selection" << std::endl;
    std::vector<int> indexes = selection(); //indexes is a vector of the numbers of the selected ones

    std::cout << "   Reproduction" << std::endl;
    reproduction(indexes);

    std::cout << "   Mutation" << std::endl;
    mutation();

  }
  stats->writeToFile();
}


void GeneticLearning::evaluation_thread(int nbrOfThreads)
/*
  Function that creates nbrOfThreads threads, that individually calls evaluation_base
*/
{
  //we compute the positions of the cuts (aka the limits of each sub-fitness array)
  int cutsPositions[nbrOfThreads+1]; //attention, il n'est pas de taille nbrOfThreads
  cutsPositions[0] = 0;
  cutsPositions[nbrOfThreads] = nbIndiv;
  for (int i = 1; i < nbrOfThreads; i++)
  {
    cutsPositions[i] = cutsPositions[i-1] + round(((float)nbIndiv - cutsPositions[i-1])/(nbrOfThreads-i+1));
  }

  //we create the array of threads
  std::vector<std::thread> threadsVector(nbrOfThreads);

  for (int i = 0; i < nbrOfThreads-1; i++)
  {
    threadsVector[i] = std::thread (&GeneticLearning::evaluation_thread_base, this, i, cutsPositions[i], cutsPositions[i+1]);
  }
  threadsVector[nbrOfThreads-1] = std::thread (&GeneticLearning::evaluation_thread_base, this, nbrOfThreads-1, cutsPositions[nbrOfThreads-1], cutsPositions[nbrOfThreads]);

  // we wait for the threads to end
  for (int i = 0; i < nbrOfThreads; i++)
  {
    threadsVector[i].join();
  }

}


void GeneticLearning::evaluation_thread_base (int threadNbr, int start, int end)
{
  // printf("      Thread %d started - individuals %d to %d\n", threadNbr, start, end);
  int currentFitness = 0;
  for (int k=start ; k<end ; k++)
  {
    currentFitness = 0;
    for (int i=0 ; i<nbEvalPerIndiv ; i++)
    {
      Game_AI game(generation[k].gridDimension, generation[k]);

      game.play();

      currentFitness += double_sum(game.grid);
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // score moyen
  }

  int avgFitness = 0;
  for (int i = start; i < end; i++)
  {
    avgFitness += fitnesses[i];
  }
  // printf("      avgFitness (thread %d): %d\n", threadNbr, avgFitness/(end-start));

}

void GeneticLearning::evaluation()
{
  int currentFitness;
  for (int k=0 ; k<nbIndiv ; k++)
  {
    currentFitness = 0;
    for (int i=0 ; i<nbEvalPerIndiv ; i++)
    {
      Game_AI game(generation[k].gridDimension, generation[k]);

      game.play();

      currentFitness += double_sum(game.grid);
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // score moyen
  }

  int avgFitness = 0;
  for (int i = 0; i < nbIndiv; i++)
  {
    avgFitness += fitnesses[i];
  }
  printf("      avgFitness: %d\n", avgFitness/nbIndiv);

}

std::vector<int> GeneticLearning::selection()
{
  //assert proportionOfBest + proportionOfOthers < 1
  // std::cout << "      Definitions" << std::endl;
  int nbrOfBest = trunc(nbIndiv * selectionRateBest);
  int nbrOfOthers = trunc(nbIndiv * selectionRateOthers);
  std::vector<int> indexes;

  std::vector<int> listOfFitnesses = fitnesses;

  // std::cout << "      Selection des meilleurs" << std::endl;
  int currentMaxIndex;
  // printf("nbrOfBest : %d\n", nbrOfBest);
  for (int k=0 ; k<nbrOfBest ; k++)
  {
    currentMaxIndex = max_index(listOfFitnesses);
    if (currentMaxIndex >= nbIndiv)
    {
        printf("index supérieur à la taille :/ \n");
    }
    // printf("current max index %d\n", currentMaxIndex);
    //il faudrait mettre qqch du genre : assert currentMaxIndex < size
    indexes.push_back(currentMaxIndex);
    listOfFitnesses[currentMaxIndex] = 0;
  }

  // std::cout << "      Selection aléatoire" << std::endl;
  int randomlySelected;
  // printf("nbrOfOthers : %d\n", nbrOfOthers);

  for (int k=0 ; k<nbrOfOthers ; k++)
  {
    randomlySelected = my_random(0, nbIndiv-1);

    while (index(indexes,randomlySelected) != -1 )
    {
      //if already one of the best, try again
      randomlySelected = my_random(0, nbIndiv-1);
    }
    indexes.push_back(randomlySelected);
  }
  //on ne supprime pas les individus non selectionnés, on réécrira juste par dessus dans reproduction
  return indexes;
}

void GeneticLearning::reproduction(std::vector<int> indexes)
{
  /*  The reproduction phase
  indexes = indexes of the selected
  At the moment : randomly mates the selected to fill up the blanks -> TROP VIOLENT ??
  Doesnt return anything
  */
  //assert len(indexes) >= 2

  int indexesSize = indexes.size();
  std::vector<int> indexesOfMissing;
  for (int k=0 ; k<nbIndiv ; k++)
  {
    if (index(indexes, k) == -1)
    {
      // if k is not indexes
      indexesOfMissing.push_back(k);
    }
  }

  int k;
  int parent1;
  int parent2;
  for (int idx = 0 ; idx < (int)indexesOfMissing.size() ; idx++)
  {
    k = indexesOfMissing.at(idx);
    parent1 = indexes.at(my_random(0, indexesSize-1));
    parent2 = indexes.at(my_random(0, indexesSize-1));

    while (parent2 == parent1)
    {
      parent2 = indexes.at(my_random(0, indexesSize-1));
    }

    for (int i=0 ; i<generation[k].gridDimension ; i++)
    {
      for (int j=0 ; j<generation[k].gridDimension ; j++)
      {
        generation[k].fitnessGrid[i][j] = trunc(0.5 * (generation[parent1].fitnessGrid[i][j] + generation[parent2].fitnessGrid[i][j]));
      }
    }
  }
}

void GeneticLearning::mutation()
{
  for (int k=0 ; k< nbIndiv ; k++)
  {
    if (my_random(1, trunc(1/mutationProba)) == 1)
    {
      //in this case we add a small noise to the grid, proportional to the tile values
      for (int i=0 ; i<generation[k].gridDimension ; i++)
      {
        for (int j=0 ; j<generation[k].gridDimension ; j++)
        {
          generation[k].fitnessGrid[i][j] += 0.05 * my_random(-1,1) * generation[k].fitnessGrid[i][j]; //valeurs random....
        }
      }
    }
  }
}

AI GeneticLearning::getBestAI()
{
  return generation[max_index(&fitnesses)];
}

int GeneticLearning::getBestFitness()
{
  return fitnesses[max_index(&fitnesses)];
}

int GeneticLearning::getAverageFitness()
{
  int avgFitness = 0;
  for (int i = 0; i < nbGeneration; i++)
  {
    avgFitness += fitnesses[i];
  }
  return(avgFitness/nbGeneration);
}

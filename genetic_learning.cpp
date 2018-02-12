
#include "Genetic_learning.hpp"

GeneticLearning::GeneticLearning()
{
  gridSize =4;
  nbGenerations = 15;
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
  nbGenerations = nbG;
  nbIndiv = nbI;
  nbEvalPerIndiv = nbE;
  selectionRateBest = selectionR;
  selectionRateOthers = selectionO;
  mutationProba = mutationP;
  nbrOfThreads = nbrOfT;
}


void GeneticLearning::execute(Learning_stats* stats)
//executes the whole learning phase
//creates generations of nbIndiv algorithms
//evaluates them on nbEvalPerIndiv games
//selectes the best
//mutates
//loops
//and at the end, save stats in a txt file
{
  //we get the time tag to save the stats
  auto start = std::chrono::system_clock::now();
  std::time_t timeNow = std::chrono::system_clock::to_time_t(start);
  char fileName[100];   // array to hold the result.
  strcpy(fileName, std::ctime(&timeNow));
  strcat(fileName, ".txt");

  //we initialize all the variables
  fitnesses.clear();
  generation.clear();

  AI_random indiv;
  for (int i=0; i<nbIndiv; i++)
  {
    indiv = AI_random(gridSize);
    generation.push_back(indiv);
    fitnesses.push_back(0);
  }
  //we launch the learning phase
  int generationCounter = 0;
  while (generationCounter < nbGenerations)
  {
    generationCounter += 1;
    std::cout << "\nGeneration : " << generationCounter << std::endl;

    std::cout << "   Evaluation" << std::endl;
    //we choose the method to evaluate the individuals
    if (nbrOfThreads > 0)
    {
      evaluationThreaded(nbrOfThreads);
    }
    else
    {
      evaluationNonThreaded();
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

    stats->writeToFile(fileName);

  }

}


void GeneticLearning::evaluationThreaded(int nbrOfThreads)
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
    threadsVector[i] = std::thread (&GeneticLearning::evaluationThreadBase, this, i, cutsPositions[i], cutsPositions[i+1]);
  }
  threadsVector[nbrOfThreads-1] = std::thread (&GeneticLearning::evaluationThreadBase, this, nbrOfThreads-1, cutsPositions[nbrOfThreads-1], cutsPositions[nbrOfThreads]);

  // we wait for the threads to end
  for (int i = 0; i < nbrOfThreads; i++)
  {
    threadsVector[i].join();
  }
}


void GeneticLearning::evaluationThreadBase (int threadNbr, int start, int end)
// function that evaluates individuals between start and end
// modifies the vector fitnesses
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

void GeneticLearning::evaluationNonThreaded()
//evaluates all the generations without multithreading
// modifies the vector fitnesses
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
//selects selectionRateBest best individuals
//and also selectionRateOthers non-best individuals
{
  //assert proportionOfBest + proportionOfOthers < 1
  // std::cout << "      Definitions" << std::endl;
  int nbrOfBest = trunc(nbIndiv * selectionRateBest);
  int nbrOfOthers = trunc(nbIndiv * selectionRateOthers);
  std::vector<int> indexes;

  std::vector<int> listOfFitnesses = fitnesses;

  // std::cout << "      Selection des meilleurs" << std::endl;
  int currentMaxIndex;
  for (int k=0 ; k<nbrOfBest ; k++)
  {
    currentMaxIndex = max_index(listOfFitnesses);
    if (currentMaxIndex >= nbIndiv)
    {
        printf("index supérieur à la taille :/ \n");
    }
    //il faudrait mettre qqch du genre : assert currentMaxIndex < size
    indexes.push_back(currentMaxIndex);
    listOfFitnesses[currentMaxIndex] = 0;
  }

  // std::cout << "      Selection aléatoire" << std::endl;
  int randomlySelected;

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
/*  The reproduction phase
indexes = indexes of the selected
At the moment : randomly mates the selected to fill up the blanks -> TROP VIOLENT ??
Doesnt return anything
*/
{
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
//mutates the individuals, by adding a small noise (positive or negative), with probability mutationProba
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
//returns the best AI
{
  return generation[max_index(&fitnesses)];
}

int GeneticLearning::getBestFitness()
//returns the best fitness
{
  return fitnesses[max_index(&fitnesses)];
}

int GeneticLearning::getAverageFitness()
//returns the average of the fitnesses
{
  int avgFitness = 0;
  for (int i = 0; i < nbGenerations; i++)
  {
    avgFitness += fitnesses[i];
  }
  return(avgFitness/nbGenerations);
}

#include "Genetic_learning.h"

Genetic_learning::Genetic_learning()
{
  gridSize = 4;
  nbGenerations = 15;
  nbIndiv = 25;
  nbEvalPerIndiv = 30;
  selectionRateBest = 0.3;
  selectionRateOthers = 0.1;
  mutationProba = 0.05;
  nbrOfThreads = 2;
  stopFlag = false;
}

Genetic_learning::Genetic_learning(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfT)
{
  gridSize = gridS;
  nbGenerations = nbG;
  nbIndiv = nbI;
  nbEvalPerIndiv = nbE;
  selectionRateBest = selectionR;
  selectionRateOthers = selectionO;
  mutationProba = mutationP;
  nbrOfThreads = nbrOfT;
  stopFlag = false;

  if (trunc(nbIndiv*selectionRateBest) < 1)
  //in that case, the selection phase fails -> we make the parameters compatible
  {
      nbIndiv = (int)(1/selectionRateBest);
  }
  if (nbrOfThreads > nbIndiv)
  {
      nbrOfThreads = nbIndiv;
  }
}


void Genetic_learning::execute(Learning_stats* stats)
// void Genetic_learning::execute()
/*
  executes the whole learning phase
  creates generations of nbIndiv algorithms
  evaluates them on nbEvalPerIndiv games
  selectes the best
  mutates
  loops
  and at the end, save stats in a txt file
*/
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
  while ((generationCounter < nbGenerations) && (!stopFlag))
  {
    generationCounter += 1;

    //we choose the method to evaluate the individuals (multithread or not)
    if (nbrOfThreads > 0)
    {
      evaluation_threaded(nbrOfThreads);
    }
    else
    {
      evaluation_non_threaded();
    }

    //we save the stats to a txt file
    stats->append_best_fitness(get_best_fitness());
    stats->append_average_fitness(get_average_fitness());
    stats->append_best_fitness_grids(get_best_AI().weightsGrid);

    std::vector<int> indexes = selection(); //indexes is a vector of the numbers of the chosen ones

    reproduction(indexes);

    mutation();

    stats->write_stats_to_file(fileName);
  }
}


void Genetic_learning::evaluation_threaded(int nbrOfThreads)
/*
  Function that creates nbrOfThreads threads, that individually calls evaluation_base
*/
{
  //we compute the positions of the cuts (aka the limits of each sub-fitness array)
  int cutsPositions[nbrOfThreads+1]; //warning : there are nbrOfThreads+1 cuts !
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
    threadsVector[i] = std::thread (&Genetic_learning::evaluation_thread_base, this, cutsPositions[i], cutsPositions[i+1]);
  }
  threadsVector[nbrOfThreads-1] = std::thread (&Genetic_learning::evaluation_thread_base, this, cutsPositions[nbrOfThreads-1], cutsPositions[nbrOfThreads]);

  // we wait for the threads to end
  for (int i = 0; i < nbrOfThreads; i++)
  {
    threadsVector[i].join();
  }
}


void Genetic_learning::evaluation_thread_base (int start, int end)
/*
  function that evaluates individuals between start and end
  modifies the vector fitnesses
*/
{
  int currentFitness = 0;
  for (int k=start ; k<end ; k++)
  {
    currentFitness = 0;
    for (int i=0 ; i<nbEvalPerIndiv ; i++)
    //each individual is evaluated of nbEvalPerIndiv games -> to have a accurate measure of performance
    {
      Game_AI game(generation[k].get_grid_dimension(), generation[k]);

      game.play();

      currentFitness += double_sum(game.grid);
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // average score of the individual
  }

  int avgFitness = 0;
  for (int i = start; i < end; i++)
  {
    avgFitness += fitnesses[i];
  }
}

void Genetic_learning::evaluation_non_threaded()
/*
  evaluates all the generations without multithreading
  modifies the vector fitnesses
*/
{
  int currentFitness;
  for (int k=0 ; k<nbIndiv ; k++)
  {
    currentFitness = 0;
    for (int i=0 ; i<nbEvalPerIndiv ; i++)
    //each individual is evaluated of nbEvalPerIndiv games -> to have a accurate measure of performance
    {
      Game_AI game(generation[k].get_grid_dimension(), generation[k]);

      game.play();

      currentFitness += double_sum(game.grid);
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // average score of the individual
  }

  int avgFitness = 0;
  for (int i = 0; i < nbIndiv; i++)
  {
    avgFitness += fitnesses[i];
  }
}

std::vector<int> Genetic_learning::selection()
/*
  selects selectionRateBest best individuals
  and also selectionRateOthers non-best individuals
*/
{
  int nbrOfBest = trunc(nbIndiv * selectionRateBest);
  int nbrOfOthers = trunc(nbIndiv * selectionRateOthers);
  std::vector<int> indexes;

  std::vector<int> listOfFitnesses = fitnesses;

  int currentMaxIndex;
  for (int k=0 ; k<nbrOfBest ; k++)
  {
    currentMaxIndex = max_index(&listOfFitnesses);
    indexes.push_back(currentMaxIndex);
    listOfFitnesses[currentMaxIndex] = 0;
  }

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
  //There's no use in deleting the individuals not selected, we'll juste write over them later
  return indexes;
}

void Genetic_learning::reproduction(std::vector<int> indexes)
/*
  The reproduction phase
  indexes = indexes of the selected
  At the moment : randomly mates the selected ones to fill up the blanks -> maybe not optimum
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

    int gridDim = generation[k].get_grid_dimension();
    for (int i = 0; i < gridDim; i++)
    {
      for (int j = 0; j < gridDim; j++)
      {
        generation[k].weightsGrid[i][j] = trunc(0.5 * (generation[parent1].weightsGrid[i][j] + generation[parent2].weightsGrid[i][j]));
      }
    }
  }
}

void Genetic_learning::mutation()
/*
  mutates the individuals, by adding a small noise (positive or negative), with probability mutationProba
*/
{
  for (int k = 0; k < nbIndiv; k++)
  {
    if (my_random(1, trunc(1/mutationProba)) == 1)
    {
      //in this case we add a small noise to the grid, proportional to the tile values
      int gridDim = generation[k].get_grid_dimension();
      for (int i = 0; i < gridDim; i++)
      {
        for (int j = 0; j < gridDim; j++)
        {
          generation[k].weightsGrid[i][j] += 0.20 * my_random(-1,1) * generation[k].weightsGrid[i][j];
        }
      }
    }
  }
}

AI Genetic_learning::get_best_AI()
/*
  returns the best AI
*/
{
  return generation[max_index(&fitnesses)];
}

int Genetic_learning::get_best_fitness()
/*
  returns the best fitness
*/
{
  return fitnesses[max_index(&fitnesses)];
}

int Genetic_learning::get_average_fitness() const
/*
  returns the average of the fitnesses
*/
{
  int avgFitness = 0;
  int nbElem = (int)fitnesses.size();
  for (int i = 0; i < nbElem; i++)
  {
    avgFitness += fitnesses[i];
  }
  return(avgFitness/nbElem);
}

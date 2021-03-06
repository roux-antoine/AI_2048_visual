#include "Genetic_learning_neural.h"

Genetic_learning_neural::Genetic_learning_neural(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfT, int givenDepth, std::vector<int> nn_layersS, std::vector<int> nn_nonL)
/*
  Constructor that sets initializationMode to 0, so that the generation will be initialized with random neural nets
*/
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
  depth = givenDepth;
  nn_nbrLayers = nn_layersS.size();
  nn_layersSizes = nn_layersS;
  nn_nonLinearities = nn_nonL;
  initializationMode = 0;

  if (trunc(nbIndiv*selectionRateBest) < 1)
  //in that case, the selection phase fails -> we make the parameters compatible
  // TODO: does not seem to work
  {
      nbIndiv = (int)(1/selectionRateBest);
  }
  if (nbrOfThreads > nbIndiv)
  {
      nbrOfThreads = nbIndiv;
  }
}

Genetic_learning_neural::Genetic_learning_neural(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfT, int givenDepth)
/*
  Constructor that sets initializationMode to 1, so that the generation will be initialized with the usual hardcoded neural nets
*/
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
  depth = givenDepth;
  nn_nbrLayers = 2;
  nn_layersSizes = {16, 1};
  nn_nonLinearities = {0};
  initializationMode = 1;

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


void Genetic_learning_neural::execute(Learning_stats* stats)
/*
  executes the whole learning phase
  creates generations of nbIndiv algorithms
  evaluates them on nbEvalPerIndiv games
  selects the best
  reproduces
  mutates
  loops
  and at the end, save stats in a txt file
*/
{
  //we get the time tag to save the stats
  auto start = std::chrono::system_clock::now();
  std::time_t timeNow = std::chrono::system_clock::to_time_t(start);
  char statsFileName[100];   // array to hold the result.
  std::strcpy(statsFileName, std::ctime(&timeNow));
  for (int k = 0; k < 100; k++) //'cleaning' the filename
  {
    if (statsFileName[k] == ' ' || statsFileName[k] == '\n')
    {
      statsFileName[k] = '_';
    }
  }
  char configFileName[100];
  std::strcpy(configFileName, statsFileName);
  char resultFileName[100];
  std::strcpy(resultFileName, statsFileName);
  std::strcat(statsFileName, "stats.csv");
  std::strcat(configFileName, "config.txt");
  std::strcat(resultFileName, "result.txt");
  write_config_to_file(configFileName);

  //we initialize all the variables
  fitnesses.clear();
  generation.clear();

  // initializing the individuals in the generation with
  if (initializationMode == 0) //aka with random neural nets
  {
    for (int i=0; i<nbIndiv; i++)
    {
      generation.push_back(Neural_net(gridSize, nn_layersSizes, nn_nonLinearities));
      fitnesses.push_back(0);
    }
  }
  else //aka with the hardcoded neural net
  {
    for (int i=0; i<nbIndiv; i++)
    {
      generation.push_back(Neural_net());
      fitnesses.push_back(0);
    }
  }

  //we launch the learning phase
  int generationCounter = 0;
  while ((generationCounter < nbGenerations) && (!stopFlag))
  {
    generationCounter += 1;
    std::cout << BOLDBLACK << "Generation: " << generationCounter << "/" << nbGenerations << RESET << std::endl;
    // std::cout << "   Evaluation" << '\n';
    //we choose the method to evaluate the individuals (multithread or not)
    if (nbrOfThreads > 0)
    {
      evaluation_threaded(nbrOfThreads);
    }
    else
    {
      evaluation_non_threaded();
    }

    generation[max_index(&fitnesses)].save_to_file(resultFileName); //saving the best neural net to a file

    //we save the stats to a txt file
    stats->append_best_fitness(get_best_fitness());
    stats->append_average_fitness(get_average_fitness());

    play_N_games_and_print_best();

    // std::cout << "   Selection" << '\n';
    std::vector<int> indexes = selection(); //indexes is a vector of the numbers of the chosen ones
    // std::cout << "   Reproduction" << '\n';
    reproduction(indexes);
    // std::cout << "   Mutation" << '\n';
    mutation();

    stats->write_stats_to_file(statsFileName);
  }
}


void Genetic_learning_neural::evaluation_threaded(int nbrOfThreads)
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
    threadsVector[i] = std::thread(&Genetic_learning_neural::evaluation_thread_base, this, cutsPositions[i], cutsPositions[i+1]);
  }
  threadsVector[nbrOfThreads-1] = std::thread(&Genetic_learning_neural::evaluation_thread_base, this, cutsPositions[nbrOfThreads-1], cutsPositions[nbrOfThreads]);

  // we wait for the threads to end
  for (int i = 0; i < nbrOfThreads; i++)
  {
    threadsVector[i].join();
  }
}


void Genetic_learning_neural::evaluation_thread_base(int start, int end)
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
      Game_neural game(gridSize, depth, generation[k]);

      game.play();

      currentFitness += double_sum(game.grid); //we say that the best algos are the one that achieve the highest sum of the tiles at the end of the game
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // average score of the individual
  }

  int avgFitness = 0;
  for (int i = start; i < end; i++)
  {
    avgFitness += fitnesses[i];
  }
}

void Genetic_learning_neural::evaluation_non_threaded()
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
      Game_neural game(gridSize, depth, generation[k]);

      game.play();

      currentFitness += game.get_my_score();
    }
    fitnesses[k] = (int)trunc(currentFitness / nbEvalPerIndiv); // average score of the individual
  }

  int avgFitness = 0;
  for (int i = 0; i < nbIndiv; i++)
  {
    avgFitness += fitnesses[i];
  }
}

std::vector<int> Genetic_learning_neural::selection()
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

void Genetic_learning_neural::reproduction(std::vector<int> indexes)
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

    for (int m = 0; m < nn_nbrLayers-1; m++)
    {
      for (int i = 0; i < nn_layersSizes[m+1]; i++)
      {
        for (int j = 0; j < nn_layersSizes[m]; j++)
        {
          generation[k].weights[m][i][j] = 0.5 * (generation[parent1].weights[m][i][j] + generation[parent2].weights[m][i][j]);
        }
      }
    }

    for (int m = 0; m < nn_nbrLayers-1; m++)
    {
      for (int i = 0; i < nn_layersSizes[m+1]; i++)
      {
        // std::cout << m << " " << i << '\n';
        generation[k].biases[m][i] = 0.5 * (generation[parent1].biases[m][i] + generation[parent2].biases[m][i]);
      }
    }
  }
}

void Genetic_learning_neural::mutation()
/*
  mutates the individuals, by adding a small noise (positive or negative), with probability mutationProba
*/
{
  for (int k = 0; k < nbIndiv; k++)
  {
    if (my_random(1, trunc(1/mutationProba)) == 1)
    {
      // in this case we add a small noise to the grid, proportional to the tile values
      for (int m = 0; m < nn_nbrLayers-1; m++)
      {
        for (int i = 0; i < nn_layersSizes[m+1]; i++)
        {
          for (int j = 0; j < nn_layersSizes[m]; j++)
          {
            generation[k].weights[m][i][j] += 0.20 * my_random(-1,1) * generation[k].weights[m][i][j];
          }
        }
      }

      for (int m = 0; m < nn_nbrLayers-1; m++)
      {
        for (int i = 0; i < nn_layersSizes[m+1]; i++)
        {
          generation[k].biases[m][i] = 0.20 * my_random(-1,1) * generation[k].biases[m][i];
        }
      }
    }
  }
}

Neural_net Genetic_learning_neural::get_best_neural_net()
/*
  returns the best neural net
*/
{
  return generation[max_index(&fitnesses)];
}

int Genetic_learning_neural::get_best_fitness()
/*
  returns the best fitness
*/
{
  return fitnesses[max_index(&fitnesses)];
}

int Genetic_learning_neural::get_average_fitness() const
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

void Genetic_learning_neural::write_config_to_file(char* filename)
/*
  writes the config to a txt file
*/
{
  std::ofstream myFile;
  myFile.open(filename);

  myFile << "int size = " << gridSize << ";\n";
  myFile << "int nbIndiv = " << nbIndiv << ";\n";
  myFile << "int nbGeneration = " << nbGenerations << ";\n";
  myFile << "int nbEvalPerIndiv = " << nbEvalPerIndiv << ";\n";
  myFile << "float selectionRateBest = " << selectionRateBest << ";\n";
  myFile << "float selectionRateOthers = " << selectionRateOthers << ";\n";
  myFile << "float mutationProba = " << mutationProba << ";\n";
  myFile << "int nbrOfThreads = " << nbrOfThreads << ";\n";
  myFile << "int depth = " << depth << ";\n";
  myFile << "int nn_nbrLayers = " << nn_nbrLayers << ";\n";
  myFile << "std::vector<int> nn_layersSizes = {" ;
  for (int k = 0; k < nn_layersSizes.size()-1; k++)
  {
    myFile << nn_layersSizes[k] << ", ";
  }
  myFile << nn_layersSizes[nn_layersSizes.size()-1] << "}" << "\n";
  myFile << "std::vector<int> nn_nonLinearities = {" ;
  for (int k = 0; k < nn_nonLinearities.size()-1; k++)
  {
    myFile << nn_nonLinearities[k] << ", ";
  }
  myFile << nn_nonLinearities[nn_nonLinearities.size()-1] << "}" << '\n';

  myFile.close();
}

void Genetic_learning_neural::play_N_games_and_print_best()
{
  std::vector<Game_neural> vecOfGames;
  std::vector<int> vecOfScores;
  int nbrGamesToEvaluate = nbEvalPerIndiv;

  for (int k=0; k<nbrGamesToEvaluate; k++)
  {
    vecOfGames.push_back(Game_neural(gridSize, depth, get_best_neural_net()));
  }

  for (int k=0; k<nbrGamesToEvaluate; k++)
  {
    vecOfGames[k].play();
    vecOfScores.push_back(vecOfGames[k].get_my_score());
  }

  vecOfGames[max_index(&vecOfScores)].print();
  std::cout << "Score: " << vecOfScores[max_index(&vecOfScores)] << "\n\n";
}

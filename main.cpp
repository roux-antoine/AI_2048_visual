
#include "Game.h"
#include "Game_player.h"
#include "tools.h"
#include "Genetic_learning_neural.h"
#include "Learning_stats.h"
#include "Neural_net.h"
#include "Game_neural.h"

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <string>

void test_neural()
{
  int gridSize = 4;
  int searchDepth = 2;
  std::vector<int> sizes = {16, 9, 1};
  std::vector<int> nonLinearities = {1, 0};
  Neural_net myNeuralNet;
  myNeuralNet.print();

  Game_neural myGame(gridSize, searchDepth, myNeuralNet);
  myGame.play();
  myGame.print();
}

void learning_test_neural()
{
  int size = 4;
  int nbGeneration = 12;
  int nbIndiv = 40;
  int nbEvalPerIndiv = 20;
  float selectionRateBest = 0.1;
  float selectionRateOthers = 0.05;
  float mutationProba = 0.4;
  int nbrOfThreads = 4;
  int depth = 2;

  // std::vector<int> layersSizes = {16, 1};
  // std::vector<int> nonLinearities = {0};

  // std::vector<int> layersSizes = {16, 9, 1};
  // std::vector<int> nonLinearities = {1, 0};
  //
  std::vector<int> layersSizes = {16, 9, 3, 1};
  std::vector<int> nonLinearities = {1, 0, 0};

  Learning_stats stats;

  Genetic_learning_neural learning(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads, depth, layersSizes, nonLinearities);
  // Genetic_learning_neural learning(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads, depth);

  auto start = std::chrono::system_clock::now();
  learning.execute(&stats);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  std::cout << "\nElapsed time: " << elapsed_seconds.count() << "s\n";
}



int main()
{

  for(int i = 0; i < 1; i++)
  {
    learning_test_neural();
  }



  return 0;
}


#include "Game.h"
#include "Game_player.h"
#include "tools.h"
#include "Game_AI.h"
#include "AI.h"
#include "AI_hc.h"
#include "AI_random.h"
#include "Genetic_learning.h"
#include "Genetic_learning_neural.h"
#include "Learning_stats.h"
#include "Neural_net.h"
#include "Game_neural.h"

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <string>


void time_test()
{
  int size = 4;
  int nbrGames = 100;
  int depth = 2;

  AI_hc myAI(size, depth);

  int startTime = clock();

  int nb128 = 0;
  int nb256 = 0;
  int nb512 = 0;
  int nb1024 = 0;
  int nb2048 = 0;
  int nb4096 = 0;
  for (int gameNbr = 0; gameNbr < nbrGames; gameNbr++)
  {
    printf("%d\n", gameNbr+1);
    Game_AI myGame(size, myAI);

    myGame.play();
    // myGame.print();
    int max = 0;
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        if (myGame.grid[i][j] > max)
        {
          max = myGame.grid[i][j];
        }
      }
    }
    if (max >= 4096)
    {
      nb4096 += 1;
    }
    else if (max >= 2048)
    {
      nb2048 += 1;
    }
    else if (max >= 1024)
    {
      nb1024 += 1;
    }
    else if (max >= 512)
    {
      nb512 += 1;
    }
    else if (max >= 256)
    {
      nb256 += 1;
    }
    else if (max >= 128)
    {
      nb128 += 1;
    }
  // printf("%d / %d \n", nb2048, gameNbr+1);
  // printf("%d\n", score/nbrGames);
  }
  printf("4096 : %d, 2048 : %d, 1024 : %d, 512 : %d, 256 : %d, 128 : %d\n", nb4096, nb2048, nb1024, nb512, nb256, nb128);

  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}


void learning_test()
{
  int size = 4;
  int nbGeneration = 10;
  int nbIndiv = 16;
  int nbEvalPerIndiv = 45;
  float selectionRateBest = 0.3;
  float selectionRateOthers = 0.05;
  float mutationProba = 0.5;
  int nbrOfThreads = 4;
  int depth = 2;

  Learning_stats stats;

  Genetic_learning learn(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads, depth);

  auto start = std::chrono::system_clock::now();
  learn.execute(&stats);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  printf("\n");

  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}

void test_one_speed()
{
  int size = 4;
  int depth = 2;

  AI_hc myAI(size, depth);

  int startTime = clock();

  Game_AI myGame(size, myAI);

  myGame.play();

  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
  myGame.print();

}

void test_neural()
{
  int gridSize = 4;
  int searchDepth = 2;
  std::vector<int> sizes = {16, 9, 1};
  std::vector<int> nonLinearities = {1, 0};

  // Neural_net myNeuralNet(4, 3, sizes, nonLinearities);
  Neural_net myNeuralNet;
  myNeuralNet.print();

  // std::vector<int> inputVector = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // myNeuralNet.print();
  // float toto = myNeuralNet.forward_pass(inputVector);
  // std::cout << "toto: " << toto << '\n';

  Game_neural myGame(gridSize, searchDepth, myNeuralNet);
  myGame.play();
  myGame.print();
}

void learning_test_neural()
{
  int size = 4;
  int nbGeneration = 10;
  int nbIndiv = 15;
  int nbEvalPerIndiv = 10;
  float selectionRateBest = 0.3;
  float selectionRateOthers = 0.05;
  float mutationProba = 0.5;
  int nbrOfThreads = 4;
  int depth = 2;

  std::vector<int> layersSizes = {16, 1};
  std::vector<int> nonLinearities = {0};

  // std::vector<int> layersSizes = {16, 9, 1};
  // std::vector<int> nonLinearities = {1, 0};

  Learning_stats stats;

  // Genetic_learning_neural learning(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads, depth, layersSizes, nonLinearities);
  Genetic_learning_neural learning(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads, depth);

  auto start = std::chrono::system_clock::now();
  learning.execute(&stats);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  printf("\n");

  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}



int main()
{

  // Game_player myGame(4);
  // myGame.play();

  // AI_hc myAI(4);
  // Game_AI myGame(4, myAI);
  // myGame.play();
  // myGame.print();

  // AI_random myAI(4);
  // Game_AI myGame(4, myAI);
  // myGame.play();
  // myGame.print();

  // time_test();
  // test_one_speed();
  // learning_test();

  // test_neural();
  learning_test_neural();

  return 0;
}

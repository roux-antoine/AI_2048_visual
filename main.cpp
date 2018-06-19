
#include "Game.h"
#include "Game_player.h"
#include "tools.h"
#include "Game_AI.h"
#include "AI.h"
#include "AI_hc.h"
#include "AI_random.h"
#include "Genetic_learning.h"
#include "Learning_stats.h"

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <string>


void time_test()
{
  int size = 4;
  int nbrGames = 1;

  AI_hc myAI(size);

  int startTime = clock();

  int nb512 = 0;
  int nb1024 = 0;
  int nb2048 = 0;
  for (int gameNbr = 0; gameNbr < nbrGames; gameNbr++)
  {
    Game_AI myGame(size, myAI);

    myGame.play();
    // myGame.print();

    // for (int i = 0; i < size; i++)
    // {
    //   for (int j = 0; j < size; j++)
    //   {
    //     if (myGame.grid[j][i] >= 2048)
    //     {
    //       nb2048 += 1;
    //     }
    //   }
    // myGame.print();
    // }
  // printf("%d\n", nb2048);
  // printf("%d\n", score/nbrGames);
  }

  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}


void learning_test()
{
  int size = 4;
  int nbGeneration = 14;
  int nbIndiv = 20;
  int nbEvalPerIndiv = 75;
  float selectionRateBest = 0.2;
  float selectionRateOthers = 0.3;
  float mutationProba = 0.5;
  int nbrOfThreads = 4;

  Learning_stats stats;

  Genetic_learning learn(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads);

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

  AI_hc myAI(size);

  int startTime = clock();

  Game_AI myGame(size, myAI);

  myGame.play();

  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
  myGame.print();

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
  learning_test();

  return 0;
}

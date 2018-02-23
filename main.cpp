
#include "Game.cpp"
#include "Game_player.cpp"
#include "Game_AI.cpp"
#include "AI.cpp"
#include "AI_hc.cpp"
#include "AI_random.cpp"
#include "Genetic_learning.cpp"
#include "Learning_stats.cpp"

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <string>


void time_test()
{
  int size = 4;
  int nbrGames = 300;

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

    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        if (myGame.grid[j][i] >= 2048)
        {
          nb2048 += 1;
    }
    // myGame.print();
  }
  printf("%d\n", nb2048);
  // printf("%d\n", score/nbrGames);

  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}


void learning_test()
{
  int size = 4;
  int nbGeneration = 5;
  int nbIndiv = 10;
  int nbEvalPerIndiv = 10;
  float selectionRateBest = 0.2;
  float selectionRateOthers = 0.05;
  float mutationProba = 0.1;
  int nbrOfThreads = 4;

  Learning_stats stats;

  GeneticLearning learn(size, nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRateBest, selectionRateOthers, mutationProba, nbrOfThreads);

  auto start = std::chrono::system_clock::now();
  learn.execute(&stats);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  printf("\n");

  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

}


int main()
{

  time_test();
  // learning_test();


  return 0;
}

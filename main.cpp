
#include "Game.cpp"
#include "Game_player.cpp"
#include "Game_AI.cpp"
#include "AI.cpp"
#include "AI_hc.cpp"
#include "genetic_learning.cpp"
#include <iostream>
#include <random>
#include <time.h>

//// -- Trucs à faire -- ////
// gérer tous les cas d'exception...

void time_test() {
  int size = 4;

  AI_hc myAI(size);

  for (size_t i = 0; i < 4; i++) {
    for (size_t k = 0; k < 4; k++) {
      printf("%d ", myAI.fitnessGrid[i][k]);
    }
    printf("\n");
  }
  printf("\n");

  int startTime = clock();

  int score = 0;
  for (int k = 0; k < 100; k++)
  {
    Game_AI myGame(4, myAI);

    myGame.play();
    // myGame.print();

    for (size_t i = 0; i < size; i++)
    {
      for (size_t j = 0; j < size; j++)
      {
        if (myGame.grid[j][i] >= 2048)
        {
          score += 1;
        }
      }
    }

    // myGame.print();
  }
  printf("%d\n", score);
  printf("Time : %f \n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}

int main(int argc, char const *argv[])
{
  // int size = 4;
  // GeneticLearning learn;
  //
  // int startTime = clock();
  // learn.execute();
  // std::cout << "Time : \n" << (double(clock() - startTime)/CLOCKS_PER_SEC) << std::endl;
  //
  // std::cout << learn.get_best_fitness() << std::endl;

  time_test();

  return 0;
}

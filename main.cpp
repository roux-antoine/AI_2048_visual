
#include "Game.cpp"
#include "Game_player.cpp"
#include "Game_AI.cpp"
#include "AI.cpp"
#include "genetic_learning.cpp"
#include <iostream>
#include <random>
#include <time.h>

//// -- Trucs à faire -- ////
// gérer tous les cas d'exception...

void time_test() {
  int size = 4;

  AI myAI(size);

  int startTime = clock();

  for (int k = 0; k < 100; k++)
  {
    Game_AI myGame(4, myAI);

    myGame.play();
    // myGame.print();
  }

  printf("Time : %f \n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}

int main(int argc, char const *argv[])
{
  int size = 4;
  GeneticLearning learn;

  int startTime = clock();
  learn.execute();
  std::cout << "Time : %f \n" << (double(clock() - startTime)/CLOCKS_PER_SEC) << std::endl;

  std::cout << learn.get_best_fitness() << std::endl;
  return 0;
}

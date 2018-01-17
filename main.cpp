
#include "Game.cpp"
#include "Game_player.cpp"
#include "Game_AI.cpp"
#include <iostream>
#include <random>
#include <time.h>

//// -- Trucs à faire -- ////
// gérer tous les cas d'exception...


int main(int argc, char const *argv[])
{

  int size = 4;
  Game myGame(size);

  int startTime = clock();
  for (int k = 0; k < 100; k++)
  {
    Game_AI myGame(4);

    myGame.play();
    // myGame.print();

  }

  printf("Time : %f \n", (double(clock() - startTime)/CLOCKS_PER_SEC));

  return 0;
}

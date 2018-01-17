
#include "Game.cpp"
#include "Game_player.cpp"
#include "Game_AI.cpp"
#include "AI.cpp"
#include <iostream>
#include <random>
#include <time.h>

//// -- Trucs à faire -- ////
// gérer tous les cas d'exception...


int main(int argc, char const *argv[])
{

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
  return 0;
}


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

  int score = 0;

  for (int k = 0; k < 500; k++)
  {
    Game_AI myGame(4, myAI);
    myGame.play();
    // myGame.print();

    for (size_t i = 0; i < size; i++) {
      for (size_t k = 0; k < size; k++) {
        if (myGame.grid[k][i] == 2048)
        {
          score ++;
        }
      }
    }
  }
  printf("%d\n", score);
  printf("Time : %f \n", (double(clock() - startTime)/CLOCKS_PER_SEC));
  return 0;
}


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
  // Game_AI myGame(size);

  // AI myAI(size);
  // std::cout << myAI.gridDimension << std::endl;
  //
  // for (size_t i = 0; i < size; i++)
  // {
  //   for (size_t k = 0; k < size; k++) {
  //     printf("%d ", myAI.fitnessGrid[i][k]);
  //   }
  //   printf("\n");
  // }


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

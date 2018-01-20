
#include "Game.cpp"
#include "Game_player.cpp"
#include "Game_AI.cpp"
#include "AI.cpp"
#include "AI_hc.cpp"
#include "AI_random.cpp"
#include "genetic_learning.cpp"
#include <iostream>
#include <random>
#include <time.h>

//// -- Trucs à faire -- ////
// gérer tous les cas d'exception...

void time_test() {
  int size = 4;
  int nbrGames = 100;

  AI_hc myAI(size);

  int startTime = clock();

  int score = 0;
  for (int gameNbr = 0; gameNbr < nbrGames; gameNbr++)
  {
    Game_AI myGame(4, myAI);

    // printf("%d\n", gameNbr);

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
        // score += myGame.grid[j][i];
      }
    }

    // myGame.print();
  }
  printf("%d\n", score);
  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}

int main(int argc, char const *argv[])
{
  int size = 4;
  GeneticLearning learn;

  int startTime = clock();
  learn.execute();
  std::cout << "Time : " << (double(clock() - startTime)/CLOCKS_PER_SEC) << std::endl;

  std::cout << "Best fitness : " << learn.get_best_fitness() << std::endl;


  return 0;
}

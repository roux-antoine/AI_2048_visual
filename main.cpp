
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

void time_test()
{
  int size = 4;
  int nbrGames = 500;

  AI_hc myAI(size);

  int startTime = clock();

  int score = 0;
  for (int gameNbr = 0; gameNbr < nbrGames; gameNbr++)
  {
    Game_AI myGame(size, myAI);

    // printf("%d\n", gameNbr);

    myGame.play();
    // myGame.print();

    for (size_t i = 0; i < size; i++)
    {
      for (size_t j = 0; j < size; j++)
      {
        // if (myGame.grid[j][i] >= 2048)
        // {
        //   score += 1;
        // }
        score += myGame.grid[j][i];
      }
    }

    //myGame.print();
  }
  printf("%d\n", score/nbrGames);
  printf("Time : %f secondes\n", (double(clock() - startTime)/CLOCKS_PER_SEC));
}


void learning_test()
{
  int size = 4;
  int nbGeneration = 10;
  int nbIndiv = 10;
  int nbEvalPerIndiv = 20;
  float selectionRate = 0.2;
  float selectionOthers = 0.05;
  float mutationProba = 0.1;

  GeneticLearning learn(nbGeneration, nbIndiv, nbEvalPerIndiv, selectionRate, selectionOthers, mutationProba);

  int startTime = clock();
  learn.execute();
  std::cout << "Time : " << (double(clock() - startTime)/CLOCKS_PER_SEC) << std::endl;

  std::cout << "Best fitness : " << learn.get_best_fitness() << std::endl;

}


int main(int argc, char const *argv[])
{

  time_test();
  //learning_test();


  return 0;
}

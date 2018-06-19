#include "Game_AI.h"

Game_AI::Game_AI(int givenSize, AI givenAI) : Game(givenSize)
{
  myAI = givenAI;
}


void Game_AI::play()
/*
  main loop in which the game is played
*/
{
  //initialization of the start grid
  this->add_random_nbr();
  this->add_random_nbr();

  //main loop
  while((!this->is_finished()))
  {
    // this->print();
    // char a;
    // std::cin >> a;
    int direction = get_direction();

    if (this->can_swipe(direction))
    {
      this->swipe(direction);
      this->add_random_nbr();
    }
  }
  // this->print();
}


int Game_AI::get_direction()
/*
  chooses the directon in which to swipe
  decides by computing the fitnesses of all the possible grids with two swipes in advance
  and chooses the direction that gives the best fitness
*/
{
  // we simulate the possible moves
  int fitnessValuesGrid[4][4]; //the size = 4 because 4 possible moves (not related to size of grid)
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      fitnessValuesGrid[k][i] = 0;
    }
  }

  bool possibleMoves[4] = {false, false, false, false};
  int nbrPossibleMoves = 0;
  for (int direction = 0; direction < 4; direction++)
  {
    bool canSwipe = this->can_swipe(direction);
    possibleMoves[direction] = canSwipe;
    nbrPossibleMoves += canSwipe;
  }

  if (nbrPossibleMoves > 0)
  {
//       // uncomment below to test a variation of the direction decision
//    if (possibleMoves[0] || possibleMoves[1] || possibleMoves[3])
//    //if can swipe up, left or down, do not swipe right
//    {
//      possibleMoves[2] = false; //we un-possiblize the right swipe -> gives better performances ?
//    }

    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          Game_AI tempGame(size, myAI);

          for (int i = 0; i<size; i++ )
          {
              for (int k = 0; k<size; k++ )
              {
                  tempGame.grid[k][i] = this->grid[k][i];
              }
          }

          tempGame.swipe(k);
          fitnessValuesGrid[k][i] += tempGame.compute_fitness();

          if (tempGame.can_swipe(i)) //the second swipe
          {
            tempGame.swipe(i);
            fitnessValuesGrid[k][i] += tempGame.compute_fitness();
          }
        }
      }
    }

    //now we need to choose the best direction according to the fitnessValuesGrid

    int maxArray[4] = {0, 0, 0, 0};
    for (int k = 0; k < 4; k++)
    // we find the max of fitnessValuesGrid, with respect to the first move
    {
      for (int i = 0; i < 4; i++)
      {
        if (fitnessValuesGrid[k][i] > maxArray[k])
        {
          maxArray[k] = fitnessValuesGrid[k][i];
        }
      }
    }

    int maxValue = 0;
    int direction = 0;
    for (int k = 0; k < 4; k++)
    {
      if (maxArray[k] > maxValue)
      {
        maxValue = maxArray[k];
        direction = k;
      }
    }
    return (direction);
  }
  return (-1);
}

int Game_AI::compute_fitness() const
/*
  computes the fitness using the fitnessGrid
*/
{
  int max = 0;

  int fitness = 0;
  for (int k = 0; k < size; k++)
  {
    for (int i = 0; i < size; i++)
    {
      if (myAI.weightsGrid[k][i] > max)
      {
        max = myAI.weightsGrid[k][i];
      }
      fitness += grid[k][i] * (myAI.weightsGrid[k][i]);
    }
  }
  return ((int)(fitness / max));
}

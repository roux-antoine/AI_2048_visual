#include "Game_AI.hpp"
#include <iostream>


Game_AI::Game_AI(int givenSize, AI givenAI) : Game(givenSize)
{
  myAI = givenAI;

}

void Game_AI::play()
// main loop in which the game is played
{
  this->add_random_nbr();
  this->add_random_nbr();

  while(!this->is_finished())
  {
    int direction = get_direction();
    // this->print();
    // char a;
    // std::cin >> a;
    if (this->can_swipe(direction))
    {
      this->swipe(direction);
      this->add_random_nbr();
    }
  }
}


int Game_AI::get_direction()
// chooses the directon in which to swipe
// decides by computing the fitnesses of all the possible grids with two swipes in advance
{

  // we simulate the possible moves
  int fitnessValuesGrid[size][size];
  for (int k = 0; k < size; k++)
  {
    for (int i = 0; i < size; i++)
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
    if (possibleMoves[0] == true || possibleMoves[1] == true || possibleMoves[3] == true)
    //if can swipe up, left or down, do not swipe right
    {
      possibleMoves[2] = false; //we un-possiblize the right swipe
    }

    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          Game_AI tempGame = *this;
          tempGame.swipe(k);
          if (tempGame.can_swipe(i))
          {
            fitnessValuesGrid[k][i] += 0.5*tempGame.compute_fitness();
            tempGame.swipe(i);
            fitnessValuesGrid[k][i] += tempGame.compute_fitness();
          }
        }
      }
    }

    //now we need to choose the direction according to the fitnessValuesGrid

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

  return (-1); // a changer
}

int Game_AI::compute_fitness()
{
  //we compute the fitness of the grid
  int fitness = 0;
  for (int k = 0; k < size; k++)
  {
    for (int i = 0; i < size; i++)
    {
      fitness += grid[k][i] * (myAI.fitnessGrid[k][i]);
    }
  }
  return (fitness);

  // //en normalisant la grille par la plus grande valeur :
  // //dans ce cas, la grille de jeu contient des floats -> la fitness est un floats
  // //peut etre qu'on peut la caster en int avant de la retourner

  //-> ça a l'air de fonctionner mais c'est beaucoup plus lent -> logique, on cherche le max à chaque fois...

  // float fitness = 0;
  // //we find the max of the grid
  // int max = 0;
  // for (int i = 0; i < size; i++)
  // {
  //   for (int k = 0; k < size; k++)
  //   {
  //     if (myAI.fitnessGrid[k][i] > max)
  //     {
  //       max = myAI.fitnessGrid[k][i];
  //     }
  //   }
  // }
  // printf("%d\n", max);
  //
  //
  // for (int k = 0; k < size; k++)
  // {
  //   for (int i = 0; i < size; i++)
  //   {
  //     fitness += grid[k][i] * (float(myAI.fitnessGrid[k][i]) / max);
  //   }
  // }
  // return ((int)fitness);

}

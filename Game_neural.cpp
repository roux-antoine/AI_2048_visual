#include "Game_neural.h"

Game_neural::Game_neural(int givenSize, int givenDepth, Neural_net givenNeuralNet) : Game(givenSize)
{
  myNeuralNet = givenNeuralNet;
  depth = givenDepth;
}


void Game_neural::play()
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
    // uncomment 3 lines below to see in terminal what happens during the game
    // this->print();
    // char a;
    // std::cin >> a;
    int direction = get_direction(depth);
    if (this->can_swipe(direction))
    {
      this->swipe(direction);
      this->add_random_nbr();
    }
  }
  // this->print();
}




int Game_neural::get_direction(int depth)
/*
  calls the get_direction function according to the given depth
  if depth is not legal, return with a depth of two
*/
{
  if (depth == 1)
  {
    return get_direction_1();
  }
  else if (depth == 2)
  {
    return get_direction_2();
  }
  else if (depth == 3)
  {
    return get_direction_3();
  }
  else if (depth == 4)
  {
    return get_direction_4();
  }
  else if (depth == 5)
  {
    return get_direction_5();
  }
  else if (depth == 6)
  {
    return get_direction_6();
  }
  else
  {
    return get_direction_2();
  }
}


int Game_neural::get_direction_1() //depth 1
/*
  chooses the direction in which to swipe
  decides by computing the fitnesses of all the possible grids with one swipe in advance
  and chooses the direction that gives the best fitness
*/
{
  double inf = std::numeric_limits<double>::infinity();

  // we simulate the possible moves
  int fitnessValuesGrid[4]; //the size = 4 because 4 possible moves (not related to size of grid)
  //for an unknown reason, if the fitnessValuesGrid is of type double it does not work...
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      fitnessValuesGrid[k] = -inf;
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
     //    // uncomment below to test a variation of the direction decision
     // if (possibleMoves[0] || possibleMoves[1] || possibleMoves[3])
     // //if can swipe up, left or down, do not swipe right
     // {
     //   possibleMoves[2] = false; //we un-possiblize the right swipe -> gives better performances ?
     // }

    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          Game_neural tempGame(size, depth, myNeuralNet);

          tempGame = *this;

          tempGame.swipe(k);
          fitnessValuesGrid[k] += tempGame.compute_fitness();
        }
      }
    }

    //now we need to choose the best direction according to the fitnessValuesGrid

    double maxArray[4] = {-inf, -inf, -inf, -inf};
    for (int k = 0; k < 4; k++)
    // we find the max of fitnessValuesGrid, with respect to the first move
    {
      for (int i = 0; i < 4; i++)
      {
        if (fitnessValuesGrid[k] > maxArray[k])
        {
          maxArray[k] = fitnessValuesGrid[k];
        }
      }
    }

    double maxValue = -inf;
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

int Game_neural::get_direction_2() //depth 2
/*
  chooses the direction in which to swipe
  decides by computing the fitnesses of all the possible grids with two swipes in advance
  and chooses the direction that gives the best fitness
*/
{
  double inf = std::numeric_limits<double>::infinity();

  // we simulate the possible moves
  int fitnessValuesGrid[4][4]; //the size = 4 because 4 possible moves (not related to size of grid)
  //for an unknown reason, if the fitnessValuesGrid is of type double it does not work...
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      fitnessValuesGrid[k][i] = -inf;
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
    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          Game_neural tempGame(size, depth, myNeuralNet);

          tempGame = *this;

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
    double maxArray[4] = {-inf, -inf, -inf, -inf};

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

    // int maxValue = 0;
    double maxValue = -inf;
    int direction = -1;
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


int Game_neural::get_direction_3() //depth 3
/*
  chooses the direction in which to swipe
  decides by computing the fitnesses of all the possible grids with three swipes in advance
  and chooses the direction that gives the best fitness
*/
{
  double inf = std::numeric_limits<double>::infinity();

  // we simulate the possible moves
  int fitnessValuesGrid[4][4][4];
  //for an unknown reason, if the fitnessValuesGrid is of type double it does not work...
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
            fitnessValuesGrid[k][i][j] = -inf;
      }
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
    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            // Game_neural tempGame = *this;

            Game_neural tempGame(size, depth, myNeuralNet);
            tempGame = *this;

            tempGame.swipe(k);
            fitnessValuesGrid[k][i][j] += tempGame.compute_fitness();

            if (tempGame.can_swipe(i)) //the second swipe
            {
              tempGame.swipe(i);
              fitnessValuesGrid[k][i][j] += tempGame.compute_fitness();

              if (tempGame.can_swipe(j)) //the third swipe
              {
                tempGame.swipe(j);
                fitnessValuesGrid[k][i][j] += tempGame.compute_fitness();
              }
            }
          }
        }
      }
    }

    //now we need to choose the direction according to the fitnessValuesGrid

    double maxArray[4] = {-inf, -inf, -inf, -inf};
    for (int k = 0; k < 4; k++)
    // we find the max of fitnessValuesGrid, with respect to the first move
    {
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          if (fitnessValuesGrid[k][i][j] > maxArray[k])
          {
            maxArray[k] = fitnessValuesGrid[k][i][j];
          }
        }
      }
    }

    double maxValue = -inf;
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

int Game_neural::get_direction_4() //depth 4
/*
  chooses the direction in which to swipe
  decides by computing the fitnesses of all the possible grids with four swipes in advance
  and chooses the direction that gives the best fitness
*/
{
  double inf = std::numeric_limits<double>::infinity();

  // we simulate the possible moves
  int fitnessValuesGrid[4][4][4][4];
  //for an unknown reason, if the fitnessValuesGrid is of type double it does not work...
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        for (int l = 0; l < 4; l++)
        {
          fitnessValuesGrid[k][i][j][l] = -inf;
        }
      }
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
    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            for (int l = 0; l < 4; l++)
            {
              Game_neural tempGame(size, depth, myNeuralNet);
              tempGame = *this;

              tempGame.swipe(k);
              fitnessValuesGrid[k][i][j][l] += tempGame.compute_fitness();

              if (tempGame.can_swipe(i)) //the second swipe
              {
                tempGame.swipe(i);
                fitnessValuesGrid[k][i][j][l] += tempGame.compute_fitness();

                if (tempGame.can_swipe(j)) //the third swipe
                {
                  tempGame.swipe(j);
                  fitnessValuesGrid[k][i][j][l] += tempGame.compute_fitness();

                  if (tempGame.can_swipe(l)) //the fourth swipe
                  {
                    tempGame.swipe(l);
                    fitnessValuesGrid[k][i][j][l] += tempGame.compute_fitness();

                  }
                }
              }
            }
          }
        }
      }
    }

    //now we need to choose the direction according to the fitnessValuesGrid

    double maxArray[4] = {-inf, -inf, -inf, -inf};
    for (int k = 0; k < 4; k++)
    // we find the max of fitnessValuesGrid, with respect to the first move
    {
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          for (int l = 0; l < 4; l++)
          {

            if (fitnessValuesGrid[k][i][j][l] > maxArray[k])
            {
              maxArray[k] = fitnessValuesGrid[k][i][j][l];
            }

          }
        }
      }
    }

    double maxValue = -inf;
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

int Game_neural::get_direction_5() //depth 5
/*
  chooses the direction in which to swipe
  decides by computing the fitnesses of all the possible grids with five swipes in advance
  and chooses the direction that gives the best fitness
*/
{
  double inf = std::numeric_limits<double>::infinity();

  // we simulate the possible moves
  int fitnessValuesGrid[4][4][4][4][4];
  //for an unknown reason, if the fitnessValuesGrid is of type double it does not work...
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        for (int l = 0; l < 4; l++)
        {
          for (int m = 0; m < 4; m++)
          {
            fitnessValuesGrid[k][i][j][l][m] = -inf;
          }
        }
      }
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
    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            for (int l = 0; l < 4; l++)
            {
              for (int m= 0; m < 4; m++) {

                // Game_neural tempGame = *this;

                Game_neural tempGame(size, depth, myNeuralNet);
                tempGame = *this;

                tempGame.swipe(k);
                fitnessValuesGrid[k][i][j][l][m] += tempGame.compute_fitness();

                if (tempGame.can_swipe(i)) //the second swipe
                {
                  tempGame.swipe(i);
                  fitnessValuesGrid[k][i][j][l][m] += tempGame.compute_fitness();

                  if (tempGame.can_swipe(j)) //the third swipe
                  {
                    tempGame.swipe(j);
                    fitnessValuesGrid[k][i][j][l][m] += tempGame.compute_fitness();

                    if (tempGame.can_swipe(l)) //the fourth swipe
                    {
                      tempGame.swipe(l);
                      fitnessValuesGrid[k][i][j][l][m] += tempGame.compute_fitness();

                      if (tempGame.can_swipe(m)) //the fifth swipe
                      {
                        tempGame.swipe(m);
                        fitnessValuesGrid[k][i][j][l][m] += tempGame.compute_fitness();
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    //now we need to choose the direction according to the fitnessValuesGrid

    double maxArray[4] = {-inf, -inf, -inf, -inf};
    for (int k = 0; k < 4; k++)
    // we find the max of fitnessValuesGrid, with respect to the first move
    {
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          for (int l = 0; l < 4; l++)
          {
            for (int m = 0; m < 4; m++)
            {
              if (fitnessValuesGrid[k][i][j][l][m] > maxArray[k])
              {
                maxArray[k] = fitnessValuesGrid[k][i][j][l][m];
              }
            }
          }
        }
      }
    }

    double maxValue = -inf;
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

int Game_neural::get_direction_6() //depth 6
/*
  chooses the direction in which to swipe
  decides by computing the fitnesses of all the possible grids with six swipes in advance
  and chooses the direction that gives the best fitness
*/
{
  double inf = std::numeric_limits<double>::infinity();

  // we simulate the possible moves
  int fitnessValuesGrid[4][4][4][4][4][4];
  //for an unknown reason, if the fitnessValuesGrid is of type double it does not work...
  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        for (int l = 0; l < 4; l++)
        {
          for (int m = 0; m < 4; m++)
          {
            for (int n = 0; n < 4; n++)
            {
              fitnessValuesGrid[k][i][j][l][m][n] = -inf;
            }
          }
        }
      }
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
    for (int k = 0; k < 4 ; k++)
    {
      if (possibleMoves[k])
      {
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            for (int l = 0; l < 4; l++)
            {
              for (int m = 0; m < 4; m++)
              {
                for (int n = 0; n < 4; n++)
                {
                  // Game_neural tempGame = *this;

                  Game_neural tempGame(size, depth, myNeuralNet);
                  tempGame = *this;

                  tempGame.swipe(k);
                  fitnessValuesGrid[k][i][j][l][m][n] += tempGame.compute_fitness();

                  if (tempGame.can_swipe(i)) //the second swipe
                  {
                    tempGame.swipe(i);
                    fitnessValuesGrid[k][i][j][l][m][n] += tempGame.compute_fitness();

                    if (tempGame.can_swipe(j)) //the third swipe
                    {
                      tempGame.swipe(j);
                      fitnessValuesGrid[k][i][j][l][m][n] += tempGame.compute_fitness();

                      if (tempGame.can_swipe(l)) //the fourth swipe
                      {
                        tempGame.swipe(l);
                        fitnessValuesGrid[k][i][j][l][m][n] += tempGame.compute_fitness();

                        if (tempGame.can_swipe(m)) //the fifth swipe
                        {
                          tempGame.swipe(m);
                          fitnessValuesGrid[k][i][j][l][m][n] += tempGame.compute_fitness();

                          if (tempGame.can_swipe(n)) //the sixth swipe
                          {
                            tempGame.swipe(n);
                            fitnessValuesGrid[k][i][j][l][m][n] += tempGame.compute_fitness();
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    //now we need to choose the direction according to the fitnessValuesGrid

    double maxArray[4] = {-inf, -inf, -inf, -inf};
    for (int k = 0; k < 4; k++)
    // we find the max of fitnessValuesGrid, with respect to the first move
    {
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          for (int l = 0; l < 4; l++)
          {
            for (int m = 0; m < 4; m++)
            {
              for (int n = 0; n < 4; n++)
              {
                if (fitnessValuesGrid[k][i][j][l][m][n] > maxArray[k])
                {
                  maxArray[k] = fitnessValuesGrid[k][i][j][l][m][n];
                }
              }
            }
          }
        }
      }
    }

    double maxValue = -inf;
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

int Game_neural::compute_fitness()
/*
  computes the fitness using the neural network structure
*/
{
  //we flatten the game grid
  std::vector<int> gridFlattened = std::vector<int>(size*size, 0);
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      gridFlattened[i*size+j] = grid[i][j];
    }
  }


  float fitness = myNeuralNet.forward_pass(gridFlattened);
  // std::cout << fitness << '\n';
  return (fitness);
  // return(classicScore);
}

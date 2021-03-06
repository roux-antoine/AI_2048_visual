#include "Game.h"

Game::Game(int givenSize)
{
  size = givenSize;
  classicScore = 0;

  for (int k = 0 ; k < givenSize ; k++)
  {
    grid.push_back(std::vector<int>(givenSize,0));
  }
}


void Game::print() const
//prints the grid -> will be replaced by something in Qt
{
  for (int k = 0 ; k < size ; k++)
  {
    for (int i = 0 ; i < size ; i++)
    {
      if (grid[k][i] == 0)
      {
        // printf(".    ");
        std::cout << BLACK << ".    " << RESET << std::endl;
      }
      else if (grid[k][i] / 10 < 0.5)
      {
        // printf("%d    ", grid[k][i]);
        if (grid[k][i] == 2)
        {
          std::cout << BLACK << grid[k][i] << "    " << RESET;
        }
        else if (grid[k][i] == 4)
        {
          std::cout << RED << grid[k][i] << "    " << RESET;
        }
        else
        {
          std::cout << GREEN << grid[k][i] << "    " << RESET;
        }
      }
      else if (grid[k][i] / 100 < 0.5)
      {
        // printf("%d   ", grid[k][i]);
        if (grid[k][i] == 16)
        {
          std::cout << YELLOW << grid[k][i] << "   " << RESET;
        }
        else if (grid[k][i] == 32)
        {
          std::cout << BLUE << grid[k][i] << "   " << RESET;
        }
        else
        {
          std::cout << MAGENTA << grid[k][i] << "   " << RESET;
        }
      }
      else if (grid[k][i] / 1000 < 0.5)
      {
        // printf("%d  ", grid[k][i]);
        if (grid[k][i] == 128)
        {
          std::cout << CYAN << grid[k][i] << "  " << RESET;
        }
        else if (grid[k][i] == 256)
        {
          std::cout << BOLDBLACK << grid[k][i] << "  " << RESET;
        }
        else
        {
          std::cout << BOLDRED << grid[k][i] << "  " << RESET;
        }
      }
      else if (grid[k][i] / 10000 < 0.5)
      {
        // printf("%d ", grid[k][i]);
        if (grid[k][i] == 1024)
        {
          std::cout << BOLDGREEN << grid[k][i] << " " << RESET;
        }
        else if (grid[k][i] == 2048)
        {
          std::cout << BOLDYELLOW << grid[k][i] << " " << RESET;
        }
        else
        {
          std::cout << BOLDBLUE << grid[k][i] << " " << RESET;
        }
      }


    }
    printf("\n");
  }
  printf("\n");
}

bool Game::can_swipe_up() const //l'originale
/*
  returns true if the grid can be swiped up
*/
{

  for (int columnNbr = 0; columnNbr < size; columnNbr++)
  {
    int currentColumn[size];
    int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the current column
    for (int k = 0; k < size; k++)
    {
      currentColumn[k] = grid[k][columnNbr];
      if (grid[k][columnNbr] != 0)
      {
        nbrNonZero++;
      }
    }

    if (nbrNonZero == 0)
    //if the current column is empty
    {
      continue; //used to go directly to the next column
    }

    for (int lineNbr = size-1; lineNbr > -1+nbrNonZero; lineNbr--)
    //checks if there is a zero in the column
    {
      if (currentColumn[lineNbr] != 0)
      {
        return true;
      }
    }

    for (int lineNbr = 0; lineNbr < size - 1; lineNbr++)
    //checks if two tiles of same value are side-by-side
    {
      if ((currentColumn[lineNbr] == currentColumn[lineNbr+1]) and (currentColumn[lineNbr] != 0))
      {
        return true;
      }
    }
  }
  return false;
}


bool Game::can_swipe_down() const
/*
  returns true if the grid can be swiped down
*/
{
    for (int columnNbr = 0; columnNbr < size; columnNbr++)
    //we iterate over the columns
    {
      int currentColumn[size];
      int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the current column
      for (int k = 0; k < size; k++)
      {
        currentColumn[k] = grid[k][columnNbr];
        if (grid[k][columnNbr] != 0)
        {
          nbrNonZero++;
        }
      }
      if (nbrNonZero == 0)
      //if the current column is empty
      {
        continue; //used to go directly to the next column
      }

      for (int lineNbr = 0; lineNbr < size-nbrNonZero; lineNbr++)
      //checks if there is a number different than zero at one side of the column
      //in that case, it is possible to swipe
      {
        if (currentColumn[lineNbr] != 0)
        {
          return true;
        }
      }

      for (int lineNbr = size - 1; lineNbr > 0; lineNbr--)
      //checks if two tiles of same value are side-by-side
      {
        if ((currentColumn[lineNbr] == currentColumn[lineNbr-1]) and (currentColumn[lineNbr] != 0))
        {
          return true;
        }
      }
    }
  return false;
}


bool Game::can_swipe_right() const
/*
  returns true if the grid can be swiped right
*/
{
    for (int lineNbr = 0; lineNbr < size; lineNbr++)
    //we iterate over the lines
    {
      int currentLine[size];
      int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the current line
      for (int k = 0; k < size; k++)
      {
        currentLine[k] = grid[lineNbr][k];
        if (grid[lineNbr][k] != 0)
        {
          nbrNonZero++;
        }
      }

      if (nbrNonZero == 0)
      //if the current line is empty
      {
        continue; //used to go directly to the next column
      }

      for (int columnNbr = 0; columnNbr < size-nbrNonZero; columnNbr++)
      //checks if there is a number different than zero at one side of the line
      //in that case, it is possible to swipe
      {
        if (currentLine[columnNbr] != 0)
        {
          return true;
        }
      }

      for (int columnNbr = size - 1; columnNbr > 0; columnNbr--)
      //checks if two tiles of same value are side-by-side
      {
        if ((currentLine[columnNbr] == currentLine[columnNbr-1]) and (currentLine[columnNbr] != 0))
        {
          return true;
        }
      }
    }
  return false;
}

bool Game::can_swipe_left() const
/*
  returns true if the grid can be swiped left
*/
{
    for (int lineNbr = 0; lineNbr < size; lineNbr++)
    //we iterate over the lines
    {
      int currentLine[size];
      int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the current line
      for (int k = 0; k < size; k++)
      {
        currentLine[k] = grid[lineNbr][k];
        if (grid[lineNbr][k] != 0)
        {
          nbrNonZero++;
        }
      }

      if (nbrNonZero == 0)
      //if the current line is empty
      {
        continue; //used to go directly to the next column
      }

      for (int columnNbr = size-1; columnNbr > -1+nbrNonZero; columnNbr--)
      //checks if there is a number different than zero at one side of the line
      //in that case, it is possible to swipe
      {
        if (currentLine[columnNbr] != 0)
        {
          return true;
        }
      }

      for (int columnNbr = 0; columnNbr < size - 1; columnNbr++)
      //checks if two tiles of same value are side-by-side
      {
        if ((currentLine[columnNbr] == currentLine[columnNbr+1]) and (currentLine[columnNbr] != 0))
        {
          return true;
        }
      }
    }
  return false;
}

bool Game::can_swipe(int direction) const
/*
  returns true if the grid can be swiped in the given direction
  directions : 0 = left, 1 = down, 2 = right, 3 = up
*/
{

  if (direction == 0)
  {
    return(this->can_swipe_left());
  }

  else if (direction == 1)
  {
    return(this->can_swipe_down());
  }

  else if (direction == 2)
  {
    return(this->can_swipe_right());
  }

  else if (direction == 3)
  {
    return(this->can_swipe_up());
  }

  else
  {
    return false;
  }
}


void Game::swipe_up()
/*
  swipes the grid in the up direction, doing all the necessary additions
*/
{
  for (int columnNbr = 0; columnNbr < size; columnNbr++)
  {
    //we start by putting every tile up
    for (int lineNbr = 0; lineNbr < size; lineNbr++)
    {
      int counter = 0;
      while ((grid[lineNbr][columnNbr] == 0) && (counter < size))
      {
        counter += 1;

        int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the columnPart
        for (int k = lineNbr; k < size; k++)
        {
          if (grid[k][columnNbr] != 0)
          {
            nbrNonZero++;
          }
        }
        if (nbrNonZero != 0)
        {
          for (int remainingLine = lineNbr; remainingLine < size-1; remainingLine++)
          {
            grid[remainingLine][columnNbr] = grid[remainingLine+1][columnNbr];
          }
          grid[size-1][columnNbr] = 0;
        }
      }
    }

    // now we do the additions
    for (int lineNbr = 0; lineNbr < size-1; lineNbr++)
    {
      if (grid[lineNbr][columnNbr] == grid[lineNbr+1][columnNbr])
      {
        grid[lineNbr][columnNbr] *= 2;
        classicScore += grid[lineNbr][columnNbr];
        for (int remainingLine = lineNbr+1; remainingLine < size-1; remainingLine++)
        {
          grid[remainingLine][columnNbr] = grid[remainingLine+1][columnNbr];
        }
        grid[size-1][columnNbr] = 0;
      }
    }
  }
}

void Game::swipe_down()
/*
  swipes the grid in the down direction, doing all the necessary additions
*/
{
  for (int columnNbr = 0; columnNbr < size; columnNbr++)
  {
    //we start by putting every tile up
    for (int lineNbr = size-1; lineNbr >= 0; lineNbr--)
    {
      int counter = 0;
      while ((grid[lineNbr][columnNbr] == 0) && (counter < size))
      {
        counter += 1;

        int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the columnPart
        for (int k = lineNbr; k >= 0 ; k--)
        {
          if (grid[k][columnNbr] != 0)
          {
            nbrNonZero++;
          }
        }
        if (nbrNonZero != 0)
        {
          for (int remainingLine = lineNbr; remainingLine > 0; remainingLine--)
          {
            grid[remainingLine][columnNbr] = grid[remainingLine-1][columnNbr];
          }
          grid[0][columnNbr] = 0;
        }
      }
    }

    // now we do the additions
    for (int lineNbr = size-1; lineNbr > 0; lineNbr--)
    {
      if (grid[lineNbr][columnNbr] == grid[lineNbr-1][columnNbr])
      {
        grid[lineNbr][columnNbr] *= 2;
        classicScore += grid[lineNbr][columnNbr];
        for (int remainingLine = lineNbr-1; remainingLine > 0; remainingLine--)
        {
          grid[remainingLine][columnNbr] = grid[remainingLine-1][columnNbr];
        }
        grid[0][columnNbr] = 0;
      }
    }
  }
}

void Game::swipe_left()
/*
  swipes the grid in the left direction, doing all the necessary additions
*/
{
  for (int lineNbr = 0; lineNbr < size; lineNbr++)
  {
    //we start by putting every tile left
    for (int columnNbr = 0; columnNbr < size; columnNbr++)
    {
      int counter = 0;
      while ((grid[lineNbr][columnNbr] == 0) && (counter < size))
      {
        counter += 1;

        int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the columnPart
        for (int k = columnNbr; k < size; k++)
        {
          if (grid[lineNbr][k] != 0)
          {
            nbrNonZero++;
          }
        }
        if (nbrNonZero != 0)
        {
          for (int remainingColumn = columnNbr; remainingColumn < size-1; remainingColumn++)
          {
            grid[lineNbr][remainingColumn] = grid[lineNbr][remainingColumn+1];
          }
          grid[lineNbr][size-1] = 0;
        }
      }
    }

    // now we do the additions
    for (int columnNbr = 0; columnNbr < size-1; columnNbr++)
    {
      if (grid[lineNbr][columnNbr] == grid[lineNbr][columnNbr+1])
      {
        grid[lineNbr][columnNbr] *= 2;
        classicScore += grid[lineNbr][columnNbr];
        for (int remainingColumn = columnNbr+1; remainingColumn < size-1; remainingColumn++)
        {
          grid[lineNbr][remainingColumn] = grid[lineNbr][remainingColumn+1];
        }
        grid[lineNbr][size-1] = 0;
      }
    }
  }
}

void Game::swipe_right()
/*
  swipes the grid in the right direction, doing all the necessary additions
*/
{
  for (int lineNbr = 0; lineNbr < size; lineNbr++)
  {
    //we start by putting every tile left
    for (int columnNbr = size-1; columnNbr >= 0; columnNbr--)
    {
      int counter = 0;
      while ((grid[lineNbr][columnNbr] == 0) && (counter < size))
      {
        counter += 1;

        int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the columnPart
        for (int k = columnNbr; k >=0 ; k--)
        {
          if (grid[lineNbr][k] != 0)
          {
            nbrNonZero++;
          }
        }
        if (nbrNonZero != 0)
        {
          for (int remainingColumn = columnNbr; remainingColumn > 0; remainingColumn--)
          {
            grid[lineNbr][remainingColumn] = grid[lineNbr][remainingColumn-1];
          }
          grid[lineNbr][0] = 0;
        }
      }
    }

    // now we do the additions
    for (int columnNbr = size-1; columnNbr > 0; columnNbr--)
    {
      if (grid[lineNbr][columnNbr] == grid[lineNbr][columnNbr-1])
      {
        grid[lineNbr][columnNbr] *= 2;
        classicScore += grid[lineNbr][columnNbr];
        for (int remainingColumn = columnNbr-1; remainingColumn > 0; remainingColumn--)
        {
          grid[lineNbr][remainingColumn] = grid[lineNbr][remainingColumn-1];
        }
        grid[lineNbr][0] = 0;
      }
    }
  }
}


void Game::swipe(int direction)
/*
  swipes the grid in the given direction, doing all the necessary additions
  directions : 0 = left, 1 = down, 2 = right, 3 = up
*/
{
  if (direction == 0)
  {
    this->swipe_left();
  }

  else if (direction == 1)
  {
    this->swipe_down();
  }

  else if (direction == 2)
  {
    this->swipe_right();
  }

  else if (direction == 3)
  {
    this->swipe_up();
  }
  else
  {
    printf("ERROR\n");
  }

}


void Game::add_random_nbr()
/*
  adds a 2 with probability 9/10 or a 4 with probability 1/10, on a tile that is empty
  if no tile is available, adds nothing and the game will end in the main loop at next iteration
*/
{
  // we pick out the random number : 2 or 4
  int randomNbr;
  if (my_random(0, 9) == 1) //generates random nbr between 1 and 10
  {
    randomNbr = 4;
  }
  else
  {
    randomNbr = 2;
  }

  // we pick a random (available) position for the number
  int nbrEmptyTiles = 0;
  for (int k = 0; k < size; k++)
  {
    for (int i = 0; i < size; i++)
    {
      if (grid[k][i] == 0)
      {
        nbrEmptyTiles += 1;
      }
    }
  }
  int randomPositionCounter = my_random(0, nbrEmptyTiles-1);

  //we put the randomNbr at the randomPosition
  for (int k = 0; k < size; k++)
  {
    for (int i = 0; i < size; i++)
    {
      if (grid[k][i] == 0)
      {
        if (randomPositionCounter == 0)
        {
          grid[k][i] = randomNbr;
        }
        randomPositionCounter -= 1;
      }
    }
  }
}


bool Game::is_finished() const
/*
  returns true if grid is full, false otherwise
*/
{
  //checks if there are some possible moves
  for (int i = 3; i >= 0; i--)
  {
    if (this->can_swipe(i))
    {
      return (false);
    }
  }
  return (true);
}

int Game::get_classic_score()
/*
  getter for classicScore
*/
{
  return (classicScore);
}

int Game::get_my_score()
/*
  getter for the score I use (ie sum of tiles)
*/
{
  return (double_sum(grid));
}

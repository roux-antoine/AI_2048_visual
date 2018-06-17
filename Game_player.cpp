#include "Game_player.h"


Game_player::Game_player(int givenSize) : Game(givenSize)
{
}


void Game_player::play()
/*
  main loop in which the game is played
*/
{
  //initialization of the start grid
  this->add_random_nbr();
  this->add_random_nbr();
  this->print();

  while(!this->is_finished())
  {
    int direction = get_direction();

    if (this->can_swipe(direction))
    {
      this->swipe(direction);
      this->add_random_nbr();
    }
    this->print();
  }
}


int Game_player::get_direction()
// returns the direction pressed on keyboard by user
{
  char input;
  std::cin >> input;
  if (input == 'q') //left
  {
    return (0);
  }

  else if (input == 'w') //down
  {
    return (1);
  }

  else if (input == 's') //right
  {
    return (2);
  }

  else if (input == 'z') //up
  {
    return (3);
  }

  else
  {
    return (-1);
  }
}

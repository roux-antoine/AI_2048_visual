#include "Game_player.hpp"


Game_player::Game_player(int size) : Game(size)
{
}

void Game_player::play()
// main loop in which the game is played
{
  this->add_random_nbr();
  this->add_random_nbr();

  while(!this->is_finished())
  {
    this->print();
    int direction = get_direction();
    if (this->can_swipe(direction))
    {
      this->swipe(direction);
      this->add_random_nbr();
    }
  }
  printf("Game finished !\n\n");
  this->print();
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

    else if (input == 's') //down
    {
      return (2);
    }

    else if (input == 'z') //down
    {
      return (3);
    }

    else
    {
      return (0);
    }
  }

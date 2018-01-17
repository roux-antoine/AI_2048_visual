// #include <vector>
// #include <stdlib.h>
// #include <iostream>
// #include <random>
// #include "tools.cpp"

#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

class Game_player : public Game
{


public:

  explicit Game_player(int size);


  int get_direction();


private:

  void play();
  // main loop in which the game is played




};

#endif

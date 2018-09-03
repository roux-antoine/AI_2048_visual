
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Game.h"

class Game_player : public Game
{
private:
  int get_direction(int depth);


public:

  Game_player(int givenSize);
  void play();

};

#endif //GAME_PLAYER_H

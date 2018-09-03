
#ifndef GAME_AI_H
#define GAME_AI_H

#include "AI.h"
#include "Game.h"

class Game_AI : public Game
{

private:

  int compute_fitness() const;
  int get_direction(int depth);
  int get_direction_1();
  int get_direction_2();
  int get_direction_3();
  int get_direction_4();
  int get_direction_5();
  int get_direction_6();
  int depth;

public:

  AI myAI;
  Game_AI(int givenSize, AI givenAI);
  void play();


};

#endif //GAME_AI_H

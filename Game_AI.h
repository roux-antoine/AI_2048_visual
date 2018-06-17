
#ifndef GAME_AI_H
#define GAME_AI_H

#include "AI.h"
#include "Game.h"

class Game_AI : public Game
{

private:

  int compute_fitness() const;
  int get_direction();


public:

  AI myAI;
  Game_AI(int givenSize, AI givenAI);
  void play();


};

#endif //GAME_AI_H

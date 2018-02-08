
#ifndef GAME_AI_HPP
#define GAME_AI_HPP

#include "AI.hpp"

class Game_AI : public Game
{
private:

  int compute_fitness();

public:

  AI myAI;
  Game_AI(int givenSize, AI givenAI);
  void play();
  int get_direction();


};

#endif

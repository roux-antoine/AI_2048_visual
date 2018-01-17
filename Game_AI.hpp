// #include <vector>
// #include <stdlib.h>
// #include <iostream>
// #include <random>
// #include "tools.cpp"

#ifndef GAME_AI_HPP
#define GAME_AI_HPP

#include "AI.hpp"

class Game_AI : public Game
{

public:

  AI myAI;

  Game_AI(int givenSize, AI givenAI);

  void play();
  // main loop in which the game is played

  int get_direction();


private:

  int compute_fitness();


};

#endif

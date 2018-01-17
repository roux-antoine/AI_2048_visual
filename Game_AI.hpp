// #include <vector>
// #include <stdlib.h>
// #include <iostream>
// #include <random>
// #include "tools.cpp"
#include "AI.hpp"

class Game_AI : public Game
{

public:

  AI myAI;

  Game_AI(int givenSize/*, AI givenAI*/);

  void play();
  // main loop in which the game is played

  int get_direction();





private:

  // std::vector<std::vector<int> > fitnessGrid;

  // void initiate_fitness_grid(int method);

  int compute_fitness();




};

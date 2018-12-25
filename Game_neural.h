
#ifndef Game_neural_H
#define Game_neural_H

#include "Neural_net.h"
#include "Game.h"

class Game_neural : public Game
{

private:

  int compute_fitness();
  int get_direction(int depth);
  int get_direction_1();
  int get_direction_2();
  int get_direction_3();
  int get_direction_4();
  int get_direction_5();
  int get_direction_6();
  int depth;

public:

  Neural_net myNeuralNet;
  Game_neural(int givenSize, int givenDepth, Neural_net givenNeuralNet);
  void play();


};

#endif //Game_neural_H

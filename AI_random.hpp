#ifndef AI_RANDOM_HPP
#define AI_RANDOM_HPP

#include <vector>

class AI_random : public AI
{
private:

  void fill_fitness_grid(int fitnessParameter = 25);

public:

  AI_random();
  AI_random(int size, int fitnessParameter = 25);


};

#endif

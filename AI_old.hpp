#ifndef AI_HPP
#define AI_HPP

#include <vector>

class AI {
public:
  std::vector<std::vector<int> > fitnessGrid;
  int fitness;
  int gridDimension;

  // AI();

  // AI(int size);

  void fill_fitness_grid();

};

#endif

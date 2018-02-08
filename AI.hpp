
#ifndef AI_HPP
#define AI_HPP

#include <vector>

class AI
{
private:

  void fill_fitness_grid();

public:

  std::vector<std::vector<int> > fitnessGrid;
  int fitness; //really need one?
  int gridDimension;

  AI();
  AI(int size);


};

#endif

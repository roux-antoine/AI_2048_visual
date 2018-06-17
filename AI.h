#ifndef AI_H
#define AI_H

#include <vector>
#include "tools.h"

class AI
{
private:

  void fill_fitness_grid();

protected:
  int gridDimension;

public:

  std::vector<std::vector<int> > fitnessGrid;

  AI();
  AI(int size);
  int get_grid_dimension() const;

};

#endif //AI_H

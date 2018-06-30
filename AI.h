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
  int depth;

public:

  std::vector<std::vector<int> > weightsGrid;

  AI();
  AI(int size, int givenDepth);
  int get_grid_dimension() const;
  int get_depth() const;

};

#endif //AI_H

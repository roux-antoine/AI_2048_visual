#ifndef ia_HPP
#define ia_HPP

#include <vector>

class AI {
private:
  std::vector<float> fitnessGrid;
  float fitness;
  int gridDimension;

public:
  AI();
  AI(int);
};

#endif

#ifndef ia_HPP
#define ia_HPP

#include <vector>

class IA {
private:
  std::vector<float> fitnessGrid;
  float fitness;
  int gridDimension;

public:
  IA();
  IA(int);
  int chooseDirection() {};
};

#endif

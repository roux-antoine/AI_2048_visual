#include <vector>

class IA {
private:
  std::vector<float> fitnessGrid;
  float fitness;
  int gridDimension;

public:
  IA() {
    gridDimension = 4;
  }
  IA(int dim) {
    gridDimension = dim;
  }
  int chooseDirection() {return 0;}
}

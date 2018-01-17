#include <vector>

class AI {
private:
  std::vector<float> fitnessGrid;
  float fitness;
  int gridDimension;

public:
  AI() {
    gridDimension = 4;
  }
  AI(int dim) {
    gridDimension = dim;
  }
}

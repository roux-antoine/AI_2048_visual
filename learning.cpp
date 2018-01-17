#include <vector>

class Learning {
private:
  int maxDuration;
  std::vector<std::vector<int>> grid;
  //TODO Object learningValues;

public:
  Learning() {
    maxDuration = 10;
    grid.push_back(std::vector<int>(4,0));
    grid.push_back(std::vector<int>(4,0));
    grid.push_back(std::vector<int>(4,0));
    grid.push_back(std::vector<int>(4,0));
  }
  Learning(std::vector<std::vector<int>>& a) {
    maxDuration = 10;
    grid = *a;
  }
  virtual void execute() =0;
}

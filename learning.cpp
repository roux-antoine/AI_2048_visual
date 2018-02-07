#include "learning.hpp"

Learning::Learning()
{
  maxDuration = 10;
  grid.push_back(std::vector<int>(4,0));
  grid.push_back(std::vector<int>(4,0));
  grid.push_back(std::vector<int>(4,0));
  grid.push_back(std::vector<int>(4,0));
}

Learning::Learning(std::vector<std::vector<int>>& a) {
  maxDuration = 10;
  grid = *a;
}

virtual void Learning::execute() = 0;

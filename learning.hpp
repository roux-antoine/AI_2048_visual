#ifndef LEARNING_HPP
#define LEARNING_HPP

#include <vector>

class Learning
{
private:
  int maxDuration;
  std::vector<std::vector<int> > grid;

public:
  Learning();
  Learning(std::vector<std::vector<int> >& a);
  virtual void execute();
};

#endif

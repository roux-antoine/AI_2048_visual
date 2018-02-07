#ifndef learning_HPP
#define learning_HPP

#include <vector>

class Learning
{
private:
  int maxDuration;
  std::vector<std::vector<int> > grid;
  //TODO Object learningValues;

public:
  Learning();
  Learning(std::vector<std::vector<int> >& a);
  virtual void execute();
};

#endif

#ifndef AI_HC_HPP
#define AI_HC_HPP

#include <vector>

class AI_hc : public AI
{
public:

  // std::vector<std::vector<int> > fitnessGrid;
  // int fitness; //really need one?
  // int gridDimension;

  AI_hc();

  AI_hc(int size);

  void fill_fitness_grid();

};

#endif

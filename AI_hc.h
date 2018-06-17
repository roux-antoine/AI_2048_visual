#ifndef AI_HC_HPP
#define AI_HC_HPP

#include <vector>
#include "AI.h"

class AI_hc : public AI
{
private:

  void fill_weights_grid();

public:

  AI_hc();
  AI_hc(int size);
  AI_hc(int size, std::vector<std::vector<int> > givenWeightsGrid);

};

#endif

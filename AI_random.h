#ifndef AI_RANDOM_H
#define AI_RANDOM_H

#include "AI.h"
#include "tools.h"

class AI_random : public AI
{
private:

  void fill_weights_grid();

public:

  AI_random();
  AI_random(int size);


};

#endif //AI_RANDOM_H

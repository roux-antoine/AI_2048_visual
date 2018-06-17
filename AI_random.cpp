#include "AI_random.h"

AI_random::AI_random(int size) : AI(size)
{
  fill_weights_grid();
}

AI_random::AI_random() : AI()
{
  fill_weights_grid();
}

void AI_random::fill_weights_grid()
/*
  fills the fitnessGrid with random nbrs
  the nbrs are randomly chosen between 0 and fitnessParameter
*/
{
  for(int k = 0; k < gridDimension; k++)
  {
    for(int i = 0; i < gridDimension; i++)
    {
      weightsGrid[k][i] = my_random(0, 50); //arbitrary parameter, has no influence
    }
  }
}

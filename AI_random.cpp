#include "AI_random.h"

AI_random::AI_random(int size) : AI(size)
{
  fill_fitness_grid();
}

AI_random::AI_random() : AI()
{
  fill_fitness_grid();
}

void AI_random::fill_fitness_grid()
/*
  fills the fitnessGrid with random nbrs
  the nbrs are randomly chosen between 0 and fitnessParameter
*/
{
  for(int k = 0; k < gridDimension; k++)
  {
    for(int i = 0; i < gridDimension; i++)
    {
      fitnessGrid[k][i] = my_random(0, 50); //arbitrary parameter, has no influence
    }
  }
}

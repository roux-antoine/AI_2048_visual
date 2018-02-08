#include <vector>
#include "AI_hc.hpp"

AI_hc::AI_hc(int size) : AI(size)
{
  fill_fitness_grid();
}

AI_hc::AI_hc() : AI()
{
  fill_fitness_grid();
}

void AI_hc::fill_fitness_grid()
//fills the fitnessGrid with numbers in an ordered way
//from the bottom left 
{
  for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[k][0] = 13+k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[k][1] = 12-k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[k][2] = 5+k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[k][3] = 4-k;
    }
}

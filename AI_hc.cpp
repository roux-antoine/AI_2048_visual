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
{

  for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[0][k] = 13+k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[1][k] = 12-k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[2][k] = 5+k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      fitnessGrid[3][k] = 4-k;
    }

}

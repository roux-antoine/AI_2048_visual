
#include <vector>
#include "AI.hpp"

AI::AI(int size)
{
  gridDimension = size;

  for (int k = 0 ; k < gridDimension ; k++)
  {
    fitnessGrid.push_back(std::vector<int>(gridDimension,0));
  }

  fill_fitness_grid();
}

AI::AI()
{
  gridDimension = 4;

  for (int k = 0 ; k < gridDimension ; k++)
  {
    fitnessGrid.push_back(std::vector<int>(gridDimension,0));
  }

  fill_fitness_grid();
}

void AI::fill_fitness_grid()
{
  
}

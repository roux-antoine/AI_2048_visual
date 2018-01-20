#include <vector>
#include "AI_random.hpp"

AI_random::AI_random(int size, int fitnessParameter) : AI(size)
{
  fill_fitness_grid(fitnessParameter);
}

AI_random::AI_random() : AI()
{
  fill_fitness_grid();
}

void AI_random::fill_fitness_grid(int fitnessParameter)
{

  for(int k = 0; k < gridDimension; k++)
  {
    for(int i = 0; i < gridDimension; i++)
    {
      fitnessGrid[k][i] = my_random(0, fitnessParameter);
    }
  }


}

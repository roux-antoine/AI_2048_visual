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
// fills the fitnessGrid with random nbrs
//the nbrs are randomly chosen between 0 and fitnessParameter
{
  for(int k = 0; k < gridDimension; k++)
  {
    for(int i = 0; i < gridDimension; i++)
    {
      fitnessGrid[k][i] = my_random(0, fitnessParameter);
    }
  }

  // for (int k = 0; k < gridDimension; k++)
  //   {
  //     fitnessGrid[k][0] = 13+k;
  //   }
  //   for (int k = 0; k < gridDimension; k++)
  //   {
  //     fitnessGrid[k][1] = 12-k;
  //   }
  //   for (int k = 0; k < gridDimension; k++)
  //   {
  //     fitnessGrid[k][2] = 5+k;
  //   }
  //   for (int k = 0; k < gridDimension; k++)
  //   {
  //     fitnessGrid[k][3] = 4-k;
  //   }

  // for(int k = 0; k < gridDimension; k++)
  // {
  //   for(int i = 0; i < gridDimension; i++)
  //   {
  //     fitnessGrid[k][i] += my_random(-fitnessParameter/4, fitnessParameter/4);
  //   }
  // }


}

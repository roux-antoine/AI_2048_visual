#include "AI_hc.h"


AI_hc::AI_hc() : AI()
/*
  initialises fitnessGrid with the hard-coded one
*/
{
  fill_fitness_grid();
}

AI_hc::AI_hc(int size) : AI(size)
/*
  initialises fitnessGrid with the hard-coded one
*/
{
  fill_fitness_grid();
}

AI_hc::AI_hc(int size, std::vector<std::vector<int> > givenFitnessGrid) : AI(size)
/*
  initialises fitnessGrid with the givenFitnessGrid
*/
{
    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
           fitnessGrid[i][k] = givenFitnessGrid[i][k];
        }
    }
}

void AI_hc::fill_fitness_grid()
/*
  fills the fitnessGrid with numbers in an ordered way
  from the bottom left to the bottom right
*/
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



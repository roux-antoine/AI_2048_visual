#include "AI_hc.h"


AI_hc::AI_hc() : AI()
/*
  initialises fitnessGrid with the hard-coded one
*/
{
  fill_weights_grid();
}

AI_hc::AI_hc(int size, int givenDepth) : AI(size, givenDepth)
/*
  initialises fitnessGrid with the hard-coded one
*/
{
  fill_weights_grid();
}

AI_hc::AI_hc(int size, std::vector<std::vector<int> > givenWeightsGrid, int givenDepth) : AI(size, givenDepth)
/*
  initialises fitnessGrid with the givenFitnessGrid
*/
{
    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
           weightsGrid[i][k] = givenWeightsGrid[i][k];
        }
    }
}

void AI_hc::fill_weights_grid()
/*
  fills the fitnessGrid with numbers in an ordered way
  from the bottom left to the bottom right
*/
{
  for (int k = 0; k < gridDimension; k++)
    {
      weightsGrid[k][0] = 13+k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      weightsGrid[k][1] = 12-k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      weightsGrid[k][2] = 5+k;
    }
    for (int k = 0; k < gridDimension; k++)
    {
      weightsGrid[k][3] = 4-k;
    }
}

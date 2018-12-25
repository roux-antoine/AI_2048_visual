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

    ////
    // uncomment below to have an AI that puts the tiles in perfect diagonal -> does not perform well
    // weightsGrid[3][0] = 64;
    // weightsGrid[2][0] = 32;
    // weightsGrid[1][0] = 16;
    // weightsGrid[0][0] = 8;
    //
    // weightsGrid[3][1] = 32;
    // weightsGrid[2][1] = 16;
    // weightsGrid[1][1] = 8;
    // weightsGrid[0][1] = 4;
    //
    // weightsGrid[3][2] = 16;
    // weightsGrid[2][2] = 8;
    // weightsGrid[1][2] = 4;
    // weightsGrid[0][2] = 2;
    //
    // weightsGrid[3][3] = 8;
    // weightsGrid[2][3] = 4;
    // weightsGrid[1][3] = 2;
    // weightsGrid[0][3] = 1;

    ////

    // uncomment below to have an AI puts some semi-ordered values (performs ok)
    // weightsGrid[3][0] = 41;
    // weightsGrid[2][0] = 35;
    // weightsGrid[1][0] = 32;
    // weightsGrid[0][0] = 30;
    //
    // weightsGrid[3][1] = 12;
    // weightsGrid[2][1] = 13;
    // weightsGrid[1][1] = 14;
    // weightsGrid[0][1] = 20;
    //
    // weightsGrid[3][2] = 9;
    // weightsGrid[2][2] = 7;
    // weightsGrid[1][2] = 6;
    // weightsGrid[0][2] = 5;
    //
    // weightsGrid[3][3] = 0;
    // weightsGrid[2][3] = 1;
    // weightsGrid[1][3] = 2;
    // weightsGrid[0][3] = 3;
    //
    // for (int x = 0; x < 4; x++)
    // {
    //   for (int y = 0; y < 4; y++)
    //   {
    //     printf("%d ", weightsGrid[x][y]);
    //   }
    //   printf("\n");
    // }

}

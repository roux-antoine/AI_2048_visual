#include "AI.h"

AI::AI(int size, int givenDepth)
/*
  Initializes the fitnessGrid and the
*/

{
  gridDimension = size;
  depth = givenDepth;


  for (int k = 0 ; k < gridDimension ; k++)
  {
    weightsGrid.push_back(std::vector<int>(gridDimension,0));
  }
}

AI::AI()
/*
  Initializes the fitnessGrid
*/
{
  gridDimension = 4;
  depth = 2;

  for (int k = 0 ; k < gridDimension ; k++)
  {
    weightsGrid.push_back(std::vector<int>(gridDimension,0));
  }
}

int AI::get_grid_dimension() const
/*
  getter for gridDimension
*/
{
    return gridDimension;
}

int AI::get_depth() const
/*
  getter for gridDimension
*/
{
    return depth;
}

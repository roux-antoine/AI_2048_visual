#include "AI.h"

AI::AI(int size)
/*
  Initializes the fitnessGrid and the
*/

{
  gridDimension = size;

  for (int k = 0 ; k < gridDimension ; k++)
  {
    fitnessGrid.push_back(std::vector<int>(gridDimension,0));
  }
}

AI::AI()
/*
  Initializes the fitnessGrid
*/
{
  gridDimension = 4;

  for (int k = 0 ; k < gridDimension ; k++)
  {
    fitnessGrid.push_back(std::vector<int>(gridDimension,0));
  }
}

int AI::get_grid_dimension() const
/*
  getter for gridDimension
*/
{
    return gridDimension;
}

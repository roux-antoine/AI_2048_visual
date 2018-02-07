
#include "Learning_stats.hpp"


Learning_stats::Learning_stats()
{
  //INUTILE car on aura juste à push_back dans les append
  // bestFitnesses = std::vector<int>(nbGenerations, 0);
  // averageFitnesses = std::vector<int>(nbGenerations, 0);
  //
  // std::vector<std::vector<std::vector<int> > > bestFitnessGrids;
  //
  // std::vector<std::vector<int> > emptyGrid;
  // for (int k = 0 ; k < gridSize ; k++)
  // {
  //   emptyGrid.push_back(std::vector<int>(gridDimension,0));
  // }
  //
  // for (int k = 0 ; k < gridSize ; k++)
  // {
  //   emptyGrid.push_back(emptyGrid);
  // }

}

void Learning_stats::appendBestFitness(int fitness)
{
  bestFitnesses.push_back(fitness);
}


void Learning_stats::appendAverageFitness(int fitness)
{
  averageFitnesses.push_back(fitness);
}


void Learning_stats::appendBestFitnessGrids (std::vector<std::vector<int> > fitnessGrid)
{
  bestFitnessGrids.push_back(fitnessGrid);

}

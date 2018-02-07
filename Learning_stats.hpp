#ifndef LEARNING_STATS_HPP
#define LEARNING_STATS_HPP


#include <vector>


class Learning_stats
{
private:


public:
  Learning_stats();
  void appendBestFitness(int fitness);
  void appendAverageFitness(int fitness);
  void appendBestFitnessGrids (std::vector<std::vector<int> > fitnessGrid);

  std::vector<int> bestFitnesses;
  std::vector<int> averageFitnesses;
  std::vector<std::vector<std::vector<int> > > bestFitnessGrids;


};





#endif

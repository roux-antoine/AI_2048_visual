#ifndef LEARNING_STATS_HPP
#define LEARNING_STATS_HPP


#include <vector>
#include <fstream>
#include <iostream>


class Learning_stats
{
private:

  std::vector<int> bestFitnesses;
  std::vector<int> averageFitnesses;
  std::vector<std::vector<std::vector<int> > > bestFitnessGrids;

public:
  Learning_stats();
  void appendBestFitness(int fitness);
  void appendAverageFitness(int fitness);
  void appendBestFitnessGrids (std::vector<std::vector<int> > fitnessGrid);

  void writeToFile(char* fileName) const;

};





#endif

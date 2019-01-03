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

public:
  Learning_stats();
  void append_best_fitness(int fitness);
  void append_average_fitness(int fitness);
  void write_stats_to_file(char* fileName) const;

};





#endif

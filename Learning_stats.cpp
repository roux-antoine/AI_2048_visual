#include "Learning_stats.h"

Learning_stats::Learning_stats()
{
}

void Learning_stats::append_best_fitness(int fitness)
//append the given fitness to the vector bestFitnesses
{
  bestFitnesses.push_back(fitness);
}


void Learning_stats::append_average_fitness(int fitness)
//append the given fitness to the vector averageFitnesses
{
  averageFitnesses.push_back(fitness);
}


void Learning_stats::write_stats_to_file(char* fileName) const
//writes the stats to a txt file
//the name of the file is created using the date and time
{
  std::ofstream myFile;

  myFile.open(fileName); 

  myFile << "Best fitnesses,Average fitnesses\n";
  for (int i = 0; i < (int)bestFitnesses.size(); i++)
  {
    myFile << bestFitnesses[i] << ","  << averageFitnesses[i]  << "\n";
  }

  myFile.close();
}

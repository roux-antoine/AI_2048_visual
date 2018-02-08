
#include "Learning_stats.hpp"
#include <ctime>
#include <chrono>


Learning_stats::Learning_stats()
{
}

void Learning_stats::appendBestFitness(int fitness)
//append the given fitness to the vector bestFitnesses
{
  bestFitnesses.push_back(fitness);
}


void Learning_stats::appendAverageFitness(int fitness)
//append the given fitness to the vector averageFitnesses
{
  averageFitnesses.push_back(fitness);
}


void Learning_stats::appendBestFitnessGrids (std::vector<std::vector<int> > fitnessGrid)
//append the given fitnessGrid to the vector bestFitnessGrids
{
  bestFitnessGrids.push_back(fitnessGrid);
}

void Learning_stats::writeToFile() const
//writes the stats to a txt file
//the name of the file is created using the date and time
{
  std::ofstream myFile;

  auto start = std::chrono::system_clock::now();
  std::time_t timeNow = std::chrono::system_clock::to_time_t(start);
  char fileName[100];   // array to hold the result.
  strcpy(fileName, std::ctime(&timeNow));
  strcat(fileName, ".txt");

  myFile.open (fileName); //the name of the file corresponds to the date and time

  myFile << "Best fitnesses\n";
  for (int i = 0; i < (int)bestFitnesses.size(); i++)
  {
    myFile << bestFitnesses[i] << " ";
  }

  myFile << "\n\n";

  myFile << "Average fitnesses\n";
  for (int i = 0; i < (int)averageFitnesses.size(); i++)
  {
    myFile << averageFitnesses[i] << " ";
  }
  myFile << "\n\n";

  myFile << "Best individual fitness grid\n";
  for (int k = 0; k < (int)bestFitnessGrids.size(); k++)
  {
    for (int i = 0; i < bestFitnessGrids[k].size(); i++)
    {
      for (int j = 0; j < bestFitnessGrids[k].size(); j++)
      {
        myFile << bestFitnessGrids[k][i][j] << " ";
      }
      myFile << "\n";
    }
    myFile << "\n";
  }
  myFile << "\n\n";
  myFile.close();

}

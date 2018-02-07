#ifndef GENETIC_LEARNING_HPP
#define GENETIC_LEARNING_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include <thread>

#include "Learning.hpp"
#include "AI.hpp"
#include "Learning_stats.hpp"

class GeneticLearning /*: public Learning*/
{
private:
  std::vector<AI> generation;
  std::vector<int> fitnesses;
  int gridSize;
  int nbGeneration;
  int nbIndiv;
  int nbEvalPerIndiv;
  double selectionRateBest;
  double selectionRateOthers;
  double mutationProba;
  bool threadedEnabled;

public:
  GeneticLearning();
  GeneticLearning(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, bool threadedE);
  void execute(Learning_stats* stats);
  void evaluation_thread(int nbrOfThreads);
  void evaluation_thread_base(int threadNbr, int start, int end);
  void evaluation();
  std::vector<int> selection();
  void reproduction(std::vector<int>);
  void mutation();
  AI getBestAI();
  int getBestFitness();
  int getAverageFitness();
};

#endif

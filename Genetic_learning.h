#ifndef GENETIC_LEARNING_H
#define GENETIC_LEARNING_H

#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <cstring>

#include "AI.h"
#include "AI_random.h"
#include "AI_hc.h"
#include "Game_AI.h"
#include "Learning_stats.h"
#include "tools.h"


class Genetic_learning
{

private:
  std::vector<AI> generation;
  std::vector<int> fitnesses;
  int gridSize;
  int nbGenerations;
  int nbIndiv;
  int nbEvalPerIndiv;
  double selectionRateBest;
  double selectionRateOthers;
  double mutationProba;
  int nbrOfThreads;
  bool stopFlag;
  int depth;

  void evaluation_threaded(int nbrOfThreads);
  void evaluation_thread_base(int start, int end);
  void evaluation_non_threaded();
  std::vector<int> selection();
  void reproduction(std::vector<int>);
  void mutation();
  void write_config_to_file(char* filename);

public:
  Genetic_learning();
  Genetic_learning(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfThreads, int givenDepth);
  void execute(Learning_stats* stats);
  AI get_best_AI();
  int get_best_fitness();
  int get_average_fitness() const;

};

#endif //GENETIC_LEARNING_H

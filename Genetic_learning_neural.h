#ifndef GENETIC_LEARNING_NEURAL_H
#define GENETIC_LEARNING_NEURAL_H

#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <cstring>

#include "Neural_net.h"
#include "Game_neural.h"
#include "Learning_stats.h"
#include "tools.h"


class Genetic_learning_neural
{

private:
  std::vector<Neural_net> generation;
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
  int nn_nbrLayers;
  std::vector<int> nn_layersSizes;
  std::vector<int> nn_nonLinearities;
  int initializationMode; //0 if random initialization, 1 if hardcoded initialization

  void evaluation_threaded(int nbrOfThreads);
  void evaluation_thread_base(int start, int end);
  void evaluation_non_threaded();
  std::vector<int> selection();
  void reproduction(std::vector<int>);
  void mutation();
  void write_config_to_file(char* filename);
  void play_N_games_and_print_best();

public:
  // Genetic_learning_neural();
  Genetic_learning_neural(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfThreads, int givenDepth, std::vector<int> nn_layersS, std::vector<int> nn_nonL);
  Genetic_learning_neural(int gridS, int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP, int nbrOfThreads, int givenDepth);
  void execute(Learning_stats* stats);
  Neural_net get_best_neural_net();
  int get_best_fitness();
  int get_average_fitness() const;

};

#endif //GENETIC_LEARNING_H

#ifndef genetic_learning_HPP
#define genetic_learning_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include <thread>

#include "learning.hpp"
#include "AI.hpp"

class GeneticLearning /*: public Learning*/ {
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
  void execute();
  void evaluation_thread(int nbrOfThreads);
  void evaluation_thread_base(int threadNbr, int start, int end);
  void evaluation();
  std::vector<int> selection();
  void reproduction(std::vector<int>);
  void mutation();
  AI get_best_AI();
  int get_best_fitness();
};

#endif

#ifndef genetic_learning_HPP
#define genetic_learning_HPP

#include <iostream>
#include <vector>
#include <math.h>

#include "learning.hpp"
#include "AI.hpp"

class GeneticLearning /*: public Learning*/ {
private:
  std::vector<AI> generation;
  std::vector<int> fitnesses;
  int nbGeneration;
  int nbIndiv;
  int nbEvalPerIndiv;
  double selectionRate; // peut etre à renommer en selectionRateBest
  double selectionOthers; // peut etre à renommer en selectionRateOthers
  double mutationProba;

public:
  GeneticLearning();
  GeneticLearning(int nbG, int nbI, int nbE, double selectionR, double selectionO, double mutationP);
  void execute();
  void evalutation();
  std::vector<int> selection();
  void reproduction(std::vector<int>);
  void mutation();
  AI get_best_AI();
  int get_best_fitness();
};

#endif

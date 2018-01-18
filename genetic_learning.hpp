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
  double selectionRate;
  double selectionOthers;
  double mutationProba;

public:
  GeneticLearning();
  GeneticLearning(int, int, int, double, double, double);
  void execute();
  void evalutation();
  std::vector<int>* selection();
  void reproduction(std::vector<int>*);
  void mutation(std::vector<int>*);
  AI get_best_AI();
  int get_best_fitness();
};

#endif

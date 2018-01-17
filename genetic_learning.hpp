#ifndef genetic_learning_HPP
#define genetic_learning_HPP

#include <iostream>
#include <vector>
#include <math.h>

#include "learning.hpp"
#include "AI.hpp"
#include "tools.cpp"

class GeneticLearning : public Learning {
private:
  std::vector<IA> generation;
  std::vector<float> fitnesses;
  int nbGeneration;
  int nbIndiv;
  int nbEvalPerIndiv;
  double selectionRate;
  double selectionOthers;
  double mutationProba;

public:
  GeneticLearning();
  GeneticLearning(int, int, int, double);
  void execute();
  int evalutation();
  void selection();
  void reproduction();
  void mutation();
};

#endif

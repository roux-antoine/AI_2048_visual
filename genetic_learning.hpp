#ifndef genetic_learning_HPP
#define genetic_learning_HPP

#include <vector>

#include "learning.hpp"
#include "ia.hpp"

class GeneticLearning : public Learning {
private:
  std::vector<IA> generation;
  int nbGeneration;
  int nbIndiv;
  int nbEvalPerIndiv;
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

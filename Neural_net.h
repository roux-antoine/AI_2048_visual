#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include "tools.h"


/*
  This is a standard neural net structure
  the equivalent of the weightsGrid has to be public fo the genetic algo to work
  The 'weights' is a vector of vectors of vectors (ie a list of matrices) that represents the weights associated with each layer
  The input vector must be of size gridSize * gridSize
  The last layer must output a single number, representing the fitness of the input grid
  The 'nonLinearities' is a vector of integers, where each integer represents a non linearity (0 = linear, 1 = ReLU, 2 = tanh)
  -> tanh does not really work because it is always equal to +1 or -1
  The 'layers' is a vector of vector, with the content of each neuron

*/

class Neural_net
{
private:
  int gridSize;
  std::vector<int> layersSizes;
  std::vector<int> nonLinearities;

// protected:


public:

  std::vector<std::vector<std::vector<int>>> weights;
  std::vector<std::vector<int>> biases;
  std::vector<std::vector<int>> layers;

  Neural_net();
  Neural_net(int givenGridSize, std::vector<int> givenLayersSizes, std::vector<int> givenNonLinearities);
  void print() const;
  float forward_pass(std::vector<int> inputVector);
  void save_to_file(char* fileName) const;


  // TODO faire des getters pour les attributs privés

};


#endif

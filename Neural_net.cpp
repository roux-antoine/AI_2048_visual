#include "Neural_net.h"

Neural_net::Neural_net(int givenGridSize, int givenNbrLayers, std::vector<int> givenLayersSizes, std::vector<int> givenNonLinearities)
/*
  Constructor that randomly initializes the weights in the layers
  We should make sure that all the dimensions match
*/
{
  gridSize = givenGridSize;
  nbrLayers = givenNbrLayers;
  layersSizes = givenLayersSizes;
  nonLinearities = givenNonLinearities;


  // creating the weights
  std::vector<std::vector<int> > temp;
  for (int k = 0 ; k < nbrLayers-1 ; k++)
  {
    temp.clear();
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      temp.push_back(std::vector<int>(layersSizes[k], 0));
    }
    weights.push_back(temp);
  }

  // initializing the weights randomly
  for (int k = 0; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      for (int j = 0; j < layersSizes[k]; j++) //le deuxième correspond à la largeur de la matrice
      {
        weights[k][i][j] = my_random(-50, 50); //arbitrary parameter, has no influence
      }
    }
  }

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    biases.push_back(std::vector<int>(layersSizes[k+1],0));
  }

  // initializing the biases randomly
  for (int k = 0; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      biases[k][i] = my_random(-50, 50); //arbitrary parameter, has no influence
    }
  }

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    layers.push_back(std::vector<int>(layersSizes[k+1],0));
  }


}

Neural_net::Neural_net()
/*
  Constructor that randomly initializes the weights in the layers
  We should make sure that all the dimensions match
*/
{
  gridSize = 4;
  nbrLayers = 2;
  layersSizes = std::vector<int> {16, 1};
  nonLinearities = std::vector<int> {0};


  // creating the weights
  std::vector<std::vector<int> > temp;
  for (int k = 0 ; k < nbrLayers-1 ; k++)
  {
    temp.clear();
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      temp.push_back(std::vector<int>(layersSizes[k], 0));
    }
    weights.push_back(temp);
  }

  // initializing the weights randomly
  for (int k = 0; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      for (int j = 0; j < layersSizes[k]; j++) //le deuxième correspond à la largeur de la matrice
      {
        weights[k][i][j] = my_random(-50, 50); //arbitrary parameter, has no influence
      }
    }
  }

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    biases.push_back(std::vector<int>(layersSizes[k+1],0));
  }

  // initializing the biases randomly
  for (int k = 0; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      biases[k][i] = my_random(-50, 50); //arbitrary parameter, has no influence
    }
  }

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    layers.push_back(std::vector<int>(layersSizes[k+1],0));
  }


}


void Neural_net::print() const
/*
  prints the matrices with the weights of each layer, as well as the non linearities
*/
{
  for (int k = 0; k < nbrLayers-1; k++)
  {
    std::cout << "Layer n°" << k << "\n";
    std::cout << "Weights matrix: \n";
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      for (int j = 0; j < layersSizes[k]; j++) //le deuxième correspond à la largeur de la matrice
      {
        std::cout << weights[k][i][j] << " ";
      }
      printf("\n");
    }
    std::cout << "Biases vector: \n";
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      std::cout << biases[k][i] << ' ';
    }
    std::cout << '\n';

    std::cout << "Neurons vector: \n";
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      std::cout << layers[k][i] << ' ';
    }
    std::cout << '\n';

    std::cout << "Non linearity: ";
    if (nonLinearities[k] == 0)
    {
      std::cout << "Linear" << '\n';
    }
    else if (nonLinearities[k] == 1)
    {
      std::cout << "ReLU" << '\n';
    }
    else if (nonLinearities[k] == 2)
    {
      std::cout << "tanh" << '\n';
    }
    else
    {
      std::cout << "Non supported non linearity" << '\n';
    }

    printf("\n\n");
  }

}

float Neural_net::forward_pass(std::vector<int> inputVector)
/*
  Computes the output of the neural network
  The input must be of the same size as the network's first layer
*/
{
  float temp = 0;
  //we take care of the first layer separately
  for (int i = 0; i < layersSizes[1]; i++)
  {
    temp = 0;
    for (int j = 0; j < layersSizes[0]; j++)
    {
      temp += inputVector[j] * weights[0][i][j];
    }
    temp += biases[0][i];
    if (nonLinearities[0] == 0)
    {
      layers[0][i] = temp;
    }
    else if (nonLinearities[0] == 1)
    {
      layers[0][i] = ReLU(temp);
    }
    else if (nonLinearities[0] == 2)
    {
      layers[0][i] = tanh(temp);
    }
    else
    {
      layers[0][i] = temp;
    }
  }


  for (int k = 1; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      temp = 0;
      for (int j = 0; j < layersSizes[k]; j++)
      {
        temp += layers[k-1][j] * weights[k][i][j];
      }
      temp += biases[k][i];
      if (nonLinearities[k] == 0)
      {
        layers[k][i] = temp;
      }
      else if (nonLinearities[k] == 1)
      {
        layers[k][i] = ReLU(temp);
      }
      else if (nonLinearities[k] == 2)
      {
        layers[k][i] = tanh(temp);
      }
      else
      {
        layers[k][i] = temp;
      }

    }
  }
  return layers[nbrLayers-2][0];
}


// la première matrice est de taille 16 x 1er element du vecteur
//
// pour faire le calcul, on fait : a2 = a1 * matrice
// 1 x n = 1 x 16 * 16 x n
//
// exemple de givenLayersSizes : [16, 9, 1]




// todo : à vérifier
// Biases vector:
// 23 13 3 33 48 25 4 23 2
// Neurons vector:
// 0 0 0 0 0 0 0 0 0
// Non linearity: ReLU
//
//
// Layer n°1
// Weights matrix:
// 10 17 20 21 14 18 0 42 9
// Biases vector:
// 7
// Neurons vector:
// 0
// Non linearity: Linear
//
//
// 16221

#include "Neural_net.h"

Neural_net::Neural_net(int givenGridSize, std::vector<int> givenLayersSizes, std::vector<int> givenNonLinearities)
/*
  Constructor that randomly initializes the weights in the layers
*/
{
  gridSize = givenGridSize;
  nbrLayers = givenLayersSizes.size();
  layersSizes = givenLayersSizes;
  nonLinearities = givenNonLinearities;

  // Making sure that all the dimensions match -> this should be a proper exception...
  if (nbrLayers != nonLinearities.size()+1)
  {
    std::cout << "NBR OF LAYERS AND NON-LINEARITIES DO NOT MATCH" << '\n';
  }
  if (givenLayersSizes[0] != gridSize*gridSize)
  {
    std::cout << "SIZE OF FIRST LAYER DOES NOT MATCH GRID SIZE" << '\n';
  }

  // creating the weights
  std::vector<std::vector<float> > temp;
  for (int k = 0 ; k < nbrLayers-1 ; k++)
  {
    temp.clear();
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      temp.push_back(std::vector<float>(layersSizes[k], 0));
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
        weights[k][i][j] = (float)my_random(-10, 10) / 10; //arbitrary parameter, has no influence (maybe it has...)
      }
    }
  }

  // creating the biases
  for (int k = 0; k < nbrLayers-1; k++)
  {
    biases.push_back(std::vector<float>(layersSizes[k+1],0));
  }

  // initializing the biases randomly
  for (int k = 0; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      biases[k][i] = (float)my_random(-10, 10) / 10; //arbitrary parameter, has no influence (maybe it has...)
    }
  }

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    layers.push_back(std::vector<float>(layersSizes[k+1], 0));
  }
}

Neural_net::Neural_net()
/*
  Constructor that initializes the weights in the layers with the usual hardcoded ones
*/
{
  gridSize = 4;
  nbrLayers = 2;
  layersSizes = std::vector<int> {16, 1};
  nonLinearities = std::vector<int> {0};


  // creating the weights
  std::vector<std::vector<float> > temp;
  for (int k = 0 ; k < nbrLayers-1 ; k++)
  {
    temp.clear();
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      temp.push_back(std::vector<float>(layersSizes[k], 0));
    }
    weights.push_back(temp);
  }


  //initializing the weights with the usual hardcoded ones (snake shape)
  for (int k = 0; k < gridSize; k++)
  {
    weights[0][0][k] = 13+k;
  }
  for (int k = 0; k < gridSize; k++)
  {
    weights[0][0][k+4] = 12-k;
  }
  for (int k = 0; k < gridSize; k++)
  {
    weights[0][0][k+8] = 5+k;
  }
  for (int k = 0; k < gridSize; k++)
  {
    weights[0][0][k+12] = 4-k;
  }


  //// initializing the weights with the ones in stairs shape
  // for (int k = 0; k < nbrLayers-1; k++)
  // {
  //   for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
  //   {
  //     for (int j = 0; j < layersSizes[k]; j++) //le deuxième correspond à la largeur de la matrice
  //     {
  //       weights[k][i][j] = i+j;
  //       // weights[k][i][j] = my_random(0,16);
  //     }
  //   }
  // }
  ////////

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    biases.push_back(std::vector<float>(layersSizes[k+1],0));
  }

  // initializing the biases as 0
  for (int k = 0; k < nbrLayers-1; k++)
  {
    for (int i = 0; i < layersSizes[k+1]; i++) //le premier correspond à la hauteur de la matrice
    {
      biases[k][i] = 0;
    }
  }

  // creating the layers
  for (int k = 0; k < nbrLayers-1; k++)
  {
    layers.push_back(std::vector<float>(layersSizes[k+1],0));
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
      // std::cout << temp << '\n';
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

  // std::cout << layers[nbrLayers-2][0] << '\n';

  return layers[nbrLayers-2][0];
}


void Neural_net::save_to_file(char* fileName) const
/*
  writes the neural net weights etc to a file (same structure as the print function)
*/
{
  std::ofstream myFile;

  myFile.open(fileName);

  for (int k = 0; k < nbrLayers-1; k++)
  {
    myFile << "LAYER N°" << k << "\n";
    myFile << "Weights matrix: \n";
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      for (int j = 0; j < layersSizes[k]; j++) //le deuxième correspond à la largeur de la matrice
      {
        myFile << weights[k][i][j] << " ";
      }
      myFile << '\n';
    }
    myFile << "Biases vector: \n";
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      myFile << biases[k][i] << ' ';
    }
    myFile << '\n';
    myFile << "Neurons vector: \n";
    for (int i = 0; i < layersSizes[k+1]; i++)
    {
      myFile << layers[k][i] << ' ';
    }
    myFile << '\n';
    myFile << "Non linearity: \n";
    if (nonLinearities[k] == 0)
    {
      myFile << "Linear" << '\n';
    }
    else if (nonLinearities[k] == 1)
    {
      myFile << "ReLU" << '\n';
    }
    else if (nonLinearities[k] == 2)
    {
      myFile << "tanh" << '\n';
    }
    else
    {
      myFile << "Non supported non linearity" << '\n';
    }
    myFile << '\n';
  }

  myFile.close();


}

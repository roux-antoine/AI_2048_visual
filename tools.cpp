#include "tools.h"

int my_random(int inf, int max)
//returns a random number between inf and max (included !!) usind std::uniform_int_distribution
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(inf, max); // distribution in range [1, 6]
  return(dist6(rng));
}

int double_sum(std::vector<std::vector<int> > v)
{
  int result = 0;
  if (v.empty())
  {
    return 0;
  }
  for (int i = 0 ; i < (int)v.size() ; i++)
  {
    if (!(v.empty()))
    {
      for (int j = 0 ; j < (int)v[i].size() ; j++)
      {
        result += v[i][j];
      }
    }
  }
  return result;
}

int index(std::vector<int>* v, int value)
// Retourne l'index de l'élément value dans le vecteur v
{
  int idx = 0;
  int flag = 0;
  if (!(v->empty()))
  {
    int i=0;
    while ((i<v->size()) && (!flag))
    {
      if (v->at(i) == value)
      {
        idx = i;
        flag = 1;
      }
      i++;
    }
  }
  if (flag)
  {
    return idx;
  }
  else
  {
    return -1;
  }
}
//
// int index(std::vector<int> v, int value)
// // Retourne l'index de l'élément value dans le vecteur v
// {
//   int idx = 0;
//   int flag = 0;
//   if (!(v.empty()))
//   {
//     int i=0;
//     while ((i < (int)v.size()) && (!flag))
//     {
//       if (v.at(i) == value)
//       {
//         idx = i;
//         flag = 1;
//       }
//       i++;
//     }
//   }
//   if (flag)
//   {
//     return idx;
//   }
//   else
//   {
//     return -1;
//   }
// }


int index(std::vector<int> v, int value)
// Retourne l'index de l'élément value dans le vecteur v
{
  int idx = 0;
  int flag = 0;
  if (!(v.empty()))
  {
    int i=0;
    while ((i < (int)v.size()) && (!flag))
    {
      if (v.at(i) == value)
      {
        idx = i;
        flag = 1;
      }
      i++;
    }
  }
  if (flag)
  {
    return idx;
  }
  else
  {
    return -1;
  }
}

int max_index(std::vector<int>* v)
// Retourne l'index de l'élément de valeur maximale du vecteur v
{
  int idx = 0;
  int m = v->front();
  if (!(v->empty()))
  {
    for (int i = 0 ; i < (int)v->size() ; i++)
    {
      if (v->at(i) > m)
      {
        m = v->at(i);
        idx = i;
      }
    }
    return idx;
  }
  else {return -1;}
}

// int max_index(std::vector<int>* v)
// // Retourne l'index de l'élément de valeur maximale du vecteur v
// {
//   int idx = 0;
//   int m = v->front();
//   if (!(v->empty()))
//   {
//     for (int i = 0 ; i < (int)v->size() ; i++)
//     {
//       if (v->at(i) > m)
//       {
//         m = v->at(i);
//         idx = i;
//       }
//     }
//     return idx;
//   }
//   else {return -1;}
// }

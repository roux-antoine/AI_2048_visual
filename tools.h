
#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <random>

int my_random(int inf, int max);
//returns a random number between inf and max (included !!) using std::uniform_int_distribution

void print(std::vector<std::vector<int> > vector);

int double_sum(std::vector<std::vector<int> > v);

int index(std::vector<int>* v, int value);

int index(std::vector<int> v, int value);

int max_index(std::vector<int>* v);


#endif //TOOLS_H

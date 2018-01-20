
#ifndef AI_HC_HPP
#define AI_HC_HPP


int my_random(int inf, int max);
//returns a random number between inf and max (included !!) usind std::uniform_int_distribution

void print(std::vector<std::vector<int> > vector);


int double_sum(std::vector<std::vector<int> > v);

template<class T>
int index(std::vector<T>* v, T value);

template<class T>
int index(std::vector<T> v, T value);

template<class T>
int max_index(std::vector<T>* v);

template<class T>
int max_index(std::vector<T> v);

#endif

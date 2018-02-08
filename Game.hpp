
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "tools.cpp"

// faut il écrire un destructeur pour libérer la mémoire ??

class Game
{
private:


protected:

  int size;

  virtual void play() = 0;

  void add_random_nbr();

  void swipe(int direction);

  virtual int get_direction() = 0 ;

public:

  std::vector<std::vector<int> > grid;

  std::vector<std::vector<int> > swipe_up_copy(std::vector<std::vector<int> > givenGrid) const;

  std::vector<std::vector<int> > swipe_down_copy(std::vector<std::vector<int> > givenGrid) const;

  std::vector<std::vector<int> > swipe_left_copy(std::vector<std::vector<int> > givenGrid) const;

  std::vector<std::vector<int> > swipe_right_copy(std::vector<std::vector<int> > givenGrid) const;

  void swipe_up();

  void swipe_down();

  void swipe_left();

  void swipe_right();

  Game(int givenSize);

  void print() const; //celle la sera remplacee par l'affiche avec Qt

  bool can_swipe_up() const;

  bool can_swipe_down() const;

  bool can_swipe_right() const;

  bool can_swipe_left() const;

  bool can_swipe(int direction) const;

  void fill_test();

  bool is_finished() const;

};

#endif

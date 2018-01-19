
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "tools.cpp"

#ifndef GAME_HPP
#define GAME_HPP

// faut il écrire un destructeur pour libérer la mémoire ??

class Game
{
private:

  // ATTRIBUTES //

  // METHODS //

protected:

  int size;


  // METHODS //


  virtual void play();
  // main loop in which the game is played
  // CODE DE TEST

  void add_random_nbr();



  void swipe(int direction);
  //directions : 0 = left, 1 = down, 2 = right, 3 = up

  virtual int get_direction();
  // in the daughters classes, calls the function that decides in which direction to swipe

public:

  // ATTRIBUTES //
  std::vector<std::vector<int> > grid;

  // METHODS //

  std::vector<std::vector<int> > swipe_up_copy(std::vector<std::vector<int> > givenGrid) const;
  // swipes the given grid in the up direction, doing all the necessary additions
  // takes a grid, returns a grid -> does not modify the original

  std::vector<std::vector<int> > swipe_down_copy(std::vector<std::vector<int> > givenGrid) const;
  // swipes the given grid in the down direction, doing all the necessary additions
  // takes a grid, returns a grid -> does not modify the original

  std::vector<std::vector<int> > swipe_left_copy(std::vector<std::vector<int> > givenGrid) const;
  // swipes the given grid in the left direction, doing all the necessary additions
  // takes a grid, returns a grid -> does not modify the original

  std::vector<std::vector<int> > swipe_right_copy(std::vector<std::vector<int> > givenGrid) const;
  // swipes the given grid in the right direction, doing all the necessary additions
  // takes a grid, returns a grid -> does not modify the original
  void swipe_up();
  // swipes the given grid in the up direction, doing all the necessary additions
  // Modifies the original

  void swipe_down();
  // swipes the given grid in the down direction, doing all the necessary additions
  // Modifies the original

  void swipe_left();
  // swipes the given grid in the left direction, doing all the necessary additions
  // Modifies the original

  void swipe_right();
  // swipes the given grid in the right direction, doing all the necessary additions
  // Modifies the original

  Game(int givenSize);

  void print();
  // celle la sera remplacee par l'affiche avec Qt

  bool can_swipe_up() const;
  // returns true if the grid can be swiped up

  bool can_swipe_down() const;
  // returns true if the grid can be swiped down

  bool can_swipe_right() const;
  // returns true if the grid can be swiped right

  bool can_swipe_left() const;
  // returns true if the grid can be swiped left

  bool can_swipe(int direction) const;
  //directions : 0 = left, 1 = down, 2 = right, 3 = up

  void fill_test();

  bool is_finished();
  // returns true if grid is full, false otherwise

};

#endif

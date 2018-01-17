
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "tools.cpp"

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

  std::vector<std::vector<int> > swipe_base(std::vector<std::vector<int> > givenGrid) const;
  // swipes the given grid in the up direction, doing all the necessary additions

  void swipe(int direction);
  //directions : 0 = left, 1 = down, 2 = right, 3 = up

  virtual int get_direction();
  // in the daughters classes, calls the function that decides in which direction to swipe


public:

  // ATTRIBUTES //
  std::vector<std::vector<int> > grid;

  // METHODS //

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

  std::vector<std::vector<int> > rotate(std::vector<std::vector<int> > givenGrid, int angle) const;

  bool is_finished();
  // returns true if grid is full, false otherwise

};

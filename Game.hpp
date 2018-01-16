
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

  // ATTRIBUTES //
  std::vector<std::vector<int> > grid;

  int size;


  // METHODS //

  Game(int givenSize);

  void print();
  // celle la sera remplacee par l'affiche avec Qt

  void fill_test();

  virtual void play();
  // main loop in which the game is played
  // CODE DE TEST

  bool is_finished();
  // returns true if grid is full, false otherwise

  void add_random_nbr();

  std::vector<std::vector<int> > rotate(std::vector<std::vector<int> > givenGrid, int angle) const;
  //rotates clockwise
  //attention, il ne faut pas que givenGrid soit modifiée, car c'est la grille de jeu
  // du coup pour le moment la fonction fait des recopies et ne passe pas par des pointeurs

  bool can_swipe_base(std::vector<std::vector<int> > givenGrid) const;
  // returns true if the grid can be swiped up

  bool can_swipe(int direction) const;
  //directions : 0 = left, 1 = down, 2 = right, 3 = up

  std::vector<std::vector<int> > swipe_base(std::vector<std::vector<int> > givenGrid) const;
  // swipes the given grid in the up direction, doing all the necessary additions

  void swipe(int direction);
  //directions : 0 = left, 1 = down, 2 = right, 3 = up

  virtual int get_direction();
  // in the daughters classes, calls the function that decides in which direction to swipe


public:

  // ATTRIBUTES //

  // METHODS //



};

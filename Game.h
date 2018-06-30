
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "tools.h"


class Game
{
private:
    virtual int get_direction(int depth) = 0;
    void swipe_up();
    void swipe_down();
    void swipe_left();
    void swipe_right();
    bool can_swipe_up() const;
    bool can_swipe_down() const;
    bool can_swipe_right() const;
    bool can_swipe_left() const;

protected:
  int size;
  Game(int givenSize);
  virtual void play() = 0;
  void add_random_nbr();
  void swipe(int direction);
  bool can_swipe(int direction) const;
  bool is_finished() const;


public:
  std::vector<std::vector<int> > grid;
  void print() const;


};

#endif //GAME_H

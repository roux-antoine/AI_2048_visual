
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "tools.h"

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
  int classicScore;



public:
  std::vector<std::vector<int> > grid;
  void print() const;
  int get_classic_score();
  int get_my_score();


};

#endif //GAME_H

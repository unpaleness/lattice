#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "container.h"

class Fragment
{
public:
  Fragment(int, int, int, int);
  ~Fragment();

  void setNeighbour(int, Fragment *); //sets neighbour
  int getId(); //gets identifier

private:
  int _id; //fragment identifier
  int _time; //local time of fragment
  int _timeLimit; //limit of time to count
  int _sizeWidth;
  int _sizeHeight;
  int _sizeBorder; //amount of border elements
  Fragment *_neighbours[8]; //pointers to neighbour fragments
};

#endif // FRAGMENT_H

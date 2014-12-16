#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "container.h"

class Fragment
{
public:
  Fragment(int, int, int, int);
  ~Fragment();

  void setNeighbour(int, Fragment *); //sets neighbour
  Fragment *getNeighbour(int); //gets neighbours
  int id(); //returns id's value
  int time(); //returns time's value
  int width(); //returns width's value
  int height(); //returns height's value

private:
  int _id; //fragment identifier
  int _time; //local time of fragment
  int _timeLimit; //limit of time to count
  int _sizeWidth; //amount of elements by width
  int _sizeHeight; //amount of elements by height
  int _sizeBorder; //amount of border elements
  Fragment *_neighbours[8]; //pointers to neighbour fragments
};

#endif // FRAGMENT_H

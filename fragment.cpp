#include "fragment.h"

/*
 * PUBLIC
 */

Fragment::Fragment(int id, int timeLimit, int sizeWidth, int sizeHeight)
{
  _id = id;
  _time = 0;
  _timeLimit = timeLimit;
  _sizeBorder = 1;
  _sizeWidth = sizeWidth;
  _sizeHeight = sizeHeight;
}

Fragment::~Fragment()
{

}

void Fragment::setNeighbour(int position, Fragment *neighbour)
{
  _neighbours[position] = neighbour;
}

int Fragment::getId() { return _id; }

/*
 * PRIVATE
 */

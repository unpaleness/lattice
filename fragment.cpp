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
  for(int i = 0; i < 8; i++)
    _neighbours[i] = nullptr;
}

Fragment::~Fragment()
{

}

void Fragment::setNeighbour(int position, Fragment *neighbour)
{
  _neighbours[position] = neighbour;
}

Fragment *Fragment::getNeighbour(int index) { return _neighbours[index]; }

int Fragment::id() { return _id; }

int Fragment::time() { return _time; }

int Fragment::width() { return _sizeWidth; }

int Fragment::height() { return _sizeHeight; }

/*
 * PRIVATE
 */

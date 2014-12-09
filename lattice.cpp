#include "cmath"
#include "fragment.h"
#include "lattice.h"

/*
 * PUBLIC
 */

Lattice::Lattice(int width, int height, int nThreads, int timeLimit,
                 bool isTorus)
{
  _width = width;
  _height = height;
  _nThreads = nThreads;
  _timeLimit = timeLimit;
  _isTorus = isTorus;
  _splitLattice();
  _fragments = new Fragment *[_width * _height];
  _setFragments();
}

Lattice::~Lattice()
{
  for(int i = 0; i < _nThreads; i++)
    delete _fragments[i];
  delete [] _fragments;
}

Fragment *Lattice::fragment(int index) { return _fragments[index]; }

/*
 * PRIVATE
 */

void Lattice::_splitLattice()
{
  if(_nThreads < 1)
    return;
  double localWidth = _width;
  double localHeight = double(_height) / _nThreads;
  _nWidth = 1;
  _nHeight = _nThreads;
  for(int k = 2; k <= _nThreads; k++)
  {
    if(_nThreads % k == 0)
    {
      if(std::abs(double(_width) / k - double(_height) * k / _nThreads) >
         std::abs(localWidth - localHeight))
        break;
      localWidth = double(_width) / k;
      localHeight = double(_height) * k / _nThreads;
      _nWidth = k;
      _nHeight = _nThreads / k;
    }
  }
}

void Lattice::_setFragments()
{
  int localWidth;
  int localHeight;
  for(int k = 0; k < _width * _height; k++)
  {
    localWidth = _width / _nWidth;
    localHeight = _height / _nHeight;
    if(k % _height < _width % _nWidth)
      localWidth++;
    if(k / _height < _height % _nHeight)
      localHeight++;
    _fragments[k] = new Fragment(k, _timeLimit, localWidth, localHeight);
  }
}

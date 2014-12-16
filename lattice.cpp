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
  _fragments = new Fragment *[_nThreads];
  _initFragments();
}

Lattice::~Lattice()
{
  for(int i = 0; i < _nThreads; i++)
    delete _fragments[i];
  delete [] _fragments;
}

Fragment *Lattice::getFragment(int index) { return _fragments[index]; }

int Lattice::nThreads() { return _nThreads; }

int Lattice::nWidth() { return _nWidth; }

int Lattice::nHeight() { return _nHeight; }

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

void Lattice::_initFragments()
{
  int localWidth = _width / _nWidth;
  int localHeight = _height / _nHeight;
  //initializing fragments
  for(int k = 0; k < _nThreads; k++)
  {
    localWidth = _width / _nWidth;
    localHeight = _height / _nHeight;
    if(k % _nWidth < _width % _nWidth)
      localWidth++;
    if(k / _nWidth < _height % _nHeight)
      localHeight++;
    _fragments[k] = new Fragment(k, _timeLimit, localWidth, localHeight);
  }
  //initializing neighbours
  for(int k = 0; k < _nThreads; k++)
  {
    // k / _nWidth - index by height
    // k % _nHeight - index by width
    _setNeighbours(k);
  }
}

void Lattice::_setNeighbours(int i)
{
  if(!_isTorus) // not torus
  {
    if(i / _nWidth != 0) // not top
    {
      if(i % _nWidth != 0) // not left
        _fragments[i]->setNeighbour(0, _fragments[i - _nWidth - 1]);
      if(i % _nWidth != _nWidth - 1) // not right
        _fragments[i]->setNeighbour(2, _fragments[i - _nWidth + 1]);
      _fragments[i]->setNeighbour(1, _fragments[i - _nWidth]);
    }
    if(i / _nWidth != _nHeight - 1) // not bottom
    {
      if(i % _nWidth != 0) // not left
        _fragments[i]->setNeighbour(6, _fragments[i + _nWidth - 1]);
      if(i % _nWidth != _nWidth - 1) // not right
        _fragments[i]->setNeighbour(4, _fragments[i + _nWidth + 1]);
      _fragments[i]->setNeighbour(5, _fragments[i + _nWidth]);
    }
    if(i % _nWidth != 0) // not left
      _fragments[i]->setNeighbour(7, _fragments[i - 1]);
    if(i % _nWidth != _nWidth - 1) // not right
      _fragments[i]->setNeighbour(3, _fragments[i + 1]);
  }
  else
  {
    if(i / _nWidth != 0) // not top
    {
      if(i % _nWidth != 0) // not left
        _fragments[i]->setNeighbour(0, _fragments[i - _nWidth - 1]);
      else
        _fragments[i]->setNeighbour(0, _fragments[i - 1]);
      if(i % _nWidth != _nWidth - 1) // not right
        _fragments[i]->setNeighbour(2, _fragments[i - _nWidth + 1]);
      else
        _fragments[i]->setNeighbour(2, _fragments[i - 2 * _nWidth + 1]);
      _fragments[i]->setNeighbour(1, _fragments[i - _nWidth]);
    }
    else
    {
      if(i % _nWidth != 0) // not left
        _fragments[i]->setNeighbour(0, _fragments[_nWidth * (_nHeight - 1) +
                                    (i % _nWidth) - 1]);
      else
        _fragments[i]->setNeighbour(0, _fragments[_nThreads - 1]);
      if(i % _nWidth != _nWidth - 1) // not right
        _fragments[i]->setNeighbour(2, _fragments[_nWidth * (_nHeight - 1) +
                                    (i % _nWidth) + 1]);
      else
        _fragments[i]->setNeighbour(2, _fragments[_nThreads - _nWidth]);
      _fragments[i]->setNeighbour(1, _fragments[_nWidth * (_nHeight - 1) +
                                  (i % _nWidth)]);
    }
    if(i / _nWidth != _nHeight - 1) // not bottom
    {
      if(i % _nWidth != 0) // not left
        _fragments[i]->setNeighbour(6, _fragments[i + _nWidth - 1]);
      else
        _fragments[i]->setNeighbour(6, _fragments[i + 2 * _nWidth - 1]);
      if(i % _nWidth != _nWidth - 1) // not right
        _fragments[i]->setNeighbour(4, _fragments[i + _nWidth + 1]);
      else
        _fragments[i]->setNeighbour(4, _fragments[i + 1]);
      _fragments[i]->setNeighbour(5, _fragments[i + _nWidth]);
    }
    else
    {
      if(i % _nWidth != 0) // not left
        _fragments[i]->setNeighbour(6, _fragments[i % _nWidth - 1]);
      else
        _fragments[i]->setNeighbour(6, _fragments[_nWidth - 1]);
      if(i % _nWidth != _nWidth - 1) // not right
        _fragments[i]->setNeighbour(4, _fragments[i % _nWidth + 1]);
      else
        _fragments[i]->setNeighbour(4, _fragments[0]);
      _fragments[i]->setNeighbour(5, _fragments[i % _nWidth]);
    }
    if(i % _nWidth != 0) // not left
      _fragments[i]->setNeighbour(7, _fragments[i - 1]);
    else
      _fragments[i]->setNeighbour(7, _fragments[i + _nWidth - 1]);
    if(i % _nWidth != _nWidth - 1) // not right
      _fragments[i]->setNeighbour(3, _fragments[i + 1]);
    else
      _fragments[i]->setNeighbour(3, _fragments[i - _nWidth + 1]);
  }

//  if(i / _nWidth == 0) // top
//  {
//    if(_isTorus)
//      _fragments[i]->setNeighbour(1, _fragments[_nWidth * (_nHeight - 1) +
//                                  (i % _nWidth)]);
//  }
//  else
//  {
//    _fragments[i]->setNeighbour(1, _fragments[i - _nWidth]);
//  }
//  if(i / _nWidth == _nHeight - 1) // bottom
//  {
//    if(_isTorus)
//      _fragments[i]->setNeighbour(5, _fragments[i % _nWidth]);
//  }
//  else
//  {
//    _fragments[i]->setNeighbour(5, _fragments[i + _nWidth]);
//  }
//  if(i % _nWidth == 0) // left middle
//  {
//    if(_isTorus)
//      _fragments[i]->setNeighbour(7, _fragments[i + _nWidth - 1]);
//  }
//  else
//    _fragments[i]->setNeighbour(7, _fragments[i - 1]);
//  if(i % _nWidth == _nWidth - 1) // right middle
//  {
//    if(_isTorus)
//      _fragments[i]->setNeighbour(3, _fragments[i - _nWidth + 1]);
//  }
//  else
//    _fragments[i]->setNeighbour(3, _fragments[i + 1]);
}

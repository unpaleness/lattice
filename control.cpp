#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <mpi.h>

#include "control.h"

using namespace std;

/*
 * PUBLIC
 */

Control::Control(int nFragments)
{
  _isInitialized = false;
  _nFragments = nFragments;
}

Control::~Control()
{
}

void Control::execute()
{
  string word;
  cout << "Hello!\n";
  _querySetLatticeParameters();
  _messageLatticeInitialized();
  cout << "(type \"exit\" to exit)\n";
  while(cin >> word)
  {
    if(word.compare("exit") == 0)
      break;
  }
  cout << "Bye!\n";
}

/*
 * PRIVATE
 */

void Control::_querySetLatticeParameters()
{
  ifstream input(FILENAME_IN, ios::in);
  input >> _width >> _height >> _timeLimit >> _isTorus;
  input.close();
  _splitLattice();
  _initFragments();
  _isInitialized = true;
}

void Control::_messageLatticeInitialized()
{
  int message[11];
  ofstream output(FILENAME_OUT, ios::out);
  output << "Lattice is splitted on " << _nFragments
       << " fragments in such a way (height x width ): "
       << _nHeight << "x" << _nWidth << "\n";
  output << "Fragments:\n";
  for(int i = 1; i < _nFragments + 1; i++)
  {
    // gets info about fragments
    MPI_Recv(message, 11, MPI_INT, i, 0, MPI_COMM_WORLD, &_mpiStatus);
    output << i << " fragment, id = "
         << message[8] << ", size = "
         << message[9] << "x"
         << message[10] << ", neighbours:\n";
    for(int j = 0; j < 3; j++)
      if(message[j])
        output << setw(W) << message[j];
      else
        output << setw(W) << "-";
    output << '\n';
    if(message[7])
      output << setw(W) << message[7];
    else
      output << setw(W) << "-";
    output << setw(W) << "x";
    if(message[3])
      output << setw(W) << message[3];
    else
      output << setw(W) << "-";
    output << '\n';
    for(int j = 6; j > 3; j--)
      if(message[j])
        output << setw(W) << message[j];
      else
        output << setw(W) << "-";
    output << '\n';
  }
  output.close();
}

void Control::_splitLattice()
{
  if(_nFragments < 1)
    return;
  double localWidth = _width;
  double localHeight = double(_height) / _nFragments;
  _nWidth = 1;
  _nHeight = _nFragments;
  for(int k = 2; k <= _nFragments; k++)
  {
    if(_nFragments % k == 0)
    {
      if(fabs(double(_width) / k - double(_height) * k / _nFragments) >
         fabs(localWidth - localHeight))
        break;
      localWidth = double(_width) / k;
      localHeight = double(_height) * k / _nFragments;
      _nWidth = k;
      _nHeight = _nFragments / k;
    }
  }
}

void Control::_initFragments()
{
  int message[4];
  int localWidth = _width / _nWidth;
  int localHeight = _height / _nHeight;
  //initializing fragments
  for(int k = 0; k < _nFragments; k++)
  {
    localWidth = _width / _nWidth;
    localHeight = _height / _nHeight;
    if(k % _nWidth < _width % _nWidth)
      localWidth++;
    if(k / _nWidth < _height % _nHeight)
      localHeight++;
    message[0] = k + 1;
    message[1] = _timeLimit;
    message[2] = localWidth;
    message[3] = localHeight;
    MPI_Send(message, 4, MPI_INT, k + 1, 0, MPI_COMM_WORLD);
  }
  //initializing neighbours
  for(int k = 0; k < _nFragments; k++)
  {
    // k / _nWidth - index by height
    // k % _nHeight - index by width
    _setNeighbours(k);
  }
}

void Control::_setNeighbours(int i)
{
  int neighbourRanks[8];
  if(!_isTorus) // not torus
  {
    if(i / _nWidth != 0) // not top
    {
      if(i % _nWidth != 0) // not left
        neighbourRanks[0] = i - _nWidth - 1;
      if(i % _nWidth != _nWidth - 1) // not right
        neighbourRanks[2] = i - _nWidth + 1;
      neighbourRanks[1] = i - _nWidth;
    }
    if(i / _nWidth != _nHeight - 1) // not bottom
    {
      if(i % _nWidth != 0) // not left
        neighbourRanks[6] = i + _nWidth - 1;
      if(i % _nWidth != _nWidth - 1) // not right
        neighbourRanks[4] = i + _nWidth + 1;
      neighbourRanks[5] = i + _nWidth;
    }
    if(i % _nWidth != 0) // not left
      neighbourRanks[7] = i - 1;
    if(i % _nWidth != _nWidth - 1) // not right
      neighbourRanks[3] = i + 1;
  }
  else
  {
    if(i / _nWidth != 0) // not top
    {
      if(i % _nWidth != 0) // not left
        neighbourRanks[0] = i - _nWidth - 1;
      else
        neighbourRanks[0] = i - 1;
      if(i % _nWidth != _nWidth - 1) // not right
        neighbourRanks[2] = i - _nWidth + 1;
      else
        neighbourRanks[2] = i - 2 * _nWidth + 1;
      neighbourRanks[1] = i - _nWidth;
    }
    else
    {
      if(i % _nWidth != 0) // not left
        neighbourRanks[0] = _nWidth * (_nHeight - 1) + (i % _nWidth) - 1;
      else
        neighbourRanks[0] = _nFragments - 1;
      if(i % _nWidth != _nWidth - 1) // not right
        neighbourRanks[2] = _nWidth * (_nHeight - 1) + (i % _nWidth) + 1;
      else
        neighbourRanks[2] = _nFragments - _nWidth;
      neighbourRanks[1] = _nWidth * (_nHeight - 1) + (i % _nWidth);
    }
    if(i / _nWidth != _nHeight - 1) // not bottom
    {
      if(i % _nWidth != 0) // not left
        neighbourRanks[6] = i + _nWidth - 1;
      else
        neighbourRanks[6] = i + 2 * _nWidth - 1;
      if(i % _nWidth != _nWidth - 1) // not right
        neighbourRanks[4] = i + _nWidth + 1;
      else
        neighbourRanks[4] = i + 1;
      neighbourRanks[5] = i + _nWidth;
    }
    else
    {
      if(i % _nWidth != 0) // not left
        neighbourRanks[6] = i % _nWidth - 1;
      else
        neighbourRanks[6] = _nWidth - 1;
      if(i % _nWidth != _nWidth - 1) // not right
        neighbourRanks[4] = i % _nWidth + 1;
      else
        neighbourRanks[4] = 0;
      neighbourRanks[5] = i % _nWidth;
    }
    if(i % _nWidth != 0) // not left
      neighbourRanks[7] = i - 1;
    else
      neighbourRanks[7] = i + _nWidth - 1;
    if(i % _nWidth != _nWidth - 1) // not right
      neighbourRanks[3] = i + 1;
    else
      neighbourRanks[3] = i - _nWidth + 1;
  }
  for(int i = 0; i < 8; i++)
    neighbourRanks[i]++;
  MPI_Send(neighbourRanks, 8, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
}


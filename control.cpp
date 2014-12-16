#include "lattice.h"
#include "fragment.h"
#include "control.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>

#define W 4

using namespace std;

/*
 * PUBLIC
 */

Control::Control()
{
  cout << fixed;
}

Control::~Control()
{
  if(_lattice)
    delete _lattice;
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

void Control::setLattice(Lattice *&lattice) { _lattice = lattice; }

/*
 * PRIVATE
 */

void Control::_querySetLatticeParameters()
{
  int width, height, nThreads, timeLimit;
  bool isTorus;
  cout << "Enter some info:\n";
  cout << "Total lattice width: "; cin >> width;
  cout << "Total lattice height: "; cin >> height;
  cout << "Amount of desired threads: "; cin >> nThreads;
  cout << "Execution time: "; cin >> timeLimit;
  cout << "Should lattice be torus-like?: "; cin >> isTorus;
  _lattice = new Lattice(width, height, nThreads, timeLimit, isTorus);
}

void Control::_messageLatticeInitialized()
{
  cout << "Lattice initialized.\n";
  cout << "Lattice is splitted on " << _lattice->nThreads()
       << " fragments in such a way (height x width ): "
       << _lattice->nHeight() << "x" << _lattice->nWidth() << "\n";
  cout << "Fragments:\n";
  for(int i = 0; i < _lattice->nThreads(); i++)
  {
    cout << i << " fragment, id = "
         << _lattice->getFragment(i)->id() << ", size = "
         << _lattice->getFragment(i)->height() << "x"
         << _lattice->getFragment(i)->width() << ", neighbours:\n";
    for(int j = 0; j < 3; j++)
      if(_lattice->getFragment(i)->getNeighbour(j))
        cout << setw(W) << _lattice->getFragment(i)->getNeighbour(j)->id();
      else
        cout << setw(W) << "-";
    cout << '\n';
    if(_lattice->getFragment(i)->getNeighbour(7))
      cout << setw(W) << _lattice->getFragment(i)->getNeighbour(7)->id();
    else
      cout << setw(W) << "-";
    cout << setw(W) << "x";
    if(_lattice->getFragment(i)->getNeighbour(3))
      cout << setw(W) << _lattice->getFragment(i)->getNeighbour(3)->id();
    else
      cout << setw(W) << "-";
    cout << '\n';
    for(int j = 6; j > 3; j--)
      if(_lattice->getFragment(i)->getNeighbour(j))
        cout << setw(W) << _lattice->getFragment(i)->getNeighbour(j)->id();
      else
        cout << setw(W) << "-";
    cout << '\n';
  }
}

#include "lattice.h"
#include "control.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*
 * PUBLIC
 */

Control::Control()
{

}

Control::~Control()
{
  if(*_lattice)
    delete *_lattice;
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

void Control::setLattice(Lattice **lattice)
{
  _lattice = lattice;
}

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
  *_lattice = new Lattice(width, height, nThreads, timeLimit, isTorus);
}

void Control::_messageLatticeInitialized()
{
  cout << "Lattice initialized.\n";
  cout << "";
}

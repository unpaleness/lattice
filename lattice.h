#ifndef LATTICE_H
#define LATTICE_H

#include "container.h"

class Fragment;

class Lattice
{
public:
  Lattice(int, int, int, int, bool); //width, height, threads, timelimit,
                                     //is torus
  ~Lattice();

  Fragment *getFragment(int); //gets pointer to fragment by index
  int nThreads(); //returns amount if threads
  int nWidth(); //returns amount of splitted fragments by width
  int nHeight(); //returns amount of splitted fragments by height

private:
  bool _isTorus; //show whether lattice is torus-like or not
  int _timeLimit; //limit of global time
  int _width; //total width of the lattice
  int _height; //total height of the lattice
  int _nWidth; //amount of fragments along width
  int _nHeight; //amount of fragments along height
  int _nThreads; //amount of threads-fragments
  Fragment **_fragments; //pointers to fragments itself

  void _splitLattice(); //splits lattice on approximately equal rectangles
  void _initFragments(); //initializes fragments
  void _setNeighbours(int); //initializes neighbours of fragments
};

#endif // LATTICE_H

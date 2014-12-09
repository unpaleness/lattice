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

  Fragment *fragment(int);

private:
  bool _isTorus; //show whether lattice is torus-like or not
  int _timeLimit; //limit of global time
  int _width; //total width of the lattice
  int _height; //total height of the lattice
  int _nWidth; //amount of fragments along width
  int _nHeight; //amount of fragments along height
  int _nThreads; //amount of threads-fragments
  Fragment **_fragments; //pointers to fragments itself

  //splits lattice on almost equal rectangles
  void _splitLattice();
  void _setFragments();
};

#endif // LATTICE_H

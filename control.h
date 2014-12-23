#ifndef CONTROL_H
#define CONTROL_H

#include "fragment.h"

#define W 4
#define FILENAME_IN "lattice.cfg"
#define FILENAME_OUT "lattice.log"

class Control
{
public:
  Control(int);
  ~Control();

  void execute();

private:
  bool _isInitialized;
  bool _isTorus; // show whether lattice is torus-like or not
  int _timeLimit; // limit of global time
  int _width; // total width of the lattice
  int _height; // total height of the lattice
  int _nWidth; // amount of fragments along width
  int _nHeight; // amount of fragments along height
  int _nFragments; // amount of threads-fragments
  MPI_Status _mpiStatus;

  void _splitLattice(); // splits lattice on approximately equal rectangles
  void _initFragments(); // initializes fragments
  void _setNeighbours(int); // initializes neighbours of fragments

  void _querySetLatticeParameters();
  void _messageLatticeInitialized();
};

#endif // CONTROL_H

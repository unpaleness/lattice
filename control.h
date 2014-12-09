#ifndef CONTROL_H
#define CONTROL_H

class Lattice;

class Control
{
public:
  Control();
  ~Control();

  void execute();
  void setLattice(Lattice **);

private:
  Lattice **_lattice;

  void _querySetLatticeParameters();
  void _messageLatticeInitialized();
};

#endif // CONTROL_H

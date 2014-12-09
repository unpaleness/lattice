#include "lattice.h"
#include "control.h"
#include <QCoreApplication>

//int main(int argc, char *argv[])
int main()
{
  Lattice *lattice;
  Control control;
  control.setLattice(&lattice);
  control.execute();
  return 0;
}

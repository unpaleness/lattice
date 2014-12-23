#ifndef FRAGMENT_H
#define FRAGMENT_H

class Fragment
{
public:
  Fragment();
  ~Fragment();

//  void setNeighbours(int *); // sets neighbour
//  int getNeighbour(int); // gets neighbours' rank
//  int id(); // returns id's value
//  int time(); // returns time's value
//  int width(); // returns width's value
//  int height(); // returns height's value

private:
  int _id; // fragment identifier
  int _time; // local time of fragment
  int _timeLimit; // limit of time to count
  int _sizeWidth; // amount of elements by width
  int _sizeHeight; // amount of elements by height
  int _sizeBorder; // amount of border elements
  int _neighbours[8]; // ranks of neighbour fragments

  MPI_Status _mpiStatus;
};

#endif // FRAGMENT_H

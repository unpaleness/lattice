#include <mpi.h>

#include "fragment.h"

/*
 * PUBLIC
 */

Fragment::Fragment()
{
  int message[11];
  // gets init parameters
  MPI_Recv(message, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, &_mpiStatus);
  _id = message[0];
  _time = 0;
  _timeLimit = message[1];
  _sizeBorder = 1;
  _sizeWidth = message[2];
  _sizeHeight = message[3];
  for(int i = 0; i < 8; i++)
    _neighbours[i] = 0;
  // gets heighbours
  MPI_Recv(message, 8, MPI_INT, 0, 0, MPI_COMM_WORLD, &_mpiStatus);
  for(int i = 0; i < 8; i++)
    _neighbours[i] = message[i];
  // sends info about fragment
  for(int i = 0; i < 8; i++)
  {
    message[i] = _neighbours[i];
  }
  message[8] = _id;
  message[9] = _sizeHeight;
  message[10] = _sizeWidth;
  MPI_Send(message, 11, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

Fragment::~Fragment()
{

}

//void Fragment::setNeighbours(int *neighbourRanks)
//{
//  for(int i = 0; i < 8; i++)
//    _neighbours[i] = neighbourRanks[i];
//}

//int Fragment::getNeighbour(int index) { return _neighbours[index]; }

//int Fragment::id() { return _id; }

//int Fragment::time() { return _time; }

//int Fragment::width() { return _sizeWidth; }

//int Fragment::height() { return _sizeHeight; }

/*
 * PRIVATE
 */

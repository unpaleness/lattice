#ifndef CONTAINER_H
#define CONTAINER_H

class Container
{
public:
  Container();

protected:
  template <class T>
  void _memoryAlloc(int, T *); //allocates memory for array
  template <class T>
  void _memoryErase(T *); //erases memory from array

};

#endif // CONTAINER_H

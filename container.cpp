#include "container.h"

/*
 * PUBLIC
 */

Container::Container()
{
}

/*
 * PRIVATE
 */

template <class T>
void Container::_memoryAlloc(int N, T *&array)
{
  array = new T [N];
}

template <class T>
void Container::_memoryErase(int N, T *&array)
{
  delete [] array;
}

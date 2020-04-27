#include "TQueue.h"

template <class T>
TQueue<T>::TQueue(int size) : TStack(size) 
{ 
	Li = 0;
}

template <class T>
int TQueue<T>::GetNextIndex(int index)
{
	return ++index % this->memSize();
}

template <class T>
T TQueue<T>::get()
{
	/*if (!this->isEmpty())
	{
		T tmp = this->cell[Li];
		Li = GetNextIndex(Li);
		this->dataCount--;
		return tmp;
	}*/
	T tmp = this->cell[Li];
	Li = GetNextIndex(Li);
	this->dataCount--;
	return tmp;
}

template <class T>
void TQueue<T>::put(T sym)
{
	/*if (!this->isFull())
	{
		this->dataCount++;
		this->cell[(Li + this->dataCount - 1) % this->memSize] = sym;
	}*/
	this->dataCount++;
	this->cell[(Li + this->dataCount - 1) % this->memSize] = sym;
}
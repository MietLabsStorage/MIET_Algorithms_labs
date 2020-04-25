#include "TStack.h"
#include <iostream>

template <class T>
TStack<T>::TStack(int _memSize)
{
	memSize = _memSize;
	dataCount = 0;
	cell = new char[_memSize];
	for (int i = 0; i < memSize; i++)
	{
		cell[i] = ' ';
	}
}

template <class T>
void TStack<T>::put(T sym, int& err)
{
	if (dataCount < memSize)
	{
		dataCount++;
		err = 0;
		cell[dataCount - 1] = sym;
	}
	else
	{
		err = 1;
	}
}

template <class T>
T TStack<T>::get(int& err)
{
	if (dataCount != 0)
	{
		char sym = cell[dataCount - 1];
		cell[dataCount - 1] = NULL;
		dataCount--;
		err = 0;
		return sym;

	}
	else
	{
		err = 1;
		return NULL;
	}
}

template <class T>
bool TStack<T>::isEmpty()
{
	if (dataCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool TStack<T>::isFull()
{
	if (dataCount == memSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}
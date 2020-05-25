#include "TStack.h"
#include <iostream>

TStack::TStack()
{
	memSize = maxMemSize;
	dataCount = 0;
	cell = new T[maxMemSize];
	for (int i = 0; i < memSize; i++)
	{
		cell[i] = ' ';
	}
}

TStack::TStack(int _memSize)
{
	memSize = _memSize;
	dataCount = 0;
	cell = new T[_memSize];
	for (int i = 0; i < memSize; i++)
	{
		cell[i] = ' ';
	}
}

void TStack::put(T sym, int& err)
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

T TStack::get(int& err)
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

bool TStack::isEmpty()
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

bool TStack::isFull()
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

int TStack::count()
{
	return dataCount;
}

void TStack::setSize(int size)
{
	memSize = size;
	delete[] cell;
	cell = new T[maxMemSize];
}
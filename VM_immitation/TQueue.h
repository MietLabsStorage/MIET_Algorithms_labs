#pragma once
#include "TStack.h"
template <class T>
class TQueue :	public TStack<T>
{
	int Li;
	int GetNextIndex(int index);

public:
	TQueue(int size = this->maxMemSize) : TStack(size) {Li = 0;}
	T get();
	void put(T sym);
};


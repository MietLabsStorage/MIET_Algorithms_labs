#pragma once
#include "TStack.h"

class TQueue : public TStack
{
	int Li;
	int GetNextIndex(int index);

public:
	TQueue();
	TQueue(int size);
	T get();
	void put(T sym);
};

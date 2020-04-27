#pragma once
template <class T>
class TStack
{
protected:
	T* cell;
	int memSize;
	const int maxMemSize = 100;
	int dataCount;

public:
	TStack(int _memSize);
	virtual void put(T sym, int& err);
	virtual T get(int& err);
	bool isEmpty();
	bool isFull();
};


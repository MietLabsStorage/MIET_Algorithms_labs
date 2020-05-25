//#ifndef TSTACK_H
//#define TSTACK_H
#pragma once

typedef int T;
class TStack
{
protected:
	T* cell;
	int memSize;
	const int maxMemSize = 100;
	int dataCount;

public:
	TStack();
	TStack(int _memSize);
	virtual void put(T sym, int& err);
	virtual T get(int& err);
	bool isEmpty();
	bool isFull();
	int count();
	void setSize(int size);
};


//#endif 
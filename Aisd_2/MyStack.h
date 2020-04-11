#pragma once
class MyStack
{
	char* cell;
	int size;
	int currentIndex;

public:
	MyStack(int _size);
	void Push(char sym, int& err);
	char Pop(int& err);
	bool isEmpty();
};


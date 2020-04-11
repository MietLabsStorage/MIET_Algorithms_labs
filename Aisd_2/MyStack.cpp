#include "MyStack.h"

MyStack::MyStack(int _size)
{
	size = _size;
	currentIndex = -1;
	cell = new char[_size];
	for (int i = 0; i < size; i++)
	{
		cell[i] = ' ';
	}
}

void MyStack::Push(char sym, int& err)
{
	if (currentIndex < size-1)
	{
		currentIndex++;
		err = 0;
		cell[currentIndex] = sym;
	}
	else
	{
		err = 1;
	}
}

char MyStack::Pop(int& err)
{
	if (currentIndex != - 1)
	{
		char sym = cell[currentIndex];
		cell[currentIndex] = ' ';
		currentIndex--;
		err = 0;
		return sym;
		
	}
	else
	{
		err = 1;
		return ' ';
	}
}

bool MyStack::isEmpty()
{
	if (currentIndex == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
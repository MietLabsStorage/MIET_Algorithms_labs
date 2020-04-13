#include <iostream>
#include <string>
#include "MyStack.h"

double recursion(int n)
{
	if (n == 0)
	{
		return 1 / 1;
	}
	else
	{
		return recursion(n - 1) * 2 / n;
	}
}

void main()
{
	//--стек--
	while (true)
	{
		MyStack stack = MyStack(5);
		int err = 0;
		std::string str;
		std::cout << "Write your string (write \"_\" for exit):: ";
		std::cin >> str;
		if (str == "_")
		{
			break;
		}
		else
		{
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == '(')
				{
					stack.Push(str[i], err);
					if (err == 1)
					{
						std::cout << "stack was overflow" << std::endl;
						break;
					}
				}
				else if (str[i] == ')')
				{
					stack.Pop(err);
					if (err == 1)
					{
						std::cout << "stack was empty" << std::endl;
						break;
					}
				}
			}
			if (stack.isEmpty() && err == 0)
			{
				std::cout << "String written right" << std::endl << std::endl;
			}
			else
			{
				std::cout << "String written wrong" << std::endl << std::endl;
			}
		}
	}


	//--рекурсия--

	//An = (2^n)/(n!)
	//рекурсивное представление: An = A_n-1_ * 2/n
	std::cout << "Recursion sequence:\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << recursion(i) << " ";
	}
	std::cout << std::endl;
	/*6. Составить программу для формирования элементов массива.*/
	double* arr;
	arr = new double[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = recursion(i);
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << " ";
	}
}
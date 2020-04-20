#include <iostream>
#include <list>
#include <set>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::set;

struct Edge
{
	int v1, v2;
};

void main()
{
	list<Edge> test1 =
	{
		{1,2},{2,3},{3,4},{4,5},
		{5,6},{6,3},{6,7},{7,1}
	};
	int E1 = 7;
	
	bool** adjacencyMatrix = new bool* [E1];
	for (int i = 0; i < E1; i++)
	{
		adjacencyMatrix[i] = new bool [E1];
	}
	for (int i = 0; i < E1; i++)
	{
		for (int j = 0; j < E1; j++)
		{
			if (i == j)
			{
				adjacencyMatrix[i][j] = 1;
			}
			else
			{
				adjacencyMatrix[i][j] = 0;
			}
		}
	}

	for (list<Edge>::iterator i = test1.begin(); i != test1.end(); ++i)
	{
		adjacencyMatrix[(*i).v1 - 1][(*i).v2 - 1] = 1;
		adjacencyMatrix[(*i).v2 - 1][(*i).v1 - 1] = 1;
	}
	int num;
	bool end;
	bool conjunction;
	for (int k = 1; k < pow(10, E1); k++)
	{
		end = 1;

		for (int i = 0; i < E1; i++)
		{
			conjunction = 0;
			num = k;
			while (num != 0)
			{
				if (num % 10 <= E1 && num % 10 != 0)
				{
					conjunction += adjacencyMatrix[i][num % 10 - 1];
				}
				num /= 10;
			}
			if (!conjunction)
			{
				end = 0;
				break;
			}
		}
		if (end)
		{
			cout << k << endl;
			break;
		}
	}
	cout << endl;
}
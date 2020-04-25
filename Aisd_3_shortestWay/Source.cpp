#include <iostream>
#include <list>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::map;

const int U1 = 12;
const int V1 = 7;

const int U2 = 12;
const int V2 = 8;

struct Arc
{
	int v1, v2;
	int weigth;
};

struct Vertex
{
	int name;
	int way;
};

void main()
{
	//-----Dynamic-----
	cout << "-----Dynamic-----" << endl;
	list<Arc> g1 =
	{
		{1,2,3},{2,6,6},{6,7,4},
		{1,4,4},{4,5,9},{5,7,2},
		{2,3,4},{1,3,8},{4,3,10},
		{3,5,7},{3,7,8},{3,6,6}
	};

	cout << "Graph::\nv1\tv2\tweight\n";
	for (list<Arc>::iterator i = g1.begin(); i != g1.end(); ++i)
	{
		cout << (*i).v1 << "\t" << (*i).v2 << "\t" << (*i).weigth << endl;
	}

	//name - way
	map<int, int> ways;
	map<int, int> opened;
	int adjacencyMatrix[V1][V1];
	for (int i = 0; i < V1; i++)
	{
		ways[i + 1] = -1;
		opened[i + 1] = 1;
		for (int j = 0; j < V1; j++)
		{
			adjacencyMatrix[i][j] = -1;
		}
	}
	for (list<Arc>::iterator i = g1.begin(); i != g1.end(); ++i)
	{
		adjacencyMatrix[(*i).v1 - 1][(*i).v2 - 1] = (*i).weigth;
	}
	ways[1] = 0;
	opened.erase(1);

	//algorithm
	int minWay;
	int minIndex;
	while (!opened.empty())
	{
		for (int j = 1; j < V1; j++)
		{
			minWay = INT_MAX;
			minIndex = -1;
			for (int i = 0; i < V1; i++)
			{
				if (adjacencyMatrix[i][j] != -1)
				{
					if (ways[i + 1] == -1)
					{
						break;
					}
					else
					{
						if (ways[i + 1] + adjacencyMatrix[i][j] < minWay)
						{
							minWay = ways[i + 1] + adjacencyMatrix[i][j];
							minIndex = i + 1;
						}
					}
				}
			}
			if (minIndex != -1)
			{
				ways[j + 1] = minWay;
				opened.erase(j + 1);
			}
		}
		for (map<int, int>::iterator i = opened.begin(); i != opened.end(); ++i)
		{
			cout << (*i).first << " - " << (*i).second << " ";
		}
		cout << endl;
	}
	//end algorithm

	cout << "Vetex - way:\n";
	for (map<int, int>::iterator i = ways.begin(); i != ways.end(); ++i)
	{
		cout << (*i).first << " - " << (*i).second << endl;
	}

	cout << "Ways:\n";
	int _currentVertex;
	for (map<int, int>::iterator i = ways.begin(); i != ways.end(); ++i)
	{
		_currentVertex = (*i).first;
		cout << (*i).first;
		while (_currentVertex != 1)
		{
			for (list<Arc>::iterator j = g1.begin(); j != g1.end(); ++j)
			{
				if ((*j).v2 == _currentVertex && ways[(*j).v1] + (*j).weigth == ways[(*j).v2])
				{
					cout << " <- " << (*j).v1;
					_currentVertex = (*j).v1;
					break;
				}
			}
		}
		cout << endl;
	}
	cout << endl << endl;



	//-----Dejkstra-----
	cout << "-----Dejkstra-----" << endl;
	list<Arc> g2 =
	{
		{1,2,6},{2,3,12},{3,8,1},
		{1,6,10},{6,7,7},{7,8,2},
		{1,4,1},{2,4,1},{6,4,1},
		{7,4,7},{4,5,4},{7,5,5},
		{2,5,1},{3,5,1},{5,8,8}
	};

	cout << "Graph::\nv1\tv2\tweight\n";
	for (list<Arc>::iterator i = g2.begin(); i != g2.end(); ++i)
	{
		cout << (*i).v1 << "\t" << (*i).v2 << "\t" << (*i).weigth << endl;
	}


	//name - way

	//way is known;
	map<int, int> s;
	//way is not known
	map<int, int> f;
	for (list<Arc>::iterator i = g2.begin(); i != g2.end(); ++i)
	{
		f.insert({ (*i).v1, -1 });
		f.insert({ (*i).v2, -1 });
		s.insert({ (*i).v1, -1 });
		s.insert({ (*i).v2, -1 });
	}
	
	int beginVertex = 1;
	s[beginVertex] = 0;
	f.erase(beginVertex);

	//algorithm
	Vertex minD;
	while (!f.empty())
	{
		minD.name = (*f.begin()).first;
		minD.way = (*f.begin()).second;
		for (list<Arc>::iterator i = g2.begin(); i != g2.end(); ++i)
		{
			if (s[(*i).v1] != -1 && s[(*i).v2] == -1)
			{
				if ((*i).weigth + s[(*i).v1] < f[(*i).v2] || f[(*i).v2] == -1)
				{
					f[(*i).v2] = (*i).weigth + s[(*i).v1];
				}
			}
			if (s[(*i).v2] != -1 && s[(*i).v1] == -1)
			{
				if ((*i).weigth + s[(*i).v2] < f[(*i).v1] || f[(*i).v1] == -1)
				{
					f[(*i).v1] = (*i).weigth + s[(*i).v2];
				}
			}
		}
		for (map<int, int>::iterator i = f.begin(); i != f.end(); ++i)
		{
			if ((*i).second < minD.way && (*i).second != -1 || minD.way == -1)
			{
				minD.name = (*i).first;
				minD.way = (*i).second;
			}
		}
		s[minD.name] = minD.way;
		f.erase(minD.name);
	}
	//end alrorithm

	cout << "Vetex - way:\n";
	for (map<int, int>::iterator i = s.begin(); i != s.end(); ++i)
	{
		cout << (*i).first << " - " << (*i).second << endl;
	}

	cout << "Ways:\n";
	int currentVertex;
	Vertex v1, v2;
	for (map<int,int>::iterator i = s.begin(); i != s.end(); ++i)
	{
		currentVertex = (*i).first;
		cout << (*i).first;
		while (currentVertex != 1)
		{
			for (list<Arc>::iterator j = g2.begin(); j != g2.end(); ++j)
			{
				
				for (map<int, int>::iterator k = s.begin(); k != s.end(); ++k)
				{
					if ((*j).v1 == (*k).first)
					{
						v1.name = (*k).first;
						v1.way = (*k).second;
					}
					if ((*j).v2 == (*k).first)
					{
						v2.name = (*k).first;
						v2.way = (*k).second;
					}
				}
				if ((*j).v2 == currentVertex && v1.way + (*j).weigth == v2.way)
				{
					cout << " <- " << v1.name;
					currentVertex = v1.name;
					break;
				}
				if ((*j).v1 == currentVertex && v2.way + (*j).weigth == v1.way)
				{
					cout << " <- " << v2.name;
					currentVertex = v2.name;
					break;
				}
			}
		}
		cout << endl;
	}
}
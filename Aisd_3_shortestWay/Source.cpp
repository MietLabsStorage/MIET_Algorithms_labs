#include <iostream>
#include <list>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::map;

const int U = 12;
const int V = 7;

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
	//graph
	list<Arc> g =
	{
		{1,2,3},{2,6,6},{6,7,4},
		{1,4,4},{4,5,9},{5,7,2},
		{2,3,4},{1,3,8},{4,3,10},
		{3,5,7},{3,7,8},{3,6,6}
	};

	//--Dejkstra--

	//way is known;
	list<Vertex> s;
	//way is not known
	//name - way
	map<int, int> f;
	for (list<Arc>::iterator i = g.begin(); i != g.end(); ++i)
	{
		f.insert({ (*i).v1, -1 });
		f.insert({ (*i).v2, -1 });
	}
	
	int beginVertex = 1;
	s.push_back({ beginVertex,0 });
	f.erase(beginVertex);

	/*for (map<int, int>::iterator i = f.begin(); i != f.end(); ++i)
	{
		cout << (*i).first << " - " << (*i).second << endl;
	}*/

	Vertex minD;
	while (!f.empty())
	{
		minD.name = (*f.begin()).first;
		minD.way = (*f.begin()).second;
		for (list<Arc>::iterator i = g.begin(); i != g.end(); ++i)
		{
			if ((*i).v1 == s.back().name)
			{
				if ((*i).weigth + s.back().way < f[(*i).v2] || f[(*i).v2] == -1)
				{
					f[(*i).v2] = (*i).weigth + s.back().way;
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
		s.push_back({ minD.name,minD.way });
		f.erase(minD.name);
	}

	for (list<Vertex>::iterator i = s.begin(); i != s.end(); ++i)
	{
		cout << (*i).name << " - " << (*i).way << endl;
	}


	//--Dinamic--

	//nmae - way
	map<int, int> ways;
	map<int, int> opened;
	int adjacencyMatrix[V][V];
	for (int i = 0; i < V; i++)
	{
		ways[i + 1] = -1;
		opened[i + 1] = 1;
		for (int j = 0; j < V; j++)
		{
			adjacencyMatrix[i][j] = -1;
		}
	}
	for (list<Arc>::iterator i = g.begin(); i != g.end(); ++i)
	{
		adjacencyMatrix[(*i).v1-1][(*i).v2-1] = (*i).weigth;
	}
	ways[beginVertex] = 0;
	opened.erase(beginVertex);

	int minWay;
	int minIndex;
	while (!opened.empty())
	{
		for (int j = 1; j < V; j++)
		{
			minWay = INT_MAX;
			minIndex = -1;
			for (int i = 0; i < V; i++)
			{
				if (adjacencyMatrix[i][j] != -1)
				{
					if (ways[i+1] == -1)
					{
						break;
					}
					else
					{
						if (ways[i+1] + adjacencyMatrix[i][j] < minWay)
						{
							minWay = ways[i+1] + adjacencyMatrix[i][j];
							minIndex = i+1;
						}
					}
				}
			}
			if (minIndex != -1)
			{
				ways[j+1] = minWay;
				opened.erase(j+1);
			}
		}
		for (map<int, int>::iterator i = opened.begin(); i != opened.end(); ++i)
		{
			cout << (*i).first << " - " << (*i).second << " ";
		}
		cout << endl;
	}

	for (map<int, int>::iterator i = ways.begin(); i != ways.end(); ++i)
	{
		cout << (*i).first << " - " << (*i).second << endl;
	}
}
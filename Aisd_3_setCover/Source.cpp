#include <iostream>
#include <list>
#include <map>
#include <set>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::map;
using std::set;

struct Edge
{
	int v1, v2;
};

struct Edges
{
	list<Edge> edge;
	int V;
};


void main()
{
	list<Edges> tests =
	{
		{{{1,2},{2,3},{3,4},{4,5},{5,6},{6,3},{6,7},{7,1}}, 7},
		{{{1,2},{2,3},{3,4},{4,5},{5,6},{6,1},{2,7},{3,7},{5,7},{6,7}}, 7},
		{{{1,2},{1,7},{2,3},{3,1},{2,8},{8,10},{10,4},{4,3},{4,5},{5,6},{5,9}}, 10 },
		{{{1,2},{1,3},{1,4},{4,10},{10,9},{3,9},{3,6},{6,7},{7,5},{5,2},{5,8},{8,7},{7,11},{11,12},{2,4},{4,3}}, 12},
		{{{1,2},{2,3},{3,6},{6,5},{5,4},{4,1},{6,11},{11,12},{5,7},{7,8},{8,9},{9,10},{4,13},{13,15},{15,16},{16,14},{14,13}}, 16}
	};


	//-----Brute-force-----
	for (list<Edges>::iterator test = tests.begin(); test != tests.end(); ++test)
	{
		bool** adjacencyMatrix = new bool* [(*test).V];
		for (int i = 0; i < (*test).V; i++)
		{
			adjacencyMatrix[i] = new bool[(*test).V];
		}
		for (int i = 0; i < (*test).V; i++)
		{
			for (int j = 0; j < (*test).V; j++)
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

		for (list<Edge>::iterator i = (*test).edge.begin(); i != (*test).edge.end(); ++i)
		{
			adjacencyMatrix[(*i).v1 - 1][(*i).v2 - 1] = 1;
			adjacencyMatrix[(*i).v2 - 1][(*i).v1 - 1] = 1;
		}
		int num;
		bool end;
		bool conjunction;
		for (int k = 1; k < pow(10, (*test).V); k++)
		{
			//cout << k << endl;
			end = 1;
			for (int i = 0; i < (*test).V; i++)
			{
				conjunction = 0;
				num = k;
				while (num != 0)
				{
					if (num % (*test).V <= (*test).V && num % (*test).V != 0)
					{
						conjunction += adjacencyMatrix[i][num % (*test).V - 1];
					}
					num /= (*test).V;
				}
				if (!conjunction)
				{
					end = 0;
					break;
				}
			}
			if (end)
			{
				cout << "test:: {";
				for (list<Edge>::iterator iter = (*test).edge.begin(); iter != (*test).edge.end(); ++iter)
				{
					cout << "[" << (*iter).v1 << "-" << (*iter).v2 << "]";
				}
				cout << "}\n Vertexes: ";
				while (k != 0)
				{
					cout << k % (*test).V << " ";
					k /= (*test).V;
				}
				cout << endl << endl;
				break;
			}
		}
	}




	//-----Heuristic-----
	for (list<Edges>::iterator test = tests.begin(); test != tests.end(); ++test)
	{
		map<int, map<int, bool>> vertex;
		for (list<Edge>::iterator iter = (*test).edge.begin(); iter != (*test).edge.end(); ++iter)
		{
			(vertex[(*iter).v1])[(*iter).v2] = 1;
			(vertex[(*iter).v2])[(*iter).v1] = 1;
		}

		/*for (map<int, map<int,bool>>::iterator iter = vertex.begin(); iter != vertex.end(); ++iter)
		{
			cout << (*iter).first << ": ";
			for (map<int, bool>::iterator i = (*iter).second.begin(); i != (*iter).second.end(); ++i)
			{
				cout << (*i).first << " ";
			}
			cout << endl;
		}*/

		list<int> cover;
		set<int> uncover;
		while (cover.size() + uncover.size() != (*test).V)
		{
			int maxNeighbs = 0;
			int nameOfMax = 0;
			for (map<int, map<int, bool>>::iterator iter = vertex.begin(); iter != vertex.end(); ++iter)
			{
				if ((*iter).second.size() >= maxNeighbs)
				{
					maxNeighbs = (*iter).second.size();
					nameOfMax = (*iter).first;
				}
			}
			//list<int> last_add;
			for (map<int, map<int, bool>>::iterator iter = vertex.begin(); iter != vertex.end(); ++iter)
			{
				/*(*iter).second.erase(nameOfMax);*/
				if ((*iter).second.empty() || (*iter).second.size() <= 2 && (*iter).second[nameOfMax] == 1)
				{
					uncover.insert((*iter).first);
					//last_add.push_back((*iter).first);
					//vertex.erase((*iter).first);
				}
				(*iter).second.erase(nameOfMax);
			}
			/*if (!last_add.empty())
			{
				for (list<int>::iterator i = last_add.begin(); i != last_add.end(); ++i)
				{
					vertex.erase((*i));
				}
				last_add.clear();
			}*/
			cover.push_back(nameOfMax);
			vertex.erase(nameOfMax);
			
		}

		for (list<int>::iterator i = cover.begin(); i != cover.end(); ++i)
		{
			cout << "|" << (*i) << "|";
		}
		cout << endl;
	}
	
}
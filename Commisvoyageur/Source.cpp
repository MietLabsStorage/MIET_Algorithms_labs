#include <iostream>
#include <list>
#include <vector>

#define TEMPSIZE 6

using namespace std;

const int inf = INT_MAX;

struct Penalty
{
	int value;
	int i;
	int j;
};

struct Matrix
{
	int size;
	int** elem;
	vector<int> trueI;
	vector<int> trueJ;
};

class Node
{
public:
	int a;
	int b;
	int weight;
	list<int> way;
	Matrix matrix;

	Node(int a, int b, int weight, list<int> way, Matrix matrix)
	{
		this->a = a;
		this->b = b;
		this->weight = weight;
		//this->way.swap(way);
		this->way.clear();
		for (list<int>::iterator i = way.begin(); i != way.end(); ++i)
		{
			this->way.push_back(*i);
		}
		this->matrix.size = matrix.size;
		this->matrix.trueI.clear();
		this->matrix.trueJ.clear();
		for (vector<int>::iterator i = matrix.trueI.begin(); i != matrix.trueI.end(); ++i)
		{
			this->matrix.trueI.push_back(*i);
		}
		for (vector<int>::iterator i = matrix.trueJ.begin(); i != matrix.trueJ.end(); ++i)
		{
			this->matrix.trueJ.push_back(*i);
		}
		this->matrix.elem = new int* [TEMPSIZE];
		for (int i = 0; i < TEMPSIZE; i++)
		{
			this->matrix.elem[i] = new int[TEMPSIZE];
			for (int j = 0; j < TEMPSIZE; j++)
			{
				this->matrix.elem[i][j] = matrix.elem[i][j];
			}
		}
	}
};

void showMatrix(Matrix matrix)
{
	for (int i = 0; i < TEMPSIZE; i++)
	{
		for (int j = 0; j < TEMPSIZE; j++)
		{
			if (matrix.elem[i][j] != inf)
			{
				cout << matrix.elem[i][j] << '\t';
			}
			else
			{
				cout << "inf\t";
			}
		}
		cout << '\n';
	}
}

int* reductByRow(Matrix& matrix)
{
	int* hi = new int[matrix.size];
	for (int i = 0; i < matrix.size; i++)
	{
		int minElem = INT_MAX;
		for (int j = 0; j < matrix.size; j++)
		{
			if (matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] < minElem)
			{
				minElem = matrix.elem[matrix.trueI[i]][matrix.trueJ[j]];
			}
		}
		hi[i] = minElem;
		for (int j = 0; j < matrix.size; j++)
		{
			if (matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] != inf)
			{
				matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] -= hi[i];
			}
		}
	}
	return hi;
}

int* reductByColumn(Matrix& matrix)
{
	int* hj = new int[matrix.size];
	for (int j = 0; j < matrix.size; j++)
	{
		int minElem = INT_MAX;
		for (int i = 0; i < matrix.size; i++)
		{
			if (matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] < minElem)
			{
				minElem = matrix.elem[matrix.trueI[i]][matrix.trueJ[j]];
			}
		}
		hj[j] = minElem;
		for (int i = 0; i < matrix.size; i++)
		{
			if (matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] != inf)
			{
				matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] -= hj[j];
			}
		}
	}
	return hj;
}

Penalty penaltyFunction(Matrix matrix)
{
	list<Penalty> penalties;
	for (int i = 0; i < matrix.size; i++)
	{
		for (int j = 0; j < matrix.size; j++)
		{
			Penalty D;
			if (matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] == 0)
			{
				D.value = 0;
				int min = INT_MAX;
				for (int ki = 0; ki < matrix.size; ki++)
				{
					if (ki != i)
					{
						if (matrix.elem[matrix.trueI[ki]][matrix.trueJ[j]] < min)
						{
							min = matrix.elem[matrix.trueI[ki]][matrix.trueJ[j]];
						}
					}
				}
				D.value += min;
				min = INT_MAX;
				for (int kj = 0; kj < matrix.size; kj++)
				{
					if (kj != j)
					{
						if (matrix.elem[matrix.trueI[i]][matrix.trueJ[kj]] < min)
						{
							min = matrix.elem[matrix.trueI[i]][matrix.trueJ[kj]];
						}
					}
				}
				D.value += min;
				D.i = matrix.trueI[i];
				D.j = matrix.trueJ[j];
				penalties.push_back(D);
			}
		}
	}
	Penalty maxD;
	maxD.value = -1000;
	for (list<Penalty>::iterator k = penalties.begin(); k != penalties.end(); ++k)
	{
		if ((*k).value > maxD.value)
		{
			maxD.i = (*k).i;
			maxD.j = (*k).j;
			maxD.value = (*k).value;
		}
	}
	return maxD;
}

int firstElem(Matrix& matrix)
{
	int R = 0;
	int* hi = new int[matrix.size];
	int* hj = new int[matrix.size];
	hi = reductByRow(matrix);
	hj = reductByColumn(matrix);
	for (int k = 0; k < matrix.size; k++)
	{
		R += hi[k];
		R += hj[k];
	}
	return R;
}

Node currNode(list<Node>& nodes)
{
	Node currentNode = nodes.back();
	list<Node>::iterator currIter = nodes.end();
	for (list<Node>::iterator i = nodes.begin(); i != nodes.end(); ++i)
	{
		if ((*i).weight <= currentNode.weight)
		{
			currentNode = (*i);
			currIter = i;
		}
	}
	nodes.erase(currIter);
	return currentNode;
}

Node currNode(list<Node>& nodes, bool e)
{
	Node currentNode = nodes.back();
	list<Node>::iterator currIter = nodes.end();
	for (list<Node>::iterator i = nodes.begin(); i != nodes.end(); ++i)
	{
		if ((*i).weight <= currentNode.weight)
		{
			currentNode = (*i);
			currIter = i;
		}
	}
	return currentNode;
}


void matrixResize(int di, int dj, Node& currentNode)
{
	vector<int>::iterator k;
	for (vector<int>::iterator i = currentNode.matrix.trueI.begin(); i != currentNode.matrix.trueI.end(); ++i)
	{
		if ((*i) == di)
		{
			k = i;
			break;
		}
	}
	currentNode.matrix.trueI.erase(k);
	for (vector<int>::iterator j = currentNode.matrix.trueJ.begin(); j != currentNode.matrix.trueJ.end(); ++j)
	{
		if ((*j) == dj)
		{
			k = j;
			break;
		}
	}
	currentNode.matrix.trueJ.erase(k);
	currentNode.matrix.size--;
	currentNode.matrix.elem[dj][di] = inf;
}

void newNodes(list<Node>& nodes)
{
	Node currentNode = currNode(nodes);

	//work with left node
	Penalty D;
	D = penaltyFunction(currentNode.matrix);
	list<int> tempWay = currentNode.way;
	tempWay.push_back(D.i);
	tempWay.push_back(D.j);
	Node tempNode = Node(D.i, D.j, currentNode.weight + D.value, tempWay, currentNode.matrix);
	nodes.push_back(tempNode);

	matrixResize(D.i, D.j, currentNode);

	//work with right node
	int H = 0;
	int* hi = new int[currentNode.matrix.size];
	int* hj = new int[currentNode.matrix.size];
	hi = reductByRow(currentNode.matrix);
	hj = reductByColumn(currentNode.matrix);
	for (int k = 0; k < currentNode.matrix.size; k++)
	{
		H += hi[k];
		H += hj[k];
	}
	tempWay.clear();
	tempWay = currentNode.way;
	tempWay.push_back(D.i);
	tempWay.push_back(D.j);
	tempNode = Node(D.i, D.j, currentNode.weight + H, tempWay, currentNode.matrix);
	nodes.push_back(tempNode);
}

int main()
{
	Matrix matrix;
	int size = 6;
	matrix.size = size;
	matrix.elem = new int* [size];
	matrix.trueI = vector<int>(size);
	matrix.trueJ = vector<int>(size);
	for (int k = 0; k < size; k++)
	{
		matrix.elem[k] = new int[size];
		matrix.trueI[k] = k;
		matrix.trueJ[k] = k;
	}

	int tempMatrix[6][6] =
	{
		{inf, 3, 25, 4, 42, 12},
		{9, inf, 18, 5, 2, inf},
		{17, 5, inf, 40, inf, 8},
		{12, 1, 43, inf, 11, 3},
		{32, 20, inf, 16, inf, 9},
		{13, 38, 22, 7, 28, inf}
	};

	for (int i = 0; i < matrix.size; i++)
	{
		for (int j = 0; j < matrix.size; j++)
		{
			matrix.elem[matrix.trueI[i]][matrix.trueJ[j]] = tempMatrix[i][j];
		}
	}
	showMatrix(matrix); cout << endl;
	int R = firstElem(matrix);
	
	list<int> tempList;
	tempList.push_back(-8);
	list<Node> nodes;
	Node tempNode = Node(-8, -8, R, tempList, matrix);
	nodes.push_back(tempNode);

	while (currNode(nodes, 1).matrix.size != 2)
	{
		newNodes(nodes);
	}

	Node finNode = currNode(nodes, 1);
	int finWay = -7;
	cout << "Way:: ";
	for (list<int>::iterator i = finNode.way.begin(); i != finNode.way.end(); ++i)
	{
		if (finWay != *i + 1)
		{
			finWay = *i + 1;
			cout << finWay << " ";
		}
	}
	cout << endl << "Weight:: " << finNode.weight;

	return 0;
}

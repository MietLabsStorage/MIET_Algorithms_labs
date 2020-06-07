#include "TuringMachine.h"

int convert(char c)
{
	if (c == 'k' || c == 'a')
	{
		return 10;
	}
	else
	{
		return c-48;
	}
}

void TuringMachine::run()
{
	logical curZ;
	int BG = convert(B[G]);
	curZ = Z[convert(Q)][BG];
	while (true)
	{
		if (curZ.value != '-')
		{
			B[G] = curZ.value;
		}
		if (curZ.status != '-')
		{
			Q = curZ.status;
		}
		if (curZ.move == 'R')
		{
			G++;
		}
		if (curZ.move == 'L')
		{
			BG = convert(B[G-1]);
			G--;
		}
		if (B[G] == 'r')
		{
			BG = 10;
		}
		else if (B[G] == '*')
		{
			BG = 11;
		}
		if (curZ.status == '-' && curZ.value == '-' && curZ.move == '-' || curZ.status == 'k' && curZ.value == '1' && curZ.move == 'H')
		{
			break;
		}
		curZ = Z[convert(Q)][BG];
	}
}

void TuringMachine::show()
{
	for (int i = 0; i < 15; i++)
	{
		cout << B[i] << " ";
	}
}

void TuringMachine::showTable()
{
	for (vector<vector<logical>>::iterator i = Z.begin(); i != Z.end(); ++i)
	{
		for (vector<logical>::iterator j = (*i).begin(); j != (*i).end(); ++j)
		{
			if ((*j).status != '-')
			{
				cout << (*j).status;
			}
			if ((*j).value != '-')
			{
				cout << (*j).value;
			}
			if ((*j).move != '-')
			{
				cout << (*j).move;
			}
			if ((*j).status == '-' && (*j).value == '-' && (*j).move == '-')
			{
				cout << '-';
			}
			cout << '\t';
		}
		cout << endl;
	}
}
#include "TuringMachine.h"

int convert(char c)
{
	if (c == 'k')
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
		//cout << curZ.status << curZ.value << curZ.move << endl;
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
			G++;
		}
		if (B[G] == 'r')
		{
			BG = 10;
		}
		else if (B[G] == '*')
		{
			BG = 11;
		}
		/*else
		{
			BG = convert(B[G]);
		}*/
		curZ = Z[convert(Q)][BG];
		if (curZ.status == '-' && curZ.value == '-' && curZ.move == '-' || curZ.status == 'k' && curZ.value == '1' && curZ.move == 'H')
		{
			break;
		}
	}
}

void TuringMachine::show()
{
	for (int i = 0; i < 15; i++)
	{
		cout << B[i] << " ";
	}
}
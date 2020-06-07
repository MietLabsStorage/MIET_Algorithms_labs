#include <iostream>
#include "TuringMachine.h"

using namespace std;

int main()
{
	TuringMachine TM = TuringMachine('5');
	cout << "tape before:: ";
	TM.show(); cout << endl;
	TM.run();
	cout << "tape after::  ";
	TM.show(); cout << endl;
	cout << endl << "Functional table:: " << endl;
	TM.showTable();
	return 0;
}
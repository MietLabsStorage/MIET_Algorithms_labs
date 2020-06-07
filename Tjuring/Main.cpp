#include <iostream>
#include "TuringMachine.h"

using namespace std;

int main()
{
	TuringMachine TM = TuringMachine('5');
	TM.show(); cout << endl;
	TM.run();
	TM.show();

	return 0;
}
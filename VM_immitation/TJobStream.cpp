#include "TJobStream.h"
#include <iostream>

TJobStream::TJobStream(int intens)
{
	jobIntens = 1 / intens;
}

int TJobStream::getNewJob()
{
	return rand() % 1000000;
}
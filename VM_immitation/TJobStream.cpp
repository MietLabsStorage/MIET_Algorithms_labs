#include "TJobStream.h"
#include <iostream>

TJobStream::TJobStream(int intens)
{
	jobIntens = 1 / intens;
}

int TJobStream::getNewJob()
{
	if (rand() % RAND_MAX < jobIntens)
	{
		return 1;
	}
	return 0;
}
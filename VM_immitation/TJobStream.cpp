#include "TJobStream.h"
#include <iostream>

TJobStream::TJobStream(int intens)
{
	jobIntens = (double) 1 / intens;
}

int TJobStream::getNewJob()
{

	if ((double) rand() / RAND_MAX < jobIntens)
	{
		return 1;
	}
	return 0;
}
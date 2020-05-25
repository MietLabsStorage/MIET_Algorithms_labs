#include "TProc.h"
#include <iostream>

TProc::TProc(int rate)
{
	procRate = (double) 1 / rate;
}

int TProc::IsProcBusy()
{
	//srand(time(0));
	if ((double) rand() / RAND_MAX >= procRate)
	{
		return 1;
	}
	return 0;
}

int TProc::RunNewJob(int jobId)
{
	return jobId;
}
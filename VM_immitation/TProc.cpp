#include "TProc.h"
#include <iostream>

TProc::TProc(int rate)
{
	procRate = 1 / rate;
}

int TProc::IsProcBusy()
{
	if (rand() % RAND_MAX >= procRate)
	{
		return 1;
	}
	return 0;
}

int TProc::RunNewJob(int jobId)
{
	return jobId;
}
#include "TProc.h"
#include <iostream>

TProc::TProc(int rate)
{
	procRate = (double) 1 / rate;
}

int TProc::IsProcBusy()
{
	if ((double) rand() / RAND_MAX >= procRate)
	{
		return 1;
	}
	return 0;
}

int TProc::RunNewJob(int jobId)
{
	this->jobId = jobId;
	return jobId;
}
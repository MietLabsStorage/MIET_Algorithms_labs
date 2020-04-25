#include "TProc.h"

TProc::TProc(int rate)
{
	procRate = 1 / rate;
}

int TProc::IsProcBusy()
{
	return 0;
}

int TProc::RunNewJob(int jobId)
{
	return jobId;
}
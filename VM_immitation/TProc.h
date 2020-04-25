#pragma once
class TProc
{
	double procRate;
	int jobId;

public:
	TProc(int rate);
	int IsProcBusy();
	int RunNewJob(int jobId);
};


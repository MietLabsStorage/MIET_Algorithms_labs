#include <iostream>
#include "TJobStream.h"
#include "TProc.h"
#include "TQueue.h"
#include "TStack.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int jobIntens;
	int procRate;
	int tacts;

	int overflow;
	int taskCount;
	int downtime;
	int finished;

	while (true)
	{
		overflow = 0;
		taskCount = 0;
		downtime = 0;
		finished = 0;

		cout << "-----VM immitation-----" << endl;
		cout << "job intens = "; cin >> jobIntens;
		cout << "proc rate = "; cin >> procRate;
		cout << "tacts = "; cin >> tacts;

		TQueue<int> queue = TQueue<int>(5);
		TProc proc = TProc(procRate);
		TJobStream jobStream = TJobStream(jobIntens);

		int newTask;

		for (int i = 0; i < tacts; i++)
		{
			newTask = (i + 1) * jobStream.getNewJob();
			if (newTask != 0)
			{
				taskCount++;
				if (!queue.isFull())
				{
					queue.put(newTask);
				}
				else
				{
					overflow++;
				}
			}

			if (!queue.isEmpty())
			{
				if (!proc.IsProcBusy())
				{
					proc.RunNewJob(queue.get());
					finished++;
				}
			}
			else
			{
				downtime++;
			}
					}

		cout << "---Report---" << endl;
		cout << "tasks created: " << taskCount << endl;
		cout << "rejection: " << overflow << endl;
		cout << "running speed: " << tacts / finished << "tacts per task" << endl;
		cout << "downtime: " << downtime << "tacts" << endl;
	}
	return 0;
}
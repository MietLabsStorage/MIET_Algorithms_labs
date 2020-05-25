#include <iostream>
#include "TJobStream.h"
#include "TProc.h"
#include "TQueue.h"
#include "TStack.h"

#include <time.h>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	srand(time(0));

	int jobIntens;
	int procRate;
	int tacts;

	int overflow;
	int taskCount;
	int downtime;
	int finished;

	int queueCount;

	while (true)
	{
		overflow = 0;
		taskCount = 0;
		downtime = 0;
		finished = 0;

		int emptierQueue = 0;
		int fullerQueue = 0;

		cout << "-----VM immitation-----" << endl;
		cout << "job intens = "; cin >> jobIntens;
		cout << "proc rate = "; cin >> procRate;
		cout << "tacts = "; cin >> tacts;
		cout << "Queue threads = "; cin >> queueCount;

		TQueue* queue = new TQueue[queueCount];
		for (int i = 0; i < queueCount; i++)
		{
			queue[i].setSize(5);
		}

		TProc proc = TProc(procRate);
		TJobStream jobStream = TJobStream(jobIntens);

		int newTask;

		for (int i = 0; i < tacts; i++)
		{
			newTask = (i + 1) * jobStream.getNewJob();
			if (newTask != 0)
			{
				taskCount++;
				if (!queue[emptierQueue].isFull())
				{
					queue[emptierQueue].put(newTask);
					for (int i = 0; i < queueCount; i++)
					{
						if (queue[i].count() < queue[emptierQueue].count())
						{
							emptierQueue = i;
						}
					}
				}
				else
				{
					overflow++;
				}
			}

			if (!queue[fullerQueue].isEmpty())
			{
				if (!proc.IsProcBusy())
				{
					proc.RunNewJob(queue[fullerQueue].get());
					for (int i = 0; i < queueCount; i++)
					{
						if (queue[i].count() > queue[fullerQueue].count())
						{
							fullerQueue = i;
						}
					}
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
		if (finished != 0)
		{
			cout << "running speed: " << (double) tacts / finished << " tacts per task" << endl;
		}
		else
		{
			cout << "running speed: " << "Inf" << " tacts per task" << endl;
		}
		cout << "downtime: " << downtime << " tacts" << endl;
		cout << endl;
	}
	return 0;
}
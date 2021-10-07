/*
 * JobShop.cpp
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps & Sandra ter Maat
 */

#include "JobShop.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <memory>
#include <limits>

#include "Job.h"
#include "Machine.h"

unsigned long long JobShop::time = 0;

JobShop::JobShop() :
		allJobsDone(false)
{
}

JobShop::~JobShop()
{
}

void JobShop::readFile(std::ifstream &file)
{

	std::string regel1;
	std::getline(file, regel1);
	std::regex num("[0-9]+");
	std::sregex_iterator next(regel1.begin(), regel1.end(), num);
	std::sregex_iterator end;
	std::smatch match = *next;
	std::string jobCountString = match.str(0);
	unsigned int jobCount = stoi(jobCountString);
	++next;
	std::smatch matchb = *next;
	std::string machineCountString = matchb.str(0);
	unsigned int machineCount = stoi(machineCountString);
	makeMachines(machineCount);
	for (unsigned char x = 0; x < jobCount; ++x)
	{
		std::string regel;
		std::getline(file, regel);
		Job a(regel);
		a.setJobId(x);
		jobs.push_back(a);
	}
	file.close();
}

void JobShop::print()
{
	for (unsigned char currentJobIndex = 0; currentJobIndex < jobs.size();
			++currentJobIndex)
	{
		Job &currentJob = jobs[currentJobIndex];
		// cout voor print aan einde van programma.
		std::cout << currentJob.getJobId() << " " << currentJob.getStartTime()
				<< " " << currentJob.getEndTime() << std::endl;
	}
}
void JobShop::makeMachines(unsigned int machineCount)
{
	for (unsigned short x = 0; x < machineCount; ++x)
	{
		Machine machine(x);
		machines.push_back(machine);
	}
}

void JobShop::checkMachines()
{
	unsigned long long aantal = machines.size();
	for (unsigned long long x = 0; x < aantal; ++x)
	{
		if (machines[x].isWaiting() == false)
		{
			machines[x].isDone();
		}
	}

	for (unsigned long long x = 0; x < aantal; ++x)
	{
		if (machines[x].isWaiting() == true)
		{
			selectTask(machines[x]);
		}
	}
}

unsigned long long JobShop::getTime()
{
	return time;
}

bool JobShop::checkIfJobsAreDone()
{
	bool done = true;
	std::for_each(jobs.begin(), jobs.end(), [&done](Job &job)
	{
		job.checkIfTasksAreDone();
		if(job.isJobIsDone() == false)
		{
			done = false;
		}
	});
	return done;
}

void JobShop::selectTask(Machine &machine)
{
	Job *jobForMachine = NULL;
	unsigned short machineID = machine.getMachineId();
	unsigned long long remainingJobTime = 0;
	std::for_each(jobs.begin(), jobs.end(),
			[machineID, &jobForMachine, &remainingJobTime](
					Job &job)
					{
						if(job.getCurrentMachineId() == machineID)
						{
							if(remainingJobTime < job.getTimeLeft() && job.isCurrentTaskDone() == false)
							{
								remainingJobTime = job.getTimeLeft();
								jobForMachine = &(job);
							}
						}
					});

	if (jobForMachine != NULL)
	{
		machine.setCurrentJob(jobForMachine);
	}
}

void JobShop::nextEvent()
{
	unsigned long long earliestDoneTime =
			std::numeric_limits<unsigned long long>::max();

	unsigned long long aantal = machines.size();
	for (unsigned long long x = 0; x < aantal; ++x)
	{
		if (machines[x].isWaiting() == false)
		{
			if (machines[x].getDoneTime() < earliestDoneTime)
			{
				earliestDoneTime = machines[x].getDoneTime();
			}
		}
	}
	if (earliestDoneTime != std::numeric_limits<unsigned long long>::max())
	{
		time = earliestDoneTime;
	}
}

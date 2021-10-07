/*
 * Machine.cpp
 *
 *  Created on: 29 Sep 2020
 *      Author: Merlijn Warps
 */

#include "Machine.h"
#include "JobShop.h"
#include <iostream>

Machine::Machine(unsigned short id) :
		machineID(id), currentJob(NULL), doneTime(0), waiting(true)
{
}

Machine::~Machine()
{
}

bool Machine::isDone()
{
	if (JobShop::getTime() >= doneTime)
	{
		if (currentJob != NULL)
		{
			currentJob->tellJobTaskIsDone();
		}
		waiting = true;
		return true;
	}
	else if (waiting)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Machine::setCurrentJob(Job *newJob)
{
	waiting = false;
	currentJob = newJob;
	doneTime = (currentJob->getCurrentTaskDuration() + JobShop::getTime());
	currentJob->tellJobTaskHasStarted();
}

unsigned short Machine::getMachineId() const
{
	return machineID;
}

unsigned long long Machine::getDoneTime() const
{
	return doneTime;
}

bool Machine::isWaiting() const
{
	return waiting;
}


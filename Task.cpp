/*
 * Task.cpp
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps & Sandra ter Maat
 */

#include "Task.h"

#include <regex>
#include <string>

#include "JobShop.h"

Task::Task(const unsigned int newMachine, const unsigned int newDuration) :
		machine(newMachine), duration(newDuration), done(false)
{

}

Task::~Task()
{
}

unsigned int Task::getDuration() const
{
	return duration;
}

unsigned int Task::getMachine() const
{
	return machine;
}

bool Task::taskIsDone() const
{
	return done;
}

void Task::setTaskAsDone(bool done)
{
	this->done = done;
	taskEndTime = JobShop::getTime();
}

unsigned long long Task::getTaskEndTime() const
{
	return taskEndTime;
}

unsigned long long Task::getTaskStartTime() const
{
	return taskStartTime;
}

void Task::taskStarted()
{
	taskStartTime = JobShop::getTime();
}

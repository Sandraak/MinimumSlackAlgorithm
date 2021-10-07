/*
 * Job.cpp
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps & Sandra ter Maat
 */

#include "Job.h"

#include <regex>
#include <string>
#include <iostream>
#include <sstream>

#include "Task.h"

Job::Job(std::string line) :
		currentTask(0)
{
	readLine(line);
	updateTimeLeft();
}

Job::~Job()
{
}

void Job::readLine(std::string line)
{
	unsigned char order = 0;
	std::regex task("[0-9]+");
	std::sregex_iterator next(line.begin(), line.end(), task);
	std::sregex_iterator end;
	while (next != end)
	{
		std::smatch match = *next;
		std::string aString = match.str(0);
		unsigned int machine = stoi(aString);
		++next;
		std::smatch matchb = *next;
		std::string bString = matchb.str(0);
		unsigned int duration = stoi(bString);
		Task c(machine, duration);
		tasks.push_back(c);
		++order;
		++next;
	}
}

unsigned short Job::getJobId() const
{
	return job_id;
}

void Job::setJobId(unsigned short jobId)
{
	job_id = jobId;
}

unsigned long long Job::getEndTime() const
{
	return endTime;
}

unsigned long long Job::getStartTime() const
{
	return startTime;
}

unsigned long long Job::getCurrentTaskDuration() const
{
	return tasks[currentTask].getDuration();
}

unsigned int Job::getCurrentMachineId() const
{
	return tasks[currentTask].getMachine();
}

unsigned long long Job::getNumberOfTasks() const
{
	return tasks.size();
}

void Job::updateTimeLeft()
{
	unsigned long long remainingTime = 0;
	for (unsigned short i = 0; i < getNumberOfTasks(); ++i)
	{
		if (tasks[i].taskIsDone() == false)
		{
			remainingTime += tasks[i].getDuration();
		}
	}
	timeLeft = remainingTime;
}

void Job::tellJobTaskIsDone()
{
	tasks[currentTask].setTaskAsDone(true);
	checkIfTasksAreDone();
	if (jobIsDone == false)
	{
		prepareNextTask();
	}
	else
	{
		endTime = tasks[currentTask].getTaskEndTime();
	}
}

void Job::tellJobTaskHasStarted()
{
	tasks[currentTask].taskStarted();
	if (currentTask == 0)
	{
		startTime = tasks[currentTask].getTaskStartTime();
	}
}

void Job::prepareNextTask()
{
	++currentTask;
	updateTimeLeft();
}

void Job::checkIfTasksAreDone()
{
	bool done = true;
	std::for_each(tasks.begin(), tasks.end(), [&done](Task &task)
	{
		if(task.taskIsDone() == false)
		{
			done = false;
		}
	});
	jobIsDone = done;
}

bool Job::isJobIsDone() const
{
	return jobIsDone;
}

bool Job::isCurrentTaskDone()
{
	return tasks[currentTask].taskIsDone();
}

unsigned long long Job::getTimeLeft() const
{
	return timeLeft;
}

unsigned short Job::getCurrentTask() const
{
	return currentTask;
}

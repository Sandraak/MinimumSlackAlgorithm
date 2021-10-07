/*
 * Task.h
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps & Sandra ter Maat
 */

#ifndef TASK_H_
#define TASK_H_

#include <string>

class Task {
public:
	Task(const unsigned int newMachine, const unsigned int newDuration);
	virtual ~Task();

	unsigned int getDuration() const;
	unsigned int getMachine() const;

	bool taskIsDone() const;
	void setTaskAsDone(bool done);
	void taskStarted();

	unsigned long long getTaskEndTime() const;
	unsigned long long getTaskStartTime() const;


private:
	unsigned int machine;
	unsigned int duration;
	bool done;
	unsigned long long taskStartTime;
	unsigned long long taskEndTime;
};

#endif /* TASK_H_ */

/*
 * Machine.h
 *
 *  Created on: 29 Sep 2020
 *      Author: Merlijn Warps
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "Job.h"

class Machine
{
public:
	Machine(unsigned short id);
	virtual ~Machine();
	bool isDone();
	void setCurrentJob(Job* newJob);
	unsigned short getMachineId() const;
	unsigned long long getDoneTime() const;
	bool isWaiting() const;

private:
	unsigned short machineID;
	Job* currentJob;
	unsigned long long doneTime;
	bool waiting;
};

#endif /* MACHINE_H_ */

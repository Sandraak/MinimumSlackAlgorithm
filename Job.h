/*
 * Job.h
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps & Sandra ter Maat
 */

#ifndef JOB_H_
#define JOB_H_

#include <vector>
#include <string>

#include "Task.h"

class Job {
public:
	Job(std::string line);
	virtual ~Job();
	void readLine(std::string line);
	unsigned short getJobId() const;
	void setJobId(unsigned short jobId);

	unsigned long long getEndTime() const;
	unsigned long long getStartTime() const;

	void updateTimeLeft();

	unsigned long long getCurrentTaskDuration() const;
	unsigned int getCurrentMachineId() const;

	unsigned long long getNumberOfTasks() const;

	bool isCurrentTaskDone();
	void tellJobTaskIsDone();
	void tellJobTaskHasStarted();
	void prepareNextTask();
	void checkIfTasksAreDone();
	bool isJobIsDone() const;
	unsigned long long getTimeLeft() const;
	unsigned short getCurrentTask() const;

private:
	std::vector<Task> tasks;
	unsigned long long timeLeft;
	unsigned short job_id;
	bool jobIsDone;
	unsigned short currentTask;
	unsigned long long startTime;
	unsigned long long endTime;

};

#endif /* JOB_H_ */

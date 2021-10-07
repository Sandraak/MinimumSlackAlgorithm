/*
 * JobShop.h
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps & Sandra ter Maat
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_

#include <vector>

#include "Job.h"
#include "Machine.h"

class JobShop {
public:
	JobShop();
	virtual ~JobShop();
	void readFile(std::ifstream& file);
	void print();
	void makeMachines(unsigned int machineCount);
	void checkMachines();
	bool checkIfJobsAreDone();
	void nextEvent();
	void selectTask(Machine &machine);

	static unsigned long long getTime();
private:
	std::vector<Job> jobs;
	std::vector<Machine> machines;
	bool allJobsDone;
	static unsigned long long time;
};

#endif /* JOBSHOP_H_ */

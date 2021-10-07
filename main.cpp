/*
 * main.cpp
 *
 *  Created on: 24 Feb 2020
 *      Author: Merlijn Warps  & Sandra ter Maat
 */

#include <regex>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>


#include "JobShop.h"

int main(int argc, char **argv)
{
	char *filename;
	if (argc >= 2)
	{
		filename = argv[1];
	}
	else
	{
		return 1;
	}
	std::ifstream file(filename, std::ios::binary);
	if (file.fail())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		return 1;
	}

	JobShop jobShop;
	jobShop.readFile(file);

	while (jobShop.checkIfJobsAreDone() == false)
	{
		jobShop.checkMachines();
		jobShop.nextEvent();
	}
	jobShop.print();
	return 0;
}

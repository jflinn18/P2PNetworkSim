#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Network.h"
#include "Nodes.h"
#include "Simulation.h"

int main() {
	srand(time(NULL));
	Simulation simulation;
	
	string resp;
	int dataRedundancy, netSize;

	std::cout << "Which Simulation? (One or Two): ";
	std::cin >> resp;
	try {
		std::cout << "Size of network: ";
		std::cin >> netSize;
		std::cout << "Data Redundancy Rate: ";
		std::cin >> dataRedundancy;
	}
	catch (exception ex) {
		std::cout << "Incorrect type" << std::endl;
		exit(0);
	}

	if (resp == "One" || resp == "one")
		simulation.simOne(netSize, dataRedundancy);
	else if (resp == "Two" || resp == "two")
		simulation.simTwo(netSize, dataRedundancy);
	else {
		std::cout << "Incorrect Simulation.";
		exit(0);
	}


	//simulation.simOne(100, 10);
	//simulation.simTwo(5000, 1);
}
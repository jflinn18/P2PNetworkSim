#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Network.h"

class Simulation {
private: 
	Network n;
	int initNetSize;
	int redundancyRate;

public: 

	Simulation() {}

	// runs one of the simulations given a choice. 
	void runSimualtion() {}

	// simOne will be running a simulation that takes a fixed diconnection probability 
	//   and fixed data redundancy rate and shows the relationship
	void simOne() {}

	// simTwo will be using a random disconnection probability and a fixed data redundancy rate
	//   and shows the relationship.
	void simTwo() {
	// run simOne passing in a random disconnection probability
	}


};

#endif
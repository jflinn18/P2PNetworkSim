#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Network.h"
#include <stdlib.h>
#include <time.h>


class Simulation {
private: 
	Network n1;
	Network n2;
	int initNetSize;
	int redundancyRate;

public: 

	Simulation(int initNetSize, int redundancyRate) {
		if (initNetSize < redundancyRate) {
			cout << "Redundancy Rate must be <= to initNetSize given the defn of Set\n";
			exit(0);
		}
		this->initNetSize = initNetSize;
		this->redundancyRate = redundancyRate;
		srand(time(NULL));
		
	}

	// runs one of the simulations given a choice. 
	void runSimualtion() {}

	void checkDups(Network net) {
		map<unsigned int, int>::iterator it;
		Node *n = NULL;
		set<unsigned int> *localDatabase;

		// Makes sure that the max redundancy is met.
		for (it = globalDatabase.begin(); it != globalDatabase.end(); it++) {
			while (it->second != redundancyRate) {
				n = net.getNode(rand() % (net.getNodeMapSize() - 1));
				localDatabase = n->getNodeDatabase();
				if (localDatabase->find(it->first) == localDatabase->end()) {
					localDatabase->insert(it->first);
					it->second++;
				}// endif
			}//endwhile
		}//endfor
	}


	// simOne will be running a simulation that takes a fixed diconnection probability 
	//   and fixed data redundancy rate and shows the relationship
	//	 we assume that only sleeping nodes will connect to the network after the simulation has begun, no new nodes
	void simOne() {
		clearGlobalDatabase();

		// setup the initial network
		for (int i = 0; i < initNetSize; i++) {
			n1.addNode();
		}
		checkDups(n1);

		// two for-loops:
		//		outer loop --> redundancy rate changing
		//		inner loop --> disconnection rate increasing
		//		
		
	}

	// simTwo will be using a random disconnection probability and a fixed data redundancy rate
	//   and shows the relationship.
	void simTwo() {
		clearGlobalDatabase();
	// run simOne passing in a random disconnection probability

	// clock tick simulation
	//     nodes can disconnect or reconnect or do nothing at each clock tick. 
	//     nodes cannot reconnect if there are no nodes in the sleeping nodes vector.
	//	   Any node can disconnect or reconnect at any clock tick. (this will be done in the network)
	//     Only one node can run a query at each clock tick (???)
		int clock = 0;
		int endTime = 0;

		bool queried;
		int numDisconnect = 0;
		int numReconnect = 0;

		std::cout << "How long do you want to run the simulation? ";
		std::cin >> endTime;

		// simulation clock
		for (; clock < endTime; clock++) {
			queried = false;

			numDisconnect = rand() % n1.getNodeMapSize();
			numReconnect = rand() % n1.getSleepingNodeSize();

		}


	}


};

#endif
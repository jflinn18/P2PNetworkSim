#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Network.h"
#include <stdlib.h>
#include <time.h>


class Simulation {
public: 

	Simulation() {}

	// simOne will be running a simulation that takes a fixed diconnection probability 
	//   and fixed data redundancy rate and shows the relationship
	//	 we assume that only sleeping nodes will connect to the network after the simulation has begun, no new nodes
	void simOne(int initNetSize, int redundancyRateCap) {

		//error checking...
		if (redundancyRateCap > initNetSize) { cout << "too big..." << endl; redundancyRateCap = initNetSize; }

		vector<pair<int, double>> successRates;
		Network n1;

		int redundancy = 1;
		while (redundancy <= redundancyRateCap) {
			cout << "redundancy rate: " << redundancy << endl;
			clearGlobalDatabase();

			// setup the initial network
			for (int i = 0; i < initNetSize; i++) {
				n1.addNode();
			}

			n1.checkDups(redundancy);

			map<int, Node*>::iterator nodeIt;			//iterator to go through the nodemap
			map<unsigned int, int>::iterator globalIt;	//iterator to go through the global database
			int randProbability;						//probability a node will disconnect from the network

														//probability of each node in the network disconnecting
			for (int disconnection = 0; disconnection < 100; disconnection += 5) {
				//get network nodes
				map<int, Node*> myNodeMap = n1.getNodes();
				for (nodeIt = myNodeMap.begin(); nodeIt != myNodeMap.end(); nodeIt++) {
					randProbability = rand() % 101; //get random number between 0 and 100
													//disconnect node from network if it fits in the probability
					if (randProbability <= disconnection) { n1.disconnectNode(nodeIt->first); }
				}

				int successfulQueries = 0;
				//query distributed database for all items in the global database --> get a percentage of accurate query execution
				for (globalIt = globalDatabase.begin(); globalIt != globalDatabase.end(); globalIt++) {
					if (n1.queryDistributedDatabase(globalIt->first)) { successfulQueries++; }
				}

				//add success rate to vector
				successRates.push_back(pair<int, double>(disconnection, static_cast<double>(successfulQueries) / static_cast<double>(globalDatabase.size())));
				//n1.reconnectAllNodes(); //puts all sleeping nodes back into the nodeMap
			}
			cout << "Simulation 1 Success rates:" << endl;
			for (int i = 0; i < successRates.size(); i++) {
				cout << successRates[i].first << ": " << successRates[i].second << endl;
			}
			cout << "end simulation 1 success rates." << endl;
			successRates.clear();
			redundancy++;
		}
	}

	// simTwo will be using a random disconnection probability and a fixed data redundancy rate
	//   and shows the relationship.
	void simTwo() {
		clearGlobalDatabase();
	// run simOne passing in a random disconnection probability


		Network n1;
		Network n2;
		int initNetSize;
		int redundancyRateCap;


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
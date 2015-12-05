#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Network.h"
#include <stdlib.h>
#include <time.h>
#include <iterator>

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

		int redundancy = 1;
		while (redundancy <= redundancyRateCap) {

			cout << "redundancy rate: " << redundancy << endl;
			clearGlobalDatabase();
			Network n1;
			// setup the initial network
			for (int i = 0; i < initNetSize; i++) { n1.addNode(); } //make the network the size we want
			n1.checkDups(redundancy);								//make redundancy rate accurate

			map<int, Node*>::iterator nodeIt;			//iterator to go through the nodemap
			map<unsigned int, int>::iterator globalIt;	//iterator to go through the global database
			int randProbability;						//probability a node will disconnect from the network

														//probability of each node in the network disconnecting
			for (int disconnection = 0; disconnection < 100; disconnection += 5) {

				if (disconnection >= 90 && redundancy == 10) {
					std::cout << std::endl;
				}

				//get network nodes
				map<int, Node*> *myNodeMap = n1.getNodes();
				std::map<int, Node*>::iterator it = myNodeMap->begin();
				while (it != myNodeMap->end()) {
					randProbability = rand() % 101; //get random number between 0 and 100
					if (randProbability < disconnection) {
						std::map<int, Node*>::iterator toErase = it;
						++it;
						//disconnect node from network if it fits in the probability
						n1.disconnectNode(toErase->first);
					}
					else {
						++it;
					}
				}

				int successfulQueries = 0;
				//query distributed database for all items in the global database --> get a percentage of accurate query execution
				for (globalIt = globalDatabase.begin(); globalIt != globalDatabase.end(); globalIt++) {
					if (n1.queryDistributedDatabase(globalIt->first)) { successfulQueries++; }
				}

				//add success rate to vector
				successRates.push_back(pair<int, double>(disconnection, static_cast<double>(successfulQueries) / static_cast<double>(globalDatabase.size())));

				n1.reconnectAllNodes(); //empty sleeping nodes because it's a pointer
			}
			cout << "Simulation 1 Success rates:" << endl;
			cout << "RR Disc SucsRate\n";
			for (int i = 0; i < successRates.size(); i++) {
				cout << '{ ' << redundancy << ', ' << successRates[i].first << ", " << successRates[i].second << '},' << endl;
			}
			cout << "end simulation 1 success rates." << endl;
			successRates.clear();
			redundancy++;
		}
	}

	// simTwo will be using a random disconnection probability and a fixed data redundancy rate
	//   and shows the relationship.
	void simTwo(int initNetSize, int redundancyRate) {
		clearGlobalDatabase();
		Network n1;

		// setup the initial network
		for (int i = 0; i < initNetSize; i++) { 
			n1.addNode(); 
		} //make the network the size we want
		n1.checkDups(redundancyRate);							//make redundancy rate accurate

		// clock tick simulation
		//     nodes can disconnect or reconnect or do nothing at each clock tick. 
		//     nodes cannot reconnect if there are no nodes in the sleeping nodes vector.
		//	   Any node can disconnect or reconnect at any clock tick. (this will be done in the network)
		//     Only one node can run a query at each clock tick (???)

		int clock = 0;
		int endTime = 0;

		int probDisconnect = 0;
		int checkProbDisconnect = 0;
		int probReconnect = 0;
		int checkProbReconnect = 0;

		unsigned int data = 0;            // This is the data that is being queried for
		int dataSize = 0;                 // This is the randomness of data to query for
		int querySuccesses = 0;

		std::cout << "How many clock ticks? ";
		std::cin >> endTime;

		std::map<int, Node*>::iterator it;
		std::map<int, Node*> *nodeMap;

		// simulation clock
		for (; clock < endTime; clock++) {
			
			nodeMap = n1.getNodes();

			//flag all of the nodes that should be reconnected
			for (int i = 0; i < n1.getSleepingNodeSize(); i++) {
				probReconnect = rand() % 101;
				checkProbReconnect = rand() % 101;
				if (checkProbReconnect <= probReconnect) { n1.getSleepingNode(i)->setRDFlag(true); } //flag that notifies if the node should disconnect
			}

			//flag all of the nodes that should be disconnected
			for (it = nodeMap->begin(); it != nodeMap->end(); it++) {
				probDisconnect = rand() % 101;
				checkProbDisconnect = rand() % 101;
				if (checkProbDisconnect <= probDisconnect) { it->second->setRDFlag(true); }
			}
			//TODO: actually reconnect nodes that have the flag set
			//	randomly disconnect nodes from nodeMap

			//reconnects the flagged nodes
			int size = n1.getSleepingNodeSize();
			for (int i = 0; i < size; i++) {
				if (n1.getSleepingNode(i)->getRDFlag()) {
					n1.reconnectNode(i);
					i--;
					size--;
				}
			}

			//disconnects the flagged nodes
			it = nodeMap->begin();
			while (it != nodeMap->end()) {
				if (it->second->getRDFlag()) {
					std::map<int, Node*>::iterator toErase = it;
					++it;
					n1.disconnectNode(toErase->first);
				}
				else {
					++it;
				}
			}

			dataSize = rand() % globalDatabase.size();
			std::map<unsigned int, int>::iterator itGlobal;

			itGlobal = globalDatabase.begin();
			for (int i = 0; i < dataSize; i++) {
				itGlobal++;
			}

			data = itGlobal->first;
			if (n1.queryDistributedDatabase(data)) {
				querySuccesses++;
			}
				
		} // end for 'clock'

		std::cout << "Stats: " << (double)querySuccesses / (double)endTime << std::endl;   // endTime is the number of queries that we ran.
	}


};

#endif
#ifndef __NODES_H__
#define __NODES_H__

#include <iostream>
#include <map>
#include <set>
#include <iterator>
#include <random>
#include <time.h>

using namespace std;

map<unsigned int, int> globalDatabase;
int maxRedundancy = 1;

class Node{

private:
	int nodeID;
	set<unsigned int> database;

public:
	Node(int nodeID) { 
		this->nodeID = nodeID; //assigns name to node

		srand(time(NULL));
		int max = 20; //max size of the local database in the node
		int min = 5;  //min size of the local database in the node
		int databaseSize = rand() % (max - min + 1) + min; //the randomly generated size of the local database in the node
		int toAdd;	  //the random numbers that will be added to the local database
		// Filling the simulated database
		for (int i = 1; i <= databaseSize; i++) {
			toAdd = i*rand() % 10000;
			if (globalDatabase[toAdd]) {
				//if the number isn't unique, check if the global database has already met the max redundancy
				if (globalDatabase[toAdd] < maxRedundancy) {
					//if the number isn't in the local database
					if (database.find(toAdd) != database.end())
						//add the number to the local database
						database.insert(toAdd);
					else i--; //if the number is already in the database, decrement
				}
				globalDatabase[toAdd]++;
			}
			else {
				//if the number isn't in the global database, add it
				globalDatabase.insert(pair<unsigned int, int>(toAdd, 1));
				database.insert(toAdd);
			}
		}
	}
	
	int getNodeID() { return nodeID; }
};

#endif

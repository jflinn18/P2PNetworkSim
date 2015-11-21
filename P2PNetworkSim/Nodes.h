#ifndef __NODES_H__
#define __NODES_H__

#include <iostream>
#include <map>
#include <set>
#include <iterator>
#include <stdlib.h>

using namespace std;

map<unsigned int, int> globalDatabase;
int maxRedundancy = 1;

void clearGlobalDatabase() {
	globalDatabase.clear();
}

class Node{

private:
	int nodeID;
	set<unsigned int> database;

public:
	
	Node(int nodeID) { 
		this->nodeID = nodeID; //assigns name to node

		int max = 20; //max size of the local database in the node
		int min = 5;  //min size of the local database in the node
		int databaseSize = rand() % (max - min + 1) + min; //the randomly generated size of the local database in the node
		int toAdd;	  //the random numbers that will be added to the local database
		// Filling the simulated database
		for (int i = 1; i <= databaseSize; i++) {
			toAdd = i*rand() % 10000;
			if (globalDatabase.find(toAdd) == globalDatabase.end()) {
				//if the number isn't in the global database, add it
				globalDatabase.insert(pair<unsigned int, int>(toAdd, 1));
				database.insert(toAdd);
			}
		}
	}
	
	int getNodeID() { return nodeID; }
	set<unsigned int>* getNodeDatabase() { return &database; }

	void showLocalDatabase() {
		set<unsigned int>::iterator it;
		for (it = database.begin(); it != database.end(); it++) {
			cout << *it << endl;
		}
	}
};

#endif

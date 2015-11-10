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
		this->nodeID = nodeID;

		srand(time(NULL));
		int max = 20;
		int min = 5;
		int databaseSize = rand() % (max - min + 1) + min;
		int toAdd;
		for (int i = 1; i <= databaseSize; i++) {
			toAdd = i*rand() % 10000;
			if (globalDatabase[toAdd]) {
				if (globalDatabase[toAdd] < maxRedundancy) {
					if (database.find(toAdd) != database.end())
						database.insert(toAdd);
					else i--;
				}
				globalDatabase[toAdd]++;
			}
			else {
				globalDatabase.insert(pair<unsigned int, int>(toAdd, 1));
				database.insert(toAdd);
			}
		}
	}
	
	int getNodeID() { return nodeID; }
};

#endif

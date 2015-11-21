#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include "Nodes.h"


using namespace std;

class Network {
private: 
	map<int, Node*> nodeMap;
	vector<Node*> sleepingNodes;
	

public: 
	Network() {}

	// Deletes all of the node pointers in the network
	~Network() {
		for (map<int, Node*>::iterator it = nodeMap.begin(); it != nodeMap.end(); it++) { delete it->second; }
		for (int i = 0; i < sleepingNodes.size(); i++) { delete sleepingNodes[i]; }
	}

	// add a node to the network
	void addNode() {
		int name = nodeMap.size(); // the next node is the current size of the map
		Node *n = new Node(name);
		nodeMap.insert(pair<int, Node*>(name, n));
	}

	// "disconnects" a node from the simulated p2p network
	// Moves the disconnected node to a vector of sleeping nodes. (They may reconnect later in the simulation)
	void disconnectNode(int nameID) {
		if (nodeMap[nameID]) {  // checks to make sure the node is in the network. 
			sleepingNodes.push_back(nodeMap[nameID]);
			nodeMap.erase(nameID);
		}
		else
			cout << "Sorry. Node is not in the map.\n"; // handles the situation where the node is not in the network. 
	}

	// "reconnects" a node by moving it from the sleepingNodes to the nodeMap
	void reconnectNode() {
		if (sleepingNodes.size() != 0) {
			int randNode = rand() % sleepingNodes.size();
			
			nodeMap.insert(pair<int, Node*>(sleepingNodes[randNode]->getNodeID(), sleepingNodes[randNode]));

			// make sure that this is erasing the index that is being used above
			sleepingNodes.erase(sleepingNodes.begin() + randNode);
		}
		else
			std::cout << "No nodes in sleepingNodes\n";
	}

	void reconnectAllNodes() {
		for (int i = sleepingNodes.size() - 1; i > 0; i--) {
			nodeMap.insert(pair<int, Node*>(sleepingNodes[i]->getNodeID(), sleepingNodes[i]));
			sleepingNodes.pop_back(); //remove the node from the sleeping nodes vector
		}
	}

	bool queryDistributedDatabase(int data) {
		map<int, Node*>::iterator nodeIt;
		for (nodeIt = nodeMap.begin(); nodeIt != nodeMap.end(); nodeIt++) {
			set<unsigned int> *localDatabase = nodeIt->second->getNodeDatabase();
			
			if (localDatabase->find(data) != localDatabase->end()) {
				return true; //found the data!
			}
		}
		return false; //didn't find the data...
	}

	void printNodeMap() {
		map<int, Node*>::iterator it;
		for (it = nodeMap.begin(); it != nodeMap.end(); it++) {
			cout << "first: " << it->first << ", second: " << it->second << endl;
			cout << "local database:" << endl;
			it->second->showLocalDatabase();
		}
	}

	map<int, Node*> *getNodes() {return &nodeMap;}
	Node* getNode(int nodeID) {return nodeMap[nodeID];}
	int getNodeMapSize() { return nodeMap.size(); }
	int getSleepingNodeSize() { return sleepingNodes.size(); }
};

#endif



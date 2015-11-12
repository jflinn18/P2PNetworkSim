#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <map>
#include <vector>
#include "Nodes.h"


using namespace std;

class Network {
private: 
	map<int, Node*> nodeMap;
	vector<Node*> sleepingNodes;
	
public:

	Network() {	}

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

	// "removes" a node from the simulated p2p network
	// Moves the disconnected node to a vector of sleeping nodes. (They may reconnect later in the simulation)
	void removeNode(int nameID) {
		if (nodeMap[nameID]) {  // checks to make sure the node is in the network. 
			sleepingNodes.push_back(nodeMap[nameID]);
			nodeMap.erase(nameID);
		}
		else
			cout << "Sorry. Node is not in the map.\n"; // handles the situation where the node is not in the network. 
	}

	map<int, Node*> getNodes() {return nodeMap;}
	Node* getNode(int nodeID) {return nodeMap[nodeID];}

};

#endif



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

	~Network() {
		for (map<int, Node*>::iterator it = nodeMap.begin(); it != nodeMap.end(); it++) { delete it->second; }
		for (int i = 0; i < sleepingNodes.size(); i++) { delete sleepingNodes[i]; }
	}

	void addNode() {
		int name = nodeMap.size() + 1;
		Node *n = new Node(name);
		nodeMap.insert(pair<int, Node*>(name, n));
	}

	void removeNode(int nameID) {
		if (nodeMap[nameID]) {
			sleepingNodes.push_back(nodeMap[nameID]);
			nodeMap.erase(nameID);

		}
		else
			cout << "Sorry. Node is not in the map.\n";
	}

	map<int, Node*> getNodes() {return nodeMap;}
	Node* getNode(int nodeID) {return nodeMap[nodeID];}

	void runSim() {

	}
};

#endif



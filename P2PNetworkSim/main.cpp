#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Network.h"
#include "Nodes.h"
#include "Simulation.h"

int main() {
	srand(time(NULL));
	Simulation simulation;
	simulation.simOne(100, 10);
	//simulation.simTwo(5000, 1);
}
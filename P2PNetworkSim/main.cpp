#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Network.h"
#include "Nodes.h"
#include "Simulation.h"

int main() {
	srand(time(NULL));
	Simulation simulation;
	simulation.simOne(3, 2);
}
#include <iostream>
#include <stdio.h>
#include "HamiltonCycle.h"
int HamiltonCycle::Vertex::nameCounter = 0;
int main(int argc, char** argv) {
	std::cout << "Have " << argc << " arguments:" << std::endl;
	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}
	
	HamiltonCycle root = HamiltonCycle();



	while (1);
}

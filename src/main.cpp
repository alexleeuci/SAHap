#include <iostream>
#include <fstream>
#include <random>
#include "Chromosome.hpp"
#include "InputReader.hpp"
#include "Genome.hpp"

//#include <utility>
//#include "Read.hpp"
//#include "DNAChar.hpp"

using namespace SAHap;
using namespace std;

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		std::cout << "Usage: " << argv[0] << " [reads]" << endl;
		return 0;
	}

	ifstream file;
	file.open(argv[1]);

	Genome g(file, 1000, 2);
	g.sim_ann(1, 0.00001, 0.9, 10);
	
}


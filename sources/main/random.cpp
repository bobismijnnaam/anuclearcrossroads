// File: random.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-03-22
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <ctime>
#include <random>

// Private

int rand(int max) {
	static std::mt19937 prng{static_cast<unsigned int>(std::time(nullptr))};
	std::uniform_int_distribution<> dist{0, max - 1};

	return dist(prng);
}

// File: functions.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-04-18
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <cctype>

// Private
#include "main/functions.hpp"
#include "nnb/log/log.hpp"

json jsonFromFile(std::string file) {
	auto vec = nnb::readLines(file);
	std::string str = "";
	for (auto line : vec) {
		str += line;
	}

	return json::parse(str);
}

bool isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

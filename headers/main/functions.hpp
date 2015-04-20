// File: functions.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-04-18
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// Public
#include <string>

// Private
#include "main/json.hpp"
#include "nnb/utils/StringHelpers.hpp"

using json = nlohmann::json;

json jsonFromFile(std::string file);
bool isNumber(const std::string& s);

#endif

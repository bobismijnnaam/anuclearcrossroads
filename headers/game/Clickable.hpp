// File: Clickable.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-04-18
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

// Public
#include <vector>
#include <string>

// Private

struct Clickable {
	Clickable(int x_ = 0, int y_ = 0, int w_ = 0, int h_ = 0);

	void setBounds(int x_, int y_, int w_, int h_);
	bool contains(int px, int py);

	int x, y, w, h;
	std::vector<std::string> actions;
	std::string condition;
	std::vector<std::string> elseActions;
} ;

#endif

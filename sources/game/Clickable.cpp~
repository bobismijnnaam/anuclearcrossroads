// File: Clickable.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-04-18
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "game/Clickable.hpp"

Clickable::Clickable(int x_, int y_, int w_, int h_) :
x{x_},
y{y_},
w{w_},
h{h_} {
}

void Clickable::setBounds(int x_, int y_, int w_, int h_) {
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

bool Clickable::contains(int px, int py) {
	if (px >= x && px < x + w && py >= y && py < y + h) {
		return true;
	}

	return false;
}

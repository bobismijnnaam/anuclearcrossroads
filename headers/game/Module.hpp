// File: Module.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-04-19
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef MODULE_HPP
#define MODULE_HPP

// Public
#include <string>

// Private
#include "nnb/graphics/Text.hpp"
#include "nnb/graphics/TextureContainer.hpp"

class Module {
public:
	virtual ~Module();

	virtual void render() const;
	virtual void logic();
	virtual void receive(std::string signal);
	virtual void enter(std::string view, int x, int y);
	virtual void leave();
} ;

class Screen : public Module {
public:
	Screen();
	~Screen();

	void render() const;
	void logic();
	void receive(std::string signal);
	void enter(std::string view, int x, int y);
	void leave();

private:
	std::string currView = "";
	int cX, cY;
	
	nnb::Text target;
	nnb::Text targetCaption;
	nnb::Text categoryCaption;
	nnb::Text category;

	nnb::TextureContainer screen;

	bool finalMode = false;
	int buzzTime = -1;
} ;

#endif

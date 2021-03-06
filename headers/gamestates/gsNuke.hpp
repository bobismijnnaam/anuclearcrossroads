// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSNUKE_HPP
#define GSNUKE_HPP

// Public
#include <SDL2/SDL.h>
#include <string>
#include <vector>

// Private
#include "nnb/states/SimpleGameState.hpp"
#include "nnb/graphics/Text.hpp"

class gsNuke : public nnb::SimpleGameState<gsNuke> {
public:
	gsNuke();
	~gsNuke();

	void event(SDL_Event& e);
	void logic(float delta);
	void render() const;

	static constexpr auto id = "nuke";

private:
	nnb::TextureContainer dead;
	nnb::TextureContainer fader;
	int fadeStart;

	nnb::Text biasCap;
	nnb::Text actionCap;
	
} ;

#endif

// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSMAINMENU_HPP
#define GSMAINMENU_HPP

// Public
#include <SDL2/SDL.h>
#include <string>
#include <vector>

// Private
#include "nnb/states/SimpleGameState.hpp"
#include "nnb/graphics/Text.hpp"

class gsMainMenu : public nnb::SimpleGameState<gsMainMenu> {
public:
	gsMainMenu();
	~gsMainMenu();

	void event(SDL_Event& e);
	void logic(float delta);
	void render() const;

	static constexpr auto id = "main";

private:

	nnb::Text playButton;
	nnb::Text titleText;
	
} ;

#endif

// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

// Private
#include "gamestates/gsMainMenu.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/constants.hpp"
#include "nnb/utils/SDL_Helpers.hpp"

gsMainMenu::gsMainMenu() {
	playButton = g_fm->getText("blogger.ttf", 50);
	playButton.setText("PLAY");
	playButton.setHAlign(nnb::HAlign::CENTER);
	playButton.setPosition(250, 300);

	titleText = g_fm->getText("blogger.ttf", 50);
	titleText.setText("A Nuclear Crossroads");
	titleText.setHAlign(nnb::HAlign::CENTER);
	titleText.setPosition(250, 100);
}

gsMainMenu::~gsMainMenu() {
}

void gsMainMenu::event(SDL_Event& e) {
	int x, y;
	SDL_Rect r;
	switch (e.type) {
		case SDL_QUIT:
			g_gm->exit();
			NNB_LOG << "Exit was requested";
			break;
		case SDL_MOUSEBUTTONUP:
			x = e.button.x;
			y = e.button.y;
			r = playButton.getBounds();
			if (nnb::pointInRect({x, y}, r)) {
				g_gm->setState("game");
			}
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				g_gm->exit();
			}
		default:
			break;
	}

}

void gsMainMenu::logic(float delta) {

}

void gsMainMenu::render() const {
	SDL_SetRenderDrawColor(g_renderer, 180, 180, 180, 255);
	SDL_RenderClear(g_renderer);

	playButton.render();
	titleText.render();
	
	SDL_RenderPresent(g_renderer);
}

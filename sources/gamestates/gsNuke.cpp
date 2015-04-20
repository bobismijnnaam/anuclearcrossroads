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
#include "gamestates/gsNuke.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/constants.hpp"
#include "nnb/utils/SDL_Helpers.hpp"

gsNuke::gsNuke() {
	g_tm->loadGroup("game");
	
	if (bias == "normal") {
		dead = g_tm->getTexture("game", "nuke_dead.png");
	} else {
		dead = g_tm->getTexture("game", "diedorthrew.png");
	}
	dead.setPosition(0, 0);
	fader = g_tm->getTexture("game", bias + ".png"); 
	fader.setPosition(0, 0);
	fader.setAlpha(0);
	fadeStart = SDL_GetTicks();

	biasCap = g_fm->getText("blogger.ttf", 30);
	biasCap.setText("This was the \"" + bias + "\" ending");
	biasCap.setHAlign(nnb::HAlign::CENTER);
	biasCap.setPosition(250, 300);

	actionCap = g_fm->getText("blogger.ttf", 30);
	actionCap.setText(action);
	actionCap.setHAlign(nnb::HAlign::CENTER);
	actionCap.setPosition(250, 400);

	if (bias == "bad") {
		actionCap.setText("You blew yourself up.");
	}

	if (bias == "good") {
		actionCap.setText("You destroyed the evil device.");
	}
}

gsNuke::~gsNuke() {
	g_tm->unloadGroup("game");
}

void gsNuke::event(SDL_Event& e) {
	switch (e.type) {
		case SDL_QUIT:
			g_gm->exit();
			NNB_LOG << "Exit was requested";
			break;
		case SDL_MOUSEBUTTONUP:
			NNB_LOG << "Mouse button was pressed at (" << e.button.x << "; " << e.button.y << ")";
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				g_gm->exit();
			}
		default:
			break;
	}

}

void gsNuke::logic(float delta) {

	NNB_DEBUG << action;

	if ((SDL_GetTicks() - fadeStart) < 3000) {
		fader.setAlpha((SDL_GetTicks() - fadeStart) / 3000.0 * 255);

		biasCap.setAlpha(0);
		actionCap.setAlpha(0);
	} else if ((SDL_GetTicks() - fadeStart) < 6000) {
		fader.setAlpha(255);
		biasCap.setAlpha(255);
		actionCap.setAlpha(255);
	} else {
		g_gm->setState("main");
	}
}

void gsNuke::render() const {
	SDL_SetRenderDrawColor(g_renderer, gb_1.r, gb_1.g, gb_1.b, 255);
	SDL_RenderClear(g_renderer);

	dead.render();

	fader.render();

	biasCap.render();
	actionCap.render();

	SDL_RenderPresent(g_renderer);
}

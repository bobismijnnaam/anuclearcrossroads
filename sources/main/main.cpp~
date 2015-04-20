// External includes
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Personal includes
#include "gamestates/gsMainMenu.hpp"
#include "gamestates/gsGame.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "nnb/states/GameStateMachine.hpp"
#include "nnb/resources/Settings.hpp"
#include "nnb/utils/unique_ptr.hpp"

int init();
int game();
int cleanup();

int main(int argc, char* args[]) {
	int errorCode = init();
	if (errorCode > 0) {
		NNB_ERROR << "An error occurred! Error code: " << errorCode;
		return errorCode;
	}

	game();

	cleanup();
	
	return 0;
}

/**
 * Initializes SDL, among others. Could be in a separate state but ah well.
 * @return Errorcode indicating which part of the initialization went wrong
 */
int init() {
	g_gf.giveSDL(true, false, true);
	g_gf.giveSDL_Image(true, true, false);
	g_gf.giveSDL_TTF();
	if (!g_gf.launch()) {
		NNB_ERROR << "An error occurred while initializing, message: " << g_gf.getError();
		return 1;
	}

	if (!g_sts.import("game")) {
		NNB_ERROR << "Game settings could not be imported. Is the \"game\" file missing in media\\settings?";
		NNB_ERROR << "(Because the game kinda needs it to run you know)";
		g_gf.land();
		return 3;
	}
	SCR_W = g_sts.getInt("scrW");
	SCR_H = g_sts.getInt("scrH");
	SCR_TITLE = g_sts.get("windowTitle");

	g_window = SDL_CreateWindow(SCR_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		NNB_ERROR << "Window could not be created. SDL error: " << SDL_GetError();
		g_gf.land();
		return 2;
	}

	g_windowSurface = SDL_GetWindowSurface(g_window);
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

	g_gm = make_unique<nnb::GameStateMachine>();

	g_tm = make_unique<nnb::TextureManager>(g_renderer);

	g_fm = make_unique<nnb::FontManager>(g_renderer);

	NNB_LOG << "Initialization complete";

	return 0;
}

int game() {
	// Set the current state to main
	g_gm->setState("main");
	g_gm->update();

	while (g_gm->getCurrentStateID() != nnb::GameStateMachine::STATE_EXIT) {
		g_gm->update();
	}

	return 0;
}

int cleanup() {
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	g_fm.release();
	g_gm.release();
	g_tm.release();

	g_gf.land();

	return 0;
}

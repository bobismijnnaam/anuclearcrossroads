// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>

// Private
#include "main/global.hpp"
#include "nnb/states/GameStateMachine.hpp"
#include "nnb/utils/GameFrame.hpp"
#include "nnb/resources/TextureManager.hpp"

SDL_Window *g_window = NULL;
SDL_Surface *g_windowSurface = NULL;
SDL_Renderer *g_renderer = NULL;

std::unique_ptr<nnb::GameStateMachine> g_gm(nullptr);
std::unique_ptr<nnb::FontManager> g_fm(nullptr);
std::unique_ptr<nnb::TextureManager> g_tm(nullptr);

nnb::GameFrame g_gf;
nnb::Settings g_sts;

int SCR_W = 0;
int SCR_H = 0;
std::string SCR_TITLE = "";

SDL_Color gb_1 = {230, 214, 156, 255};
SDL_Color gb_2 = {180, 165, 106, 255};
SDL_Color gb_3 = {123, 113, 98, 255};
SDL_Color gb_4 = {57, 56, 41, 255};

std::string action;
std::string bias;

int finalScore = 0;

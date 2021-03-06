// File: global.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>

// Private
#include "nnb/states/GameStateMachine.hpp"
#include "nnb/utils/GameFrame.hpp"
#include "nnb/resources/Settings.hpp"
#include "nnb/resources/FontManager.hpp"
#include "nnb/resources/TextureManager.hpp"

extern SDL_Window *g_window;
extern SDL_Surface *g_windowSurface;
extern SDL_Renderer *g_renderer;

extern std::unique_ptr<nnb::GameStateMachine> g_gm;
extern std::unique_ptr<nnb::FontManager> g_fm;
extern std::unique_ptr<nnb::TextureManager> g_tm;

extern nnb::GameFrame g_gf;
extern nnb::Settings g_sts;

extern int SCR_W;
extern int SCR_H;
extern std::string SCR_TITLE;

extern SDL_Color gb_1;
extern SDL_Color gb_2;
extern SDL_Color gb_3;
extern SDL_Color gb_4;

extern int finalScore;

extern std::string action;
extern std::string bias;

#endif

// File: gsGame.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSGAME_HPP
#define GSGAME_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <map>

// Private
#include "nnb/states/SimpleGameState.hpp"
#include "nnb/graphics/Text.hpp"
#include "main/json.hpp"
#include "game/Clickable.hpp"
#include "game/Module.hpp"

using json = nlohmann::json;

struct Item : Clickable {
	bool has = true;
	nnb::TextureContainer sprite;

	bool isSelected = false;
	void render() const;
} ;

extern std::vector<std::string> possibleDirections;
extern std::map<std::string, SDL_Rect> directionRects;

class gsGame : public nnb::SimpleGameState<gsGame> {
public:
	gsGame();
	~gsGame();
	void event(SDL_Event& e);
	void logic(float delta);
	void render() const;

	static constexpr auto id = "game";

private:
	void switchToView();
	void playMusic(std::string file);
	void playSound(std::string file);
	void doAction(std::string action);
	bool checkCondition(std::string condition);
	void say(std::string);

	void extractClickables(json clickables);
	void extractModifiers(json modifiers);

	Uint32 stateStart = 0;

	nnb::TextureContainer bg;
	std::map<std::string, std::string> directions;
	std::map<std::string, std::unique_ptr<Module>> modules;
	std::vector<Clickable> clickAreas;
	std::vector<nnb::TextureContainer> sprites;
	std::map<std::string, Item> items;
	std::vector<Module*> activeModules;
	json vars;
	std::map<std::string, Item> inventory;
	json view;
	std::string nextView = "";

	int transitionTime = -1;
	int transitionStart = -1;

	bool hasClicked = false;
	int mx, my;
	bool showExl = false;
	nnb::TextureContainer exl;
	bool hasMoved = false;
	int mmx, mmy;

	int nextItemX = 100;

	nnb::Text line1;
	nnb::Text line2;

} ;

#endif

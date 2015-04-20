// File: gsGame.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <SDL2/SDL.h>
#include <string>
#include <sstream>

// Private
#include "gamestates/gsGame.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "nnb/states/GameState.hpp"
#include "nnb/utils/unique_ptr.hpp"
#include "main/random.hpp"
#include "main/functions.hpp"
#include "game/Clickable.hpp"
#include "nnb/utils/StringHelpers.hpp"

std::vector<std::string> possibleDirections = {"top", "right", "bottom", "left"};
std::map<std::string, SDL_Rect> directionRects {{"top", {50, 0, 400, 50}}, {"right", {450, 50, 50, 450}}, {"bottom", {50, 500, 400, 50}}, {"left", {0, 50, 50, 450}}};

void Item::render() const {
	if (!has)
		return;

	SDL_Rect bounds = sprite.getBounds();
	if (isSelected) {
		SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(g_renderer, &bounds);
	}

	sprite.render();
}

gsGame::gsGame() {
	g_tm->loadGroup("views");
	g_tm->loadGroup("sprites");
	g_tm->loadGroup("game");

	vars["day"] = 1;
	//vars["day"] = 3;
	vars["nukes"] = 0;
	vars["skips"] = 0;
	vars["current_item"] = "none";
	vars["has_button"] = 0;

	nextView = "bedroom";
	switchToView();

	modules["screen"] = std::unique_ptr<Module>(new Screen());

	line1 = g_fm->getText("blogger.ttf", 30);
	line1.setPosition(0, 650);

	line2 = g_fm->getText("blogger.ttf", 30);
	line2.setPosition(0, 700);

	exl = g_tm->getTexture("sprites", "exclamation.png");
}

gsGame::~gsGame() {
	g_tm->unloadGroup("views");
	g_tm->unloadGroup("sprites");
	g_tm->unloadGroup("game");
}

void gsGame::event(SDL_Event& e) {
	switch (e.type) {
		case SDL_QUIT:
			g_gm->exit();
			break;
		case SDL_MOUSEBUTTONUP:
			mx = e.button.x;
			my = e.button.y;
			hasClicked = true;
			break;
		case SDL_MOUSEMOTION:
			mmx = e.motion.x;
			mmy = e.motion.y;
			hasMoved = true;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				g_gm->exit();
			}
		default:
			break;
	}
}

void gsGame::logic(float delta) {
	delta = 0;

	if (hasMoved) {
		showExl = false;
		exl.setPosition(mmx, mmy);

		for (auto directionPair : directions) {
			if (directionPair.second != "") {
				SDL_Rect bounds = directionRects[directionPair.first];
				if (nnb::pointInRect({mmx, mmy}, bounds)) {
					showExl = true;
				}
			}
		}

		for (auto& pair : items) {
			if (pair.second.contains(mmx, mmy)) {
				showExl = true;
			}
		}

		for (auto& pair : inventory) {
			if (pair.second.contains(mmx, mmy)) {
				showExl = true;
			}
		}

		for (auto& clickArea : clickAreas) {
			if (clickArea.contains(mmx, mmy)) {
				if (clickArea.condition.empty()) {
					showExl = true;
				} else if (checkCondition(clickArea.condition)) {
					showExl = true;
				} else {
					if (clickArea.elseActions.size() > 0) {	
						showExl = true;
					}
				}
			}
		}
	}

	if (hasClicked) {
		for (auto directionPair : directions) {
			if (directionPair.second != "" && directionPair.second != "turnmeon") {
				SDL_Rect bounds = directionRects[directionPair.first];
				if (nnb::pointInRect({mx, my}, bounds)) {
					nextView = directionPair.second;

					vars["current_item"] = "none";
					for (auto& pair : inventory) {
						pair.second.isSelected = false;
					}

					break;
				}
			}
		}

		std::string toRemove = "";
		for (auto& pair : items) {
			if (pair.second.contains(mx, my)) {
				inventory[pair.first] = pair.second;
				inventory[pair.first].sprite.setPosition(nextItemX, 560);
				inventory[pair.first].setBounds(nextItemX, 560, inventory[pair.first].sprite.getRenderWidth(), inventory[pair.first].sprite.getRenderHeight());
				toRemove = pair.first;
				nextItemX += 100;
				break;
			}
		}
		if (toRemove != "") {
			items.erase(toRemove);
		}

		for (auto& pair : inventory) {
			if (pair.second.contains(mx, my)) {
				pair.second.isSelected = true;
				vars["current_item"] = pair.first;
				for (auto& otherPair : inventory) {
					if (otherPair.first != pair.first) {
						otherPair.second.isSelected = false;
					}
				}
			}
		}

		NNB_DEBUG << vars["current_item"].get<std::string>();

		if (nextView == "") {
			bool usedCurrentItem = false;

			for (auto& clickArea : clickAreas) {
				if (clickArea.contains(mx, my)) {
					if (clickArea.condition.empty()) {
						for (auto action : clickArea.actions) {
							doAction(action);
						}
					} else {
						if (checkCondition(clickArea.condition)) {
							for (auto action : clickArea.actions) {
								doAction(action);
							}
						} else {
							for (auto action : clickArea.elseActions) {
								doAction(action);
							}
						}
					}
				
					// break; // TODO: Think some more about this
					
					usedCurrentItem = true;
				}
			}

			if (usedCurrentItem) {
				vars["current_item"] = "none";
				for (auto& pair : inventory) {
					pair.second.isSelected = false;
				}
			}
		}
		
		hasClicked = false;
		mx = 0;
		my = 0;
	}

	for (auto module : activeModules) {
		module->logic();
	}

	if (!nextView.empty()) {
		switchToView();
	}
}

void gsGame::render() const {
	SDL_SetRenderDrawColor(g_renderer, gb_1.r, gb_1.g, gb_1.b, 255);
	SDL_RenderClear(g_renderer);

	bg.render();

	for (auto module : activeModules) {
		module->render();
	}

	for (auto sprite : sprites) {
		sprite.render();
	}

	for (auto& pair : items) {
		pair.second.render();
	}

	SDL_Rect gui = {0, 550, 500, 200};
	SDL_RenderFillRect(g_renderer, &gui);

	line1.render();
	line2.render();

	for (auto& pair : inventory) {
		pair.second.render();
	}

	SDL_SetRenderDrawColor(g_renderer, 0, 170, 0, 60);
	for (auto dir : possibleDirections) {
		if (directions.at(dir) != "") {
			SDL_RenderFillRect(g_renderer, &directionRects[dir]);
		}
	}

	if (showExl) {
		exl.render();
	}

	SDL_RenderPresent(g_renderer);
}

void gsGame::playMusic(std::string file) {

}

void gsGame::playSound(std::string file) {

}

// "actions": ["transition 3000 carwork", "playsound drive.wav"]
// "onEnter": ["set $nukes 0", "set $skips 0"],
// "actions": ["signal nuke", "inc $nukes"]
// "actions": ["goto office"],
// "elseActions": ["say Just a few more"]
// inc $var
void gsGame::doAction(std::string action) {
	auto args = nnb::split(action, " ");
	if (args.size() == 0) {
		NNB_ERROR << "Empty condition!";
	} else if (args[0] == "playsound") {
		playSound(args[1]);
	} else if (args[0] == "set") {
		auto var = args[1].substr(1, args[1].size() - 1);
		if (isNumber(args[2])) {
			vars[var] = nnb::stoi(args[2]);
		} else {
			vars[var] = args[2];
		}
	} else if (args[0] == "signal") {
		std::string msg = args[1];
		for (size_t i = 2; i < args.size(); ++i) {
			msg += " " + args[i];
		}
		
		if (msg == "throwit") {
			NNB_DEBUG << "THROW IT";
			bias = "good";
			action = "You destroyed the evil device.";
			g_gm->setState("nuke");
		} else if (msg == "suicide") {
			NNB_DEBUG << "SUICIDE";
			bias = "bad";
			action = "You threw yourself to the ground";
			g_gm->setState("nuke");
		}

		for (auto& module : activeModules) {
			module->receive(msg);
		}
	} else if (args[0] == "goto") {
		nextView = args[1];
		transitionTime = -1;
	} else if (args[0] == "transition") {
		nextView = args[2];
		transitionTime = nnb::stoi(args[1]);
		transitionStart = SDL_GetTicks();
	} else if (args[0] == "say") {
		std::string msg = args[1];
		for (size_t i = 2; i < args.size(); ++i) {
			msg += " " + args[i];
		}
		
		auto lines = nnb::split(msg, "#");

		if (lines.size() == 1) {
			line1.setText(lines[0]);
			line2.setText("");
		} else if (lines.size() == 2) {
			line1.setText(nnb::trim(lines[0]));
			line2.setText(nnb::trim(lines[1]));
		}

		std::cout << msg << std::endl;
	} else if (args[0] == "item") {
		auto itemName = args[1].substr(0, args[1].size() - 4);
		inventory[itemName] = Item();
		inventory[itemName].sprite = g_tm->getTexture("sprites", args[1]);
		inventory[itemName].sprite.setPosition(nextItemX, 560);
		inventory[itemName].setBounds(nextItemX, 560, inventory[itemName].sprite.getRenderWidth(), inventory[itemName].sprite.getRenderHeight());
		nextItemX += 100;
	} else if (args[0] == "consume") {
		// inventory.erase(args[1]);
		inventory[args[1]].has = false;
	} else if (args[0] == "inc") {
		auto varName = args[1].substr(1, args[1].size());
		vars[varName] = vars[varName].get<int>() + 1;
	}
}

// "condition": "meq $nukes 5",
// "condition": "else",
// "condition": "eq $day 3",
bool gsGame::checkCondition(std::string condition) {
	auto args = nnb::split(condition, " ");
	if (args.size() == 0) {
		NNB_ERROR << "WUT";
	} else if (args[0] == "meq") {
		int val = nnb::stoi(args[2]);
		std::string varname = args[1].substr(1, args[1].size() - 1);
		int varvalue = vars[varname].get<int>();
		return varvalue >= val;
	} else if (args[0] == "eq") {
		int val = nnb::stoi(args[2]);
		std::string varname = args[1].substr(1, args[1].size() - 1);
		int varvalue = vars[varname].get<int>();
		return varvalue == val;
	} else if (args[0] == "le") {
		int val = nnb::stoi(args[2]);
		std::string varname = args[1].substr(1, args[1].size() - 1);
		int varvalue = vars[varname].get<int>();
		return varvalue < val;
	} else if (args[0] == "nis") {
		std::string varname = args[1].substr(1, args[1].size() - 1);
		auto varvalue = vars[varname].get<std::string>();
		return varvalue != args[2];
	} else if (args[0] == "is") {
		std::string varname = args[1].substr(1, args[1].size() - 1);
		auto varvalue = vars[varname].get<std::string>();
		return varvalue == args[2];
	} else if (args[0] == "else") {
		return true;
	}

	return false;
}

void gsGame::say(std::string msg) {
	NNB_DEBUG << msg;
}

// TODO: Check if clickables overlap and warn accordingly
void gsGame::switchToView() {
	for (auto& pair : directions) {
		pair.second = "";
	}
	clickAreas.clear();
	sprites.clear();
	items.clear();
	line1.setText("");
	line2.setText("");

	for (auto module : activeModules) {
		module->leave();
	}
	activeModules.clear();

	bg = g_tm->getTexture("game", "black.png");

	if (transitionStart != -1 && SDL_GetTicks() - transitionStart < transitionTime) {
		return;
	}

	if (view.find("onLeave") != view.end()) {
		for (auto action : view["onLeave"]) {
			doAction(action.get<std::string>());
		}
	}

	std::string file = "media/views/" + nextView + ".json";
	view = jsonFromFile(file);

	if (view.find("bg") != view.end()) {
		bg = g_tm->getTexture("views", view["bg"]);
	} else {
		bg = g_tm->getTexture("views", nextView + ".png");
	}

	for (auto dir : possibleDirections) {
		directions[dir] = "";
		if (view.find(dir) != view.end()) {
			directions[dir] = view[dir].get<std::string>();
		}
	}

	extractModifiers(view);

	if (view.find("triggers") != view.end()) {
		json triggers = view["triggers"];
		for (auto trigger : triggers) {
			if (checkCondition(trigger["condition"].get<std::string>())) {
				extractModifiers(trigger["modifiers"]);
				break;
			}
		}
	}

	// Make sure we don't change view again
	transitionStart = -1;
	transitionTime = -1;
	nextView = "";
}

void gsGame::extractModifiers(json modifiers) {
	if (modifiers.find("onEnter") != modifiers.end()) {
		for (auto action : modifiers["onEnter"]) {
			doAction(action.get<std::string>());
		}
	}

	if (modifiers.find("clickable") != modifiers.end()) {
		extractClickables(modifiers["clickable"]);
	}

	if (modifiers.find("music") != modifiers.end()) {
		playMusic(modifiers["music"].get<std::string>());
	}

	if (modifiers.find("sprites") != modifiers.end()) {
		for (auto sprite : modifiers["sprites"]) {
			auto spriteArgs = nnb::split(sprite.get<std::string>(), " ");
			sprites.push_back(g_tm->getTexture("sprites", spriteArgs[0]));
			sprites.back().setPosition(nnb::stoi(spriteArgs[1]), nnb::stoi(spriteArgs[2]));
		}	
	}

	if (modifiers.find("modules") != modifiers.end()) {
		for (auto module : modifiers["modules"]) {
			auto moduleArgs = nnb::split(module.get<std::string>(), " ");
			if (modules.find(moduleArgs[0]) != modules.end()) {
				activeModules.push_back(modules[moduleArgs[0]].get());
				activeModules.back()->enter(nextView, nnb::stoi(moduleArgs[1]), nnb::stoi(moduleArgs[2]));
			}
		}
	}
	if (modifiers.find("items") != modifiers.end()) {
		for (auto item : modifiers["items"]) {
			auto itemArgs = nnb::split(item.get<std::string>(), " ");
			auto name = itemArgs[0].substr(0, itemArgs[0].size() - 4);

			if (inventory.find(name) == inventory.end()) {
				int x = nnb::stoi(itemArgs[1]);
				int y = nnb::stoi(itemArgs[2]);

				items[name] = Item();
				items[name].sprite = g_tm->getTexture("sprites", itemArgs[0]);
				items[name].sprite.setPosition(x, y);
				items[name].setBounds(x, y, items[name].sprite.getRenderWidth(), items[name].sprite.getRenderHeight());
			}
		}
	}
}

void gsGame::extractClickables(json clickables) {
	for (auto clickable : clickables) {
		json area = clickable["area"];
		Clickable clickArea;

		if (area.is_array()) {
			clickArea.setBounds(area[0], area[1], area[2], area[3]);
		} else if (area.is_string()) {
			SDL_Rect bounds = directionRects[area.get<std::string>()];
			clickArea.setBounds(bounds.x, bounds.y, bounds.w, bounds.h);
			directions[area.get<std::string>()] = "turnmeon";
		} else {
			NNB_ERROR << "\"" << area << "\" is not a string nor an array!";
		}

		if (clickable.find("condition") != clickable.end()) {
			clickArea.condition = clickable["condition"].get<std::string>();
		}

		if (clickable.find("actions") != clickable.end()) {
			clickArea.actions = clickable["actions"].get<std::vector<std::string>>();
		}

		if (clickable.find("elseActions") != clickable.end()) {
			clickArea.elseActions = clickable["elseActions"].get<std::vector<std::string>>();
		}

		clickAreas.push_back(clickArea);
	}
}

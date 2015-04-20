// File: Module.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-04-19
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "game/Module.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "main/random.hpp"

///////////////////////
// Module base class //
///////////////////////

Module::~Module() {}

void Module::render() const {}

void Module::logic() {}

void Module::receive(std::string signal) {}

void Module::enter(std::string view, int x, int y) {}

void Module::leave() {}

///////////////////
// Screen Module //
///////////////////

std::vector<std::tuple<std::string, std::string>> targets = {
	std::tuple<std::string, std::string> {"School", "Riverbank High"},
	std::tuple<std::string, std::string> {"School", "Easton High" },
	std::tuple<std::string, std::string> {"School", "Ashton High"},
	std::tuple<std::string, std::string> {"School", "Arrowsmith High"},
	std::tuple<std::string, std::string> {"School", "Northvale High"},
	std::tuple<std::string, std::string> {"School", "Northdale High"},
	std::tuple<std::string, std::string> {"School", "Eppingswood High"},
	std::tuple<std::string, std::string> {"School", "Riverdell High"},
	std::tuple<std::string, std::string> {"School", "Cedarwood High"},
	std::tuple<std::string, std::string> {"School", "Colby High"},
	std::tuple<std::string, std::string> {"Country", "Amestris"},
	std::tuple<std::string, std::string> {"Country", "Rastosjka"},
	std::tuple<std::string, std::string> {"Country", "Babar's Kingdom"},
	std::tuple<std::string, std::string> {"Country", "Borduria",},
	std::tuple<std::string, std::string> {"Country", "Country of the Blind"},
	std::tuple<std::string, std::string> {"Country", "Ecotopia"},
	std::tuple<std::string, std::string> {"Country", "Freedonia"},
	std::tuple<std::string, std::string> {"Country", "Graustark"},
	std::tuple<std::string, std::string> {"Country", "Ivalice"},
	std::tuple<std::string, std::string> {"Country", "Krakozhia"},
	std::tuple<std::string, std::string> {"Country", "Lilliput"},
	std::tuple<std::string, std::string> {"Country", "Qumar"},
	std::tuple<std::string, std::string> {"Country", "Samavia"},
	std::tuple<std::string, std::string> {"Country", "Spensonia"},
	std::tuple<std::string, std::string> {"Country", "Trans-Carpathia"},
	std::tuple<std::string, std::string> {"Country", "Val Verde"},
	std::tuple<std::string, std::string> {"Country", "Wakanda"},
	std::tuple<std::string, std::string> {"Country", "Yellow Empire"},
	std::tuple<std::string, std::string> {"Country", "Zubrowka"},
	std::tuple<std::string, std::string> {"City", "Metropolis"},
	std::tuple<std::string, std::string> {"City", "Zion"},
	std::tuple<std::string, std::string> {"City", "Mayberry"},
	std::tuple<std::string, std::string> {"City", "Springfield"},
	std::tuple<std::string, std::string> {"City", "Hogsmeade"},
	std::tuple<std::string, std::string> {"City", "Los Santos"},
	std::tuple<std::string, std::string> {"City", "Vice City"},
	std::tuple<std::string, std::string> {"City", "Atlantis"},
	std::tuple<std::string, std::string> {"City", "Waterdeep"},
	std::tuple<std::string, std::string> {"Person", "Joella Talarico"},
	std::tuple<std::string, std::string> {"Person", "Elton Bradstreet"},
	std::tuple<std::string, std::string> {"Person", "Karyl Geiser"},
	std::tuple<std::string, std::string> {"Person", "Aletha Prasad"},
	std::tuple<std::string, std::string> {"Person", "Vada Coletti"},
	std::tuple<std::string, std::string> {"Person", "Sandi Grego"},
	std::tuple<std::string, std::string> {"Person", "Erinn Mcgahan"},
	std::tuple<std::string, std::string> {"Person", "Brynn Weingartner"},
	std::tuple<std::string, std::string> {"Person", "Arlen Vanhorn"},
	std::tuple<std::string, std::string> {"Person", "Carlene Placencia"},
	std::tuple<std::string, std::string> {"Person", "Rosenda Tullis"},
	std::tuple<std::string, std::string> {"Person", "Malika Moser"},
	std::tuple<std::string, std::string> {"Person", "Gianna Foraker"},
	std::tuple<std::string, std::string> {"Person", "Hershel Harrill"},
	std::tuple<std::string, std::string> {"Person", "Petra Wellner"},
	std::tuple<std::string, std::string> {"Person", "Violette Speir"},
	std::tuple<std::string, std::string> {"Person", "Jaimie Marois"},
	std::tuple<std::string, std::string> {"Person", "Rochell Spratt"},
	std::tuple<std::string, std::string> {"Person", "Mara Sheets"},
	std::tuple<std::string, std::string> {"Person", "Eliseo Lewellen"},
	std::tuple<std::string, std::string> {"Person", "Jestine Birge"},
	std::tuple<std::string, std::string> {"Person", "Felixirklin  "},
	std::tuple<std::string, std::string> {"Person", "Ivey Garlitz"},
	std::tuple<std::string, std::string> {"Person", "Geneva Corrao"},
	std::tuple<std::string, std::string> {"Person", "Gilberto Linnell"},
	std::tuple<std::string, std::string> {"Person", "Nubia Parent"},
	std::tuple<std::string, std::string> {"Person", "Kara Atherton"},
	std::tuple<std::string, std::string> {"Person", "Lakiesha Villescas"},
	std::tuple<std::string, std::string> {"Person", "Kent Beltz"},
	std::tuple<std::string, std::string> {"Person", "Temeka Heckstall"},
	std::tuple<std::string, std::string> {"Person", "Clemmie Forward"},
	std::tuple<std::string, std::string> {"Person", "Bob Moises"},
	std::tuple<std::string, std::string> {"Person", "Debrah Liriano"},
	std::tuple<std::string, std::string> {"Person", "Garry Chenoweth"},
	std::tuple<std::string, std::string> {"Person", "Millicent Landry"},
	std::tuple<std::string, std::string> {"Person", "Adrian Lanctot"},
	std::tuple<std::string, std::string> {"Person", "Shamika Carlsen"},
	std::tuple<std::string, std::string> {"Person", "Hollie Ryan"},
	std::tuple<std::string, std::string> {"Person", "Jewell Salamanca"},
	std::tuple<std::string, std::string> {"Person", "Leif Stein"},
	std::tuple<std::string, std::string> {"Company", "Universo Realtors"},
	std::tuple<std::string, std::string> {"Company", "Incredible Universe"},
	std::tuple<std::string, std::string> {"Company", "Planet Profit"},
	std::tuple<std::string, std::string> {"Company", "The Happy Bear"},
	std::tuple<std::string, std::string> {"Company", "The Lawn Guru"},
	std::tuple<std::string, std::string> {"Company", "Almacs"},
	std::tuple<std::string, std::string> {"Company", "Yardbirds Homeenter"},
	std::tuple<std::string, std::string> {"Company", "National Record Mart"}
};

Screen::Screen() {
	targetCaption = g_fm->getText("deuperset.ttf", 20);
	targetCaption.setText("TARGET");
	targetCaption.setColor(255, 0, 0);
	targetCaption.setPosition(35, 80);

	target = g_fm->getText("deuperset.ttf", 20);
	target.setColor(255, 255, 255);
	target.setPosition(35, 80 + targetCaption.getHeight() + 5);

	categoryCaption = g_fm->getText("deuperset.ttf", 20);
	categoryCaption.setColor(255, 0, 0);
	categoryCaption.setText("CATEGORY");
	categoryCaption.setPosition(35, 150);

	category = g_fm->getText("deuperset.ttf", 20);
	category.setColor(255, 255, 255);
	category.setPosition(35, 150 + categoryCaption.getHeight() + 5);

	NNB_DEBUG << "Module Screen created";
}

Screen::~Screen() {

}

void Screen::render() const {
	screen.render();
	target.render();
	targetCaption.render();
	categoryCaption.render();
	category.render();
}

void Screen::logic() {
	if ((SDL_GetTicks() - buzzTime) < 300) {
		target.setAlpha(0);
		targetCaption.setAlpha(0);
		categoryCaption.setAlpha(0);
		category.setAlpha(0);

		screen = g_tm->getTexture("sprites", "screenNoise1.png");
	} else if ((SDL_GetTicks() - buzzTime) < 600) {
		screen = g_tm->getTexture("sprites", "screenNoise2.png");
	} else if ((SDL_GetTicks() - buzzTime) < 900) {
		screen = g_tm->getTexture("sprites", "screenNoise3.png");
	} else {
		target.setAlpha(255);
		targetCaption.setAlpha(255);
		categoryCaption.setAlpha(255);
		category.setAlpha(255);

		screen = g_tm->getTexture("sprites", "screen.png");
		buzzTime = -1;
	}

	screen.setPosition(10, 50);
}

void Screen::receive(std::string signal) {
	// caption.setText(currView + signal);
	NNB_DEBUG << "signal is:::::" << signal;
	if (signal == "suicide") {
		NNB_DEBUG << "SUICIDE";
	} else if (signal == "throwit") {
		NNB_DEBUG << "THREW IT ON THE GROUND";
	} else if (buzzTime == -1 && (signal == "nuke" || signal == "skip") && !finalMode) {
		auto p = targets[rand(targets.size())];
		category.setText(std::get<0>(p));
		target.setText(std::get<1>(p));
	} else if (buzzTime == -1 && (signal == "nuke" || signal == "skip") && finalMode) {
		NNB_DEBUG << "OMG LET'S PANIC";
		if (signal == "nuke") {
			// TODO: Trigger nuke
			NNB_DEBUG << "Game over";
			g_gm->setState("nuke");

			bias = "normal";
			action = "You blew yourself up.";
		} else {
			// TODO: Trigger screen flicker
			NNB_DEBUG << "Bzzzzt";
			buzzTime = SDL_GetTicks();
		}
	} else if (signal == "screen final") {
		finalMode = true;
		category.setText("RIOT");
		target.setText("Manhattan Group Plaza");
	}

	NNB_DEBUG << "Received \"" << signal << "\"";
}

void Screen::enter(std::string view, int x, int y) {
	currView = view;
	cX = x;
	cY = y;

	auto p = targets[rand(targets.size())];
	category.setText(std::get<0>(p));
	target.setText(std::get<1>(p));

	NNB_DEBUG << "Screen was entered";
}

void Screen::leave() {
	NNB_DEBUG << "Screen left";
}

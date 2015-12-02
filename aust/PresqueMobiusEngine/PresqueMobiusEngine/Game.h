#pragma once
#include "Engine.h"
#include "Button.h"
#include "MenuSystem.h"

#define WINDOW_TITLE "Kojima Gaiden"

enum gameState {
	mmenu,
	hmenu,
	omenu,
	cselect,
	gplay,
	pause,
	finish
};

class Game {
private:
	gameState curState;
	bool showFPS;
	renInfo tempInfo;
	textStruct fpsText;

	//menu stuff
	spriteStruct backGround;
	MenuSystem menu;
	bool play;
	void createMenu();
	void createOptions();
	void createHelp();

	//game setting
	bool _rensa;
	bool _magic;

	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
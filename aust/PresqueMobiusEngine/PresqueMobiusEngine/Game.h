#pragma once
#include "Engine.h"
#include "Button.h"
#include "MenuSystem.h"

#define WINDOW_TITLE "Kojima Gaiden"


class Game {
private:
	bool showFPS;
	renInfo tempInfo;
	textStruct fpsText;
	MenuSystem menu;

	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
#pragma once
#include "Engine.h"

#define WINDOW_TITLE "WEEEEEE"

class Game {
private:
	camera cam;


	imageAsset testImage;
	spriteStruct testSprite;
	renInfo testInfo;
	textStruct testText;
	modelAsset* testModel;
	lineStruct testLine;


	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
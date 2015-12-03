#pragma once
#include "Engine.h"
#include "Tetris.h"

#define WINDOW_TITLE "WEEEEEE"

class Game {
private:
	camera cam;


	Tetris tetristest;



	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
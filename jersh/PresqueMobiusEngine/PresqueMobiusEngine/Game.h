#pragma once
#include "Engine.h"
#include "TetrisGame.h"

#define WINDOW_TITLE "WEEEEEE"

class Game {
private:
	camera cam;


	TetrisGame tetris;



	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
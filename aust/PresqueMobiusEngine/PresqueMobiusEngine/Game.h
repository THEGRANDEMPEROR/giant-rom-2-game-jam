#pragma once
#include "Engine.h"
#include "Button.h"
#include "MenuSystem.h"

#define WINDOW_TITLE "Battle Tetris Solid 5: The Phantom Kojima"

enum gameState {
	mmenu,
	hmenu,
	omenu,
	cselect,
	gplay,
	pause,
	finish
};

struct CharacterInfo {
	std::string name;
	spriteStruct icon;
	spriteStruct selectBackground;
	spriteStruct victoryBackground;
	void (*abilities[4])();
};

class Game {
private:
	std::vector<CharacterInfo> charList;
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
	void createFinish();
	void startTetris();

	//char select
	bool p1Lock;
	bool p2Lock;
	int p1Select;
	int p2Select;
	textStruct p1Name;
	textStruct p2Name;
	D3DXMATRIX charTrans;

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
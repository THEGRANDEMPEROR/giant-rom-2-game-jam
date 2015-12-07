#pragma once
#include "Engine.h"
#include "Button.h"
#include "MenuSystem.h"
#include "TetrisGame.h"

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
	void (*abilities[4])(Player*,Player*);
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
	spriteStruct gamelogo;
	MenuSystem menu;
	bool play;
	void createMenu();
	void createOptions();
	void createHelp();
	void createFinish();
	void startTetris();

	//char select
	float startDelay;
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

	//tetris things
	TetrisGame tetris;
	int p1cont;
	int p2cont;

	//Sound stuff
	soundStruct click;
	soundStruct rollover;
	vector soundvec;

	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
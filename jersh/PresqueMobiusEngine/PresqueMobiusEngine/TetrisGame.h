#pragma once
#include "Tetris.h"
#include "Engine.h"


const int NUMPLAYERS = 2;




class Player {
private:
	int controller; // 0-3 gamepads. 4 keyboard. 
	Tetris tetris;
	// abilities

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
};


class TetrisGame {
private:
	Player players[NUMPLAYERS];
	bool running;
public:
	TetrisGame();
	~TetrisGame();
	void Init();
	void Update();
	void Draw();

};
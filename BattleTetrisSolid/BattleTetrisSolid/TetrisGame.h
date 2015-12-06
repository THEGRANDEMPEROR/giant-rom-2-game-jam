#pragma once
#include "Tetris.h"
#include "Engine.h"


const int NUMPLAYERS = 2;
const int MAGICCHANCE = 5;

const int TIMETOSPEEDUP = 15;
const int MAXSPEED = 9;
//const int Xqueueoffset = 





class Player {
private:
	int controller; // 0 keyboard. 1-4 gamepads. 
	int player;
	int magic;
	int maxMagic;
	float immune;
	float magicBlocked;
	float magicRunning;
	Tetris tetris;
	// abilities
	void (*abilities[4])(Player* ,Player*);
public:
	Player();
	~Player();
	void Init(int a_player);
	void Update(int a_speed);
	void Draw();
	void BindCont(int a_controller); // 0 keyboard. 1-4 gamepads.
	void useMagic(Player* otherPlayer);
	void Reset();
	bool needPiece();
	void setMagic(int magicLevel,void (*magicFunc)(Player*,Player*));
	int getMagic() {return magic;}
	void subMagic(int ammount);
	void setPiece(Tetrimino& piece);
	bool isImmune(){return immune > 0;}
	bool isBlocked(){return magicBlocked > 0;}
	bool isUsingMagic(){return magicRunning > 0;}
	//immune time is in seconds
	void setImmune(float immuneTime);
	void setUsingMagic(float magicTime);
	void setBlocked(float blockedTime);
	Tetris* getTetris(){return &tetris;}
};


class TetrisGame {
private:
	Player players[NUMPLAYERS];
	bool running;
	std::vector <Tetrimino> tetqueue; // TETQUEUENO
	bool magic;
	bool rensa;
	int speed;
	float speedtime;

	// sprites for tetqeueue // TETQUEUENO
	spriteStruct bluesprite;
	spriteStruct magicsprite;
	spriteStruct darkbluesprite;
	spriteStruct greensprite;
	spriteStruct greysprite;
	spriteStruct orangesprite;
	spriteStruct purplesprite;
	spriteStruct redsprite;
	spriteStruct yellowsprite;
	spriteStruct lockedMagicsprite;


	Tetrimino randomTet(); // TETQUEUENO returns a random tetrimino
	void DrawQueue(); // TETQUEUENO not finished
public:
	TetrisGame();
	~TetrisGame();
	void Init();
	void Update();
	void Draw();
	void BindPlayer(int a_player, int a_controller); // 0 keyboard. 1-4 gamepads.
	void Reset(bool a_magic, bool a_rensa);
	void setMagic(int player,int level,void (*func)(Player*,Player*));
};
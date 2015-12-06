#pragma once
#include "Tetris.h"
#include "Engine.h"


const int NUMPLAYERS = 2;
const int MAGICCHANCE = 5;

const int TIMETOSPEEDUP = 15;
const int MAXSPEED = 9;
const int MAXWINS = 2;
//const int Xqueueoffset = 

class TetrisGame;

enum PlayerEffect {
	noEffect,
	noRot,
	noDrop,
	ranRot,
	noMagic,
	attackImmune,
};

class Player {
private:
	TetrisGame* game;
	int controller; // 0 keyboard. 1-4 gamepads. 
	int player;
	int magic;
	int maxMagic;
	int effectLength;
	float magicRunning;
	Tetris tetris;
	PlayerEffect curEffect;
	// abilities
	void (*abilities[4])(Player* ,Player*);
public:
	Player();
	~Player();
	void setEffect(PlayerEffect effect, int length){curEffect = effect;effectLength = length;}
	void Init(int a_player);
	void setGame(TetrisGame* a_game){game = a_game;}
	TetrisGame* getGame();
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
	bool isImmune(){return curEffect == attackImmune;}
	bool isBlocked(){return curEffect == noMagic;}
	bool isUsingMagic(){return magicRunning > 0;}
	//
	void setUsingMagic(float magicTime);
	Tetris* getTetris(){return &tetris;}
	
	int LinesToSend();
	void setLinesToSend(int a_lines);
	void addGarbage(int a_lines);

	// returns true if they are about to solidify, and need some garbage lines.
	bool needGarbage();
	bool Living();
};


class TetrisGame {
private:
	Player players[NUMPLAYERS];
	// number of wins.
	int p1wins, p2wins;

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
	// cancels out each other's lines if both sides have linestosend. 2 and 1 becomes 1 and 0. 7 and 2 becomes 5 and 0
	void CancelOutLines();
public:
	TetrisGame();
	~TetrisGame();
	void Init();
	void Update();
	void Draw();
	void BindPlayer(int a_player, int a_controller); // 0 keyboard. 1-4 gamepads.

	void Reset(bool a_magic, bool a_rensa);
	void fillQueue(TetriminoType fill,bool hasMagic,int number);

	void Reset(bool a_magic, bool a_rensa, bool a_winsreset);

	void setMagic(int player,int level,void (*func)(Player*,Player*));
};
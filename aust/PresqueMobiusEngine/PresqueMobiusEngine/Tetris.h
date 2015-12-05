#pragma once
#include "Tetrimino.h"
#include "ResourceDefines.h"
#include "Engine.h"


const int FIELD_SIZE_X = 10; // the width of a standard tetris field
const int FIELD_SIZE_Y = 22; // the height of a standard tetris field. topmost 2 are hidden, where the new pieces get spawned.
							// Player loss on a block solidifying in those two spaces.
const int DEATHZONE = 2; // top two rows equals death if you solidify there.



const float dropspeed = 10.0f;
const float basespeed = 1.0f;
const float twospeed = 1.4f;
const float threespeed = 1.8f;
const float fourspeed = 2.2f;
const float timetogofastsideways = 0.25f; // The time it takes for it to quickly move sideways while holding either direction

const int xOffsetP1 = 128;
const int yOffsetP1 = 32;

const int xOffsetP2 = 768;
const int yOffsetP2 = 32;




enum spotstuff {
	EMPTY,
	BLOCK,
	NANO
};


class spot {
private:
	spotstuff stuff;		// can be empty or filled, possibly add ghost or falling
	pos position;			// x,y from the top down. top left corner is 0,0 bottom right corner should be 9,21
public:
	spot() { stuff = EMPTY; position = pos(0, 0); /*sprite*/ }
	spot(spotstuff a_stuff, pos a_position/*, sprite*/) {
		stuff = a_stuff;
		position = a_position;

	};
	spotstuff getStuff();
	pos getPos();
	void Init(spotstuff a_stuff, pos a_position);
	void setStuff(spotstuff a_stuff);
	// position should never change, so we don't need a set for it.
	// void Draw();
};


class Tetris {
private:
	spot field[FIELD_SIZE_X][FIELD_SIZE_Y];
	int linestosend;
	int numlines;
	int speed;
	float timeheld;
	bool iNeedATetrimino;
	Tetrimino curtet;
	spriteStruct bluesprite;
	spriteStruct magicsprite;
	spriteStruct darkbluesprite;
	spriteStruct greensprite;
	spriteStruct greysprite;
	spriteStruct orangesprite;
	spriteStruct purplesprite;
	spriteStruct redsprite;
	spriteStruct yellowsprite;


	void TryToMove(int a_x, float a_y);
	bool DoICollide(int a_x, float a_y);
	int checkAllLines();
	void removeLine(int a_line);
	void Rotate(bool clockwise); // true for clockwise, false for counterclockwise
	
public:
	Tetris();
	~Tetris();
	void Init();
	void Update(int a_controller);
	void Draw(int a_player);
	void Reset();
	void setPiece(Tetrimino& piece);

	bool needPiece();
	void Solidify();
	int LinesToSend();
};




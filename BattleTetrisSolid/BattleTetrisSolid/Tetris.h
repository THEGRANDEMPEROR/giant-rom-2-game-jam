#pragma once
#include "Tetrimino.h"
#include "ResourceDefines.h"
#include "Engine.h"


const int FIELD_SIZE_X = 10; // the width of a standard tetris field
const int FIELD_SIZE_Y = 22; // the height of a standard tetris field. topmost 2 are hidden, where the new pieces get spawned.
							// Player loss on a block solidifying in those two spaces.
const int DEATHZONE = 2; // top two rows equals death if you solidify there.



const float speedmultiplier = 0.3f;
const float timetogofastsideways = 0.25f; // The time it takes for it to quickly move sideways while holding either direction
const float timetoslide = 0.5f;
const float timetoslideholdingdown = 0.1f;

const int xOffsetP1 = 128;
const int yOffsetP1 = 32;

const int xOffsetP2 = 768;
const int yOffsetP2 = 32;

const int SAMECOLUMNGARBAGECHANCE = 2;



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
	int controller;
	float timeheld;
	float timesliding;
	bool iNeedATetrimino;
	bool needgarbage;
	bool alive;
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
	// for use after being pushed up. Deathzone should always be empty
	void ClearDeathZone();
	
	
	int magic;
	
public:
	Tetris();
	~Tetris();
	void Init();
	void Update(int a_speed);
	void Draw(int a_player);
	void Reset(int a_controller);
	void setPiece(Tetrimino& piece);
	void transformMagic();

	bool needPiece();
	bool needGarbage();
	void Solidify();
	int LinesToSend();
	void setLinesToSend(int a_lines);
	//gets the amount of magic to add to player
	int getMagic(){return magic;}
	//sets magic to 0
	void clearMagic(){magic = 0;}
	// adds garbage lines at the bottom
	void addGarbage(int a_garbage);
	// returns true if alive
	bool Living();
};




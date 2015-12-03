#pragma once
#include "ResourceDefines.h"
const int TETRIMINO_SIZE = 4;
const int NUM_TETRIMINO_TYPES = 7;
const int CENTER_TETRIMINO_BLOCK = 1;

enum TetriminoType {
	LINE,
	SQUARE,
	LPIECE,
	JPIECE,
	SPIECE,
	ZPIECE,
	TPIECE
};


struct pos {
	int x, y;
	pos() { x = 0; y = 0; }
	pos(int a_x, int a_y) {
		x = a_x;
		y = a_y;
	}
};


struct fallingpos { // same as pos but an int and a float, so it can be animated as it falls and has proper collision
	int x;
	float y;
	fallingpos() { x = 0; y = 0.0f; }
	fallingpos(int a_x, float a_y) {
		x = a_x;
		y = a_y;
	}
};


class Block {
private:
	bool magic;			// nano
	fallingpos position;// int x, float y
public:
	Block();
	~Block();
	void Init(fallingpos a_pos, bool a_magic);
	fallingpos getPos();
	bool getMagic();
	void setPos(fallingpos a_pos);
	void Move(int a_x, float a_y);
	void Move(int a_x, int a_y);
	void setMagic(bool a_magic);
};




class Tetrimino {
private:
	Block blocks[TETRIMINO_SIZE];
	TetriminoType type;
public:
	Tetrimino();
	~Tetrimino();
	Tetrimino(Tetrimino &a_tet);
	void Init(TetriminoType a_type, bool a_magic);
	// Hardcoded starting positions depending on TetriminoType, possibly change that
	// the magic block will always be Blocks[1] and should probably be rotated around.
	void Move(int a_x, float a_y);
	void Move(int a_x, int a_y);
	Block getBlock(int a_index);
	TetriminoType getType();
	void Snap(bool a_snap); // snaps to grid. true = positive AKA down. false = negative AKA up
	void SetBlockPos(int a_index, fallingpos a_pos);
};


// MAGIC BLOCK SPOT
// 
// MAGIC = 0
// REGULAR = X
// 
// LINE
// X0XX
// 
// SQUARE
// X0
// XX
// 
// L
// X
// 0
// XX
// 
// J
//  X
//  0
// XX
// 
// S
//  0X
// XX
// 
// Z
// X0
//  XX
// 
// T
//  X 
// X0X




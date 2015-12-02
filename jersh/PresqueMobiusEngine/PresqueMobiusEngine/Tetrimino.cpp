#pragma once
#include "Tetrimino.h"


Block::Block() {
	magic = false;
	position.x = 0;
	position.y = 0.0f;
}


Block::~Block() {

}


void Block::Init(fallingpos a_pos, bool a_magic) {
	position.x = a_pos.x;
	position.y = a_pos.y;
	magic = a_magic;
}


fallingpos Block::getPos() {
	return position;
}


bool Block::getMagic() {
	return magic;
}


void Block::setPos(fallingpos a_pos) {
	position.x = a_pos.x;
	position.y = a_pos.y;
}


void Block::Move(int a_x, float a_y) {
	position.x += a_x;
	position.y += a_y;
}


void Block::Move(int a_x, int a_y) {
	position.x += a_x;
	position.y += a_y;
}


void Block::setMagic(bool a_magic) {
	magic = a_magic;
}




Tetrimino::Tetrimino() {
	Init(LINE, false);
}


Tetrimino::~Tetrimino() {

}


void Tetrimino::Init(TetriminoType a_type, bool a_magic) {
	if (a_type == LINE) {
		blocks[0].Init(fallingpos(3, 1.0f), false);
		blocks[1].Init(fallingpos(4, 1.0f), false);
		blocks[2].Init(fallingpos(5, 1.0f), false);
		blocks[3].Init(fallingpos(6, 1.0f), false);
	}
	else if (a_type == SQUARE) {
		blocks[0].Init(fallingpos(4, 0.0f), false);
		blocks[1].Init(fallingpos(5, 0.0f), false);
		blocks[2].Init(fallingpos(5, 1.0f), false);
		blocks[3].Init(fallingpos(4, 1.0f), false);
	}
	else if (a_type == LPIECE) {
		blocks[0].Init(fallingpos(3, 1.0f), false);
		blocks[1].Init(fallingpos(4, 1.0f), false);
		blocks[2].Init(fallingpos(5, 1.0f), false);
		blocks[3].Init(fallingpos(5, 0.0f), false);
	}
	else if (a_type == JPIECE) {
		blocks[0].Init(fallingpos(3, 0.0f), false);
		blocks[1].Init(fallingpos(4, 0.0f), false);
		blocks[2].Init(fallingpos(5, 0.0f), false);
		blocks[3].Init(fallingpos(5, 1.0f), false);
	}
	else if (a_type == SPIECE) {
		blocks[0].Init(fallingpos(5, 0.0f), false);
		blocks[1].Init(fallingpos(4, 0.0f), false);
		blocks[2].Init(fallingpos(4, 1.0f), false);
		blocks[3].Init(fallingpos(3, 1.0f), false);
	}
	else if (a_type == ZPIECE) {
		blocks[0].Init(fallingpos(3, 0.0f), false);
		blocks[1].Init(fallingpos(4, 0.0f), false);
		blocks[2].Init(fallingpos(4, 1.0f), false);
		blocks[3].Init(fallingpos(5, 1.0f), false);
	}
	else if (a_type == TPIECE) {
		blocks[0].Init(fallingpos(3, 1.0f), false);
		blocks[1].Init(fallingpos(4, 1.0f), false);
		blocks[2].Init(fallingpos(5, 1.0f), false);
		blocks[3].Init(fallingpos(4, 0.0f), false);
	}
	if (a_magic)
		blocks[1].setMagic(a_magic);
}

void Tetrimino::Move(int a_x, float a_y) {
	for (int i = 0; i < TETRIMINO_SIZE; ++i) {
		blocks[i].Move(a_x, a_y);
	}
}


void Tetrimino::Move(int a_x, int a_y) {
	for (int i = 0; i < TETRIMINO_SIZE; ++i) {
		blocks[i].Move(a_x, a_y);
	}
}


Block Tetrimino::getBlock(int a_index) {
	return blocks[a_index];
}


TetriminoType Tetrimino::getType() {
	return type;
}



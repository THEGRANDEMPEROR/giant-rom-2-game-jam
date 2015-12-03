#pragma once
#include "Tetris.h"
#include "InputSystem.h"
#include <math.h>


spotstuff spot::getStuff() {
	return stuff;
}


pos spot::getPos() {
	return position;
}


void spot::Init(spotstuff a_stuff, pos a_position) {
	setStuff(a_stuff);
	position.x = a_position.x;
	position.y = a_position.y;
}


void spot::setStuff(spotstuff a_stuff) {
	stuff = a_stuff;
}


Tetris::Tetris() {

}


Tetris::~Tetris() {

}


void Tetris::Init() {
	// Initialize the solidified block sprite
	solidsprite.image = (imageAsset*)Engine::instance()->getResource("element_blue_square.png", image)->resource;
	solidsprite.rec.top = 0;
	solidsprite.rec.left = 0;
	solidsprite.rec.right = solidsprite.image->texInfo.Width;
	solidsprite.rec.bottom = solidsprite.image->texInfo.Height;
	solidsprite.color = 0xFFFFFFFF;
	solidsprite.center = D3DXVECTOR3(solidsprite.image->texInfo.Width / 2.0f, solidsprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the magic sprite
	magicsprite.image = (imageAsset*)Engine::instance()->getResource("element_yellow_square.png", image)->resource;
	magicsprite.rec.top = 0;
	magicsprite.rec.left = 0;
	magicsprite.rec.right = magicsprite.image->texInfo.Width;
	magicsprite.rec.bottom = magicsprite.image->texInfo.Height;
	magicsprite.color = 0xFFFFFFFF;
	magicsprite.center = D3DXVECTOR3(magicsprite.image->texInfo.Width / 2.0f, magicsprite.image->texInfo.Height / 2.0f, 0);

	for (int y = 0; y < FIELD_SIZE_Y; ++y) {
		for (int x = 0; x < FIELD_SIZE_X; ++x) {
			field[x][y].Init(EMPTY, pos(x, y));
		}
	}// initialize the field to be empty

	// test stuff
	//field[9][6].setStuff(BLOCK);
	//field[9][5].setStuff(BLOCK);
	//field[9][4].setStuff(BLOCK);
	//field[8][2].setStuff(BLOCK);
	//field[8][3].setStuff(NANO);


	//field[5][21].setStuff(BLOCK);
	//field[4][13].setStuff(BLOCK);
	//field[3][13].setStuff(BLOCK);
	//field[6][12].setStuff(BLOCK);

	// end of test stuff

	Engine::instance()->bind(pad1_RIGHT, "Player 1 Right DPAD");
	Engine::instance()->bind(pad1_UP, "Player 1 Up DPAD");
	Engine::instance()->bind(pad1_LEFT, "Player 1 Left DPAD");
	Engine::instance()->bind(pad1_DOWN, "Player 1 Down DPAD");
	Engine::instance()->bind(pad1_A, "Player 1 A");
	Engine::instance()->bind(pad1_B, "Player 1 B");
	Engine::instance()->bind(pad1_X, "Player 1 X");
	Engine::instance()->bind(pad1_Y, "Player 1 Y");
	Engine::instance()->bind(pad1_START, "Player 1 Start");
	Engine::instance()->bind(pad1_BACK, "Player 1 Back");



	numlines = 0;
	linestosend = 0; // initialize lines
	speed = 1;
	lasttime = 0;

	curtet.Init(LINE, false);




}


void Tetris::Update() {
	//int random = 0;
	//int random1 = 0;
	//if (Engine::instance()->getBind("Player 1 A")) {
	//	random = rand() % FIELD_SIZE_X;
	//	random1 = rand() % FIELD_SIZE_Y;
	//	field[random][random1].setStuff(BLOCK);
	//}



	if (Engine::instance()->getBind("Player 1 Down DPAD")) {
		TryToMove(0, 1);
	}
	if (Engine::instance()->getBind("Player 1 Right DPAD")) {
		TryToMove(1, 0);
	}
	if (Engine::instance()->getBind("Player 1 Left DPAD")) {
		TryToMove(-1, 0);
	}
	if (Engine::instance()->getBind("Player 1 A")) {
		Rotate(true);
	}
	if (Engine::instance()->getBind("Player 1 B")) {
		Rotate(false);
	}
	TryToMove(0, Engine::instance()->dt());
}


void Tetris::Draw() {
	D3DXMATRIX translation, scaling;

	renInfo tempinfo;
	tempinfo.type = screenSprite;
	tempinfo.asset = &solidsprite; // set it to solid sprite, just in case.

	// Draw the whole field of solidified blocks.
	// Add offsets later

	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		for (int y = 0; y < FIELD_SIZE_Y; ++y) {	// for each spot in the field,
			if (field[x][y].getStuff() != EMPTY) {	// if the spot ISN'T empty
				if (field[x][y].getStuff() == BLOCK) {
					tempinfo.type = screenSprite;
					tempinfo.asset = &solidsprite;

					// Matrix transformation
					D3DXMatrixIdentity(&translation);
					D3DXMatrixIdentity(&scaling);
					D3DXMatrixIdentity(&tempinfo.matrix);


					D3DXMatrixTranslation(&translation, (solidsprite.rec.right*x), (solidsprite.rec.bottom*y), 0.0f);
					D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
					D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);



					Engine::instance()->addRender(tempinfo);
				}
				else if (field[x][y].getStuff() == NANO) {
					tempinfo.type = screenSprite;
					tempinfo.asset = &magicsprite;

					// Matrix transformation
					D3DXMatrixIdentity(&translation);
					D3DXMatrixIdentity(&scaling);
					D3DXMatrixIdentity(&tempinfo.matrix);


					D3DXMatrixTranslation(&translation, (magicsprite.rec.right*x), (magicsprite.rec.bottom*y), 0.0f);
					D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
					D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);

					Engine::instance()->addRender(tempinfo);
				}

			}
		}
	}

	for (int i = 0; i < TETRIMINO_SIZE; ++i) {
		if (!curtet.getBlock(i).getMagic()) {
			tempinfo.type = screenSprite;
			tempinfo.asset = &solidsprite;

			// Matrix transformation
			D3DXMatrixIdentity(&translation);
			D3DXMatrixIdentity(&scaling);
			D3DXMatrixIdentity(&tempinfo.matrix);


			D3DXMatrixTranslation(&translation, (solidsprite.rec.right*curtet.getBlock(i).getPos().x), (solidsprite.rec.bottom*curtet.getBlock(i).getPos().y), 0.0f);
			D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
			D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);

			Engine::instance()->addRender(tempinfo);




		}
		else {
			tempinfo.type = screenSprite;
			tempinfo.asset = &magicsprite;

			// Matrix transformation
			D3DXMatrixIdentity(&translation);
			D3DXMatrixIdentity(&scaling);
			D3DXMatrixIdentity(&tempinfo.matrix);


			D3DXMatrixTranslation(&translation, (magicsprite.rec.right*curtet.getBlock(i).getPos().x), (magicsprite.rec.bottom*curtet.getBlock(i).getPos().y), 0.0f);
			D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
			D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);

			Engine::instance()->addRender(tempinfo);
		}

	}




}


bool Tetris::DoICollide(int a_x, float a_y) {
	fallingpos temppos;
	for (int i = 0; i < TETRIMINO_SIZE; ++i) {
		temppos.x = curtet.getBlock(i).getPos().x + a_x;
		temppos.y = curtet.getBlock(i).getPos().y + a_y;
		if (temppos.x < 0 || temppos.x >= FIELD_SIZE_X || temppos.y < 0.0f || temppos.y > FIELD_SIZE_Y - 1) { // if you're trying to move out of the level
			return true;
		}
		for (int y = 0; y < FIELD_SIZE_Y; ++y) {	// for each y,
			if (temppos.y - y < 1.0f && temppos.y - y > -1.0f) {				// if that y is within 1.0f of the current position,
				if (field[temppos.x][y].getStuff() != EMPTY) // then check collision with that space
					return true;
			}
		}

		//if (a_y != 0.0f) {
		//	for (int y = 0; y < FIELD_SIZE_Y; ++y) {	// for each y,
		//		if (temppos.y - y < 1.0f) {				// if that y is within 1.0f of the current position,
		//			if (field[temppos.x][y].getStuff() != EMPTY) // then check collision with that space
		//				return true;
		//		}
		//	}
		//}
	}
	return false;
}


void Tetris::TryToMove(int a_x, float a_y) {
	if (a_x != 0) { // if you're moving to the right or left,
		if (!DoICollide(a_x, a_y)) { // if you don't collide, move
			curtet.Move(a_x, a_y);

		}
	}
	if (a_y != 0.0f) { // if you're moving up or down, (always down)
		if (!DoICollide(a_x, a_y)) { // if you don't collide, move
			curtet.Move(a_x, a_y);

		}
		else {	// if you do collide, snap to grid.
			if (a_y > 0.0f)
				curtet.Snap(true);
			else
				curtet.Snap(false);

			Solidify(randomTet());
		}
	}
}


Tetrimino Tetris::randomTet() {
	int random = rand() % NUM_TETRIMINO_TYPES; // chance to be each type
	int random2 = rand() % 5; // chance to be magic
	bool magic = false;
	Tetrimino tet;
	if (random2 == 0)
		magic = true;
	if (random == 0)
		tet.Init(LINE, magic);
	else if (random == 1)
		tet.Init(SQUARE, magic);
	else if (random == 2)
		tet.Init(LPIECE, magic);
	else if (random == 3)
		tet.Init(JPIECE, magic);
	else if (random == 4)
		tet.Init(SPIECE, magic);
	else if (random == 5)
		tet.Init(ZPIECE, magic);
	else if (random == 6)
		tet.Init(TPIECE, magic);


	return tet;


}


void Tetris::Solidify(Tetrimino a_tet) {
	int tempx = 0, tempy = 0;
	for (int i = 0; i < TETRIMINO_SIZE; ++i) { // for each block in curtet,
		tempx = curtet.getBlock(i).getPos().x; // save the position of the block, so we don't have to get it again
		tempy = curtet.getBlock(i).getPos().y; // float to int, which is kinda bad but w/e man

		if (curtet.getBlock(i).getMagic())
			field[tempx][tempy].setStuff(NANO);
		else
			field[tempx][tempy].setStuff(BLOCK);
	}

	curtet = a_tet;
	linestosend += checkAllLines();
}


int Tetris::checkAllLines() {
	int lowestline = 0; // probably don't need this
	int numlines = 0;
	bool tempbool = true;

	for (int y = 0; y < FIELD_SIZE_Y; ++y) { // each row
		tempbool = true;									// reset tembool at each row
		for (int x = 0; x < FIELD_SIZE_X && tempbool; ++x) { // each column, as long as you don't find an empty space
			if (field[x][y].getStuff() == EMPTY)			// if there's an empty space
				tempbool = false;							// change tempbool to false

		}
		if (tempbool) {										// If you made it through the whole row without an empty space,
			removeLine(y);									// remove that line, moving everything above it down, CHANGE THIS FOR RENSA MODE
			++numlines;										// and increment numlines
			lowestline = y;									// and set the lowestline to y (important for rensa, i think.)
		}
	}

	// put rensa drop here, using lowestline, for now nothing RENSA RENSA RENSA


	return numlines;

}


void Tetris::removeLine(int a_line) {
	// GOING TO NEED TO CHANGE THIS FOR RENSA MODE.

	for (int y = a_line; y > 0; --y) { // for each row, starting from a_line and going up(negative), but not doing row 0 cause there's nothing above there
		for (int x = 0; x < FIELD_SIZE_X; ++x) {// for each column in that row,
			field[x][y].setStuff(field[x][y - 1].getStuff());
		}
	}

	// then, set the top row to all empty, since it moves down and doesn't have anything above it.
	// in theory, the top row shouldn't have anything in it except in dire circumstances, 
	// since the top two rows are off screen and induce death when you end a block there.
	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		field[x][0].setStuff(EMPTY);
	}

}


void Tetris::Rotate(bool clockwise) {
	fallingpos temppos[TETRIMINO_SIZE];
	float roundingthing = curtet.getBlock(0).getPos().y; // save a y. This is used because of rounding problems.
	curtet.Snap(false); // snap it to the grid.
	roundingthing -= curtet.getBlock(0).getPos().y; // save the decimal after, basically
	for (int i = 0; i < TETRIMINO_SIZE; ++i) { // copy the current position to temppos
		temppos[i].x = curtet.getBlock(i).getPos().x;
		temppos[i].y = curtet.getBlock(i).getPos().y;
	}
	


	int xChange = 0;
	float yChange = 0.0f;
	for (int i = 0; i < TETRIMINO_SIZE; ++i) { // for each block in the tetrimino,
		if (i != CENTER_TETRIMINO_BLOCK) { // except the center block, which should stay still,
			xChange = temppos[CENTER_TETRIMINO_BLOCK].x - temppos[i].x;
			yChange = temppos[CENTER_TETRIMINO_BLOCK].y - temppos[i].y;

			curtet.SetBlockPos(i, fallingpos(temppos[CENTER_TETRIMINO_BLOCK].x + yChange, temppos[CENTER_TETRIMINO_BLOCK].y + xChange));
		}
	}

	xChange = 0;
	yChange = 0;
	for (int i = 0; i < TETRIMINO_SIZE; ++i) { // for each block,
		if (i != CENTER_TETRIMINO_BLOCK) {
			xChange = temppos[CENTER_TETRIMINO_BLOCK].x - curtet.getBlock(i).getPos().x;

			curtet.SetBlockPos(i, fallingpos(temppos[CENTER_TETRIMINO_BLOCK].x + xChange, curtet.getBlock(i).getPos().y));
		}
	}
	bool outside = DoICollide(0,0.0f);
	
	if (outside) { // change it back if it is outside
		for (int i = 0; i < TETRIMINO_SIZE; ++i) {
			curtet.SetBlockPos(i, fallingpos(temppos[i].x, temppos[i].y));
		}
	}

	curtet.Move(0, roundingthing);



}








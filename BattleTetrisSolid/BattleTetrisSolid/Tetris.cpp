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

//turns magic into normal blocks
void Tetris::transformMagic() {
	spot tempSpot;
	for(int x = 0; x < FIELD_SIZE_X; ++x) {
		for(int y = 0; y < FIELD_SIZE_Y; ++y) {
			if(field[x][y].getStuff() == NANO) {
				field[x][y].setStuff(BLOCK);
			}
		}
	}
}


void Tetris::Init() {
	// Initialize the blue sprite
	bluesprite.image = (imageAsset*)Engine::instance()->getResource("element_blue_square.png", image)->resource;
	bluesprite.rec.top = 0;
	bluesprite.rec.left = 0;
	bluesprite.rec.right = bluesprite.image->texInfo.Width;
	bluesprite.rec.bottom = bluesprite.image->texInfo.Height;
	bluesprite.color = 0xFFFFFFFF;
	bluesprite.center = D3DXVECTOR3(bluesprite.image->texInfo.Width / 2.0f, bluesprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the magic sprite
	magicsprite.image = (imageAsset*)Engine::instance()->getResource("element_bomb_square.png", 0x00FFFFFF)->resource;
	magicsprite.rec.top = 0;
	magicsprite.rec.left = 0;
	magicsprite.rec.right = magicsprite.image->texInfo.Width;
	magicsprite.rec.bottom = magicsprite.image->texInfo.Height;
	magicsprite.color = 0xFFFFFFFF;
	magicsprite.center = D3DXVECTOR3(magicsprite.image->texInfo.Width / 2.0f, magicsprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the dark blue sprite
	darkbluesprite.image = (imageAsset*)Engine::instance()->getResource("element_dark_blue_square.png", image)->resource;
	darkbluesprite.rec.top = 0;
	darkbluesprite.rec.left = 0;
	darkbluesprite.rec.right = darkbluesprite.image->texInfo.Width;
	darkbluesprite.rec.bottom = darkbluesprite.image->texInfo.Height;
	darkbluesprite.color = 0xFFFFFFFF;
	darkbluesprite.center = D3DXVECTOR3(darkbluesprite.image->texInfo.Width / 2.0f, darkbluesprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the green sprite
	greensprite.image = (imageAsset*)Engine::instance()->getResource("element_green_square.png", image)->resource;
	greensprite.rec.top = 0;
	greensprite.rec.left = 0;
	greensprite.rec.right = greensprite.image->texInfo.Width;
	greensprite.rec.bottom = greensprite.image->texInfo.Height;
	greensprite.color = 0xFFFFFFFF;
	greensprite.center = D3DXVECTOR3(greensprite.image->texInfo.Width / 2.0f, greensprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the grey sprite
	greysprite.image = (imageAsset*)Engine::instance()->getResource("element_grey_square.png", image)->resource;
	greysprite.rec.top = 0;
	greysprite.rec.left = 0;
	greysprite.rec.right = greysprite.image->texInfo.Width;
	greysprite.rec.bottom = greysprite.image->texInfo.Height;
	greysprite.color = 0xFFFFFFFF;
	greysprite.center = D3DXVECTOR3(greysprite.image->texInfo.Width / 2.0f, greysprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the orange sprite
	orangesprite.image = (imageAsset*)Engine::instance()->getResource("element_orange_square.png", image)->resource;
	orangesprite.rec.top = 0;
	orangesprite.rec.left = 0;
	orangesprite.rec.right = orangesprite.image->texInfo.Width;
	orangesprite.rec.bottom = orangesprite.image->texInfo.Height;
	orangesprite.color = 0xFFFFFFFF;
	orangesprite.center = D3DXVECTOR3(orangesprite.image->texInfo.Width / 2.0f, orangesprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the red sprite
	redsprite.image = (imageAsset*)Engine::instance()->getResource("element_red_square.png", image)->resource;
	redsprite.rec.top = 0;
	redsprite.rec.left = 0;
	redsprite.rec.right = redsprite.image->texInfo.Width;
	redsprite.rec.bottom = redsprite.image->texInfo.Height;
	redsprite.color = 0xFFFFFFFF;
	redsprite.center = D3DXVECTOR3(redsprite.image->texInfo.Width / 2.0f, redsprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the yellow sprite
	yellowsprite.image = (imageAsset*)Engine::instance()->getResource("element_yellow_square.png", image)->resource;
	yellowsprite.rec.top = 0;
	yellowsprite.rec.left = 0;
	yellowsprite.rec.right = yellowsprite.image->texInfo.Width;
	yellowsprite.rec.bottom = yellowsprite.image->texInfo.Height;
	yellowsprite.color = 0xFFFFFFFF;
	yellowsprite.center = D3DXVECTOR3(yellowsprite.image->texInfo.Width / 2.0f, yellowsprite.image->texInfo.Height / 2.0f, 0);

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



	numlines = 0;
	linestosend = 0; // initialize lines
	speed = 1;
	timeheld = 0.0f;
	iNeedATetrimino = true;

	curtet.Init(LINE, true);
	magic = 0;



}


void Tetris::Update(int a_controller, int a_speed) {
	//int random = 0;
	//int random1 = 0;
	//if (Engine::instance()->getBind("Player 1 A")) {
	//	random = rand() % FIELD_SIZE_X;
	//	random1 = rand() % FIELD_SIZE_Y;
	//	field[random][random1].setStuff(BLOCK);
	//}
	float tempYChange = 0.0f;
	if (a_controller == 0) { // gamepad 1
		Engine::instance()->setRepeat(0.05f);
		if (Engine::instance()->getFlags("Player 1 Down DPAD")&buttonFlags::_repeat) {
			tempYChange += 1.0f;
		}
		if (Engine::instance()->getFlags("Player 1 Right DPAD")&buttonFlags::_pushed) {
			TryToMove(1, 0);
		}
		if (Engine::instance()->getFlags("Player 1 Right DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Player 1 Right DPAD")&buttonFlags::_repeat) {
					TryToMove(1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Player 1 Right DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Player 1 Left DPAD")&buttonFlags::_pushed) {
			TryToMove(-1, 0);
		}
		if (Engine::instance()->getFlags("Player 1 Left DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Player 1 Left DPAD")&buttonFlags::_repeat) {
					TryToMove(-1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Player 1 Left DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Player 1 A")&buttonFlags::_pushed) {
			Rotate(true);
		}
		if (Engine::instance()->getFlags("Player 1 B")&buttonFlags::_pushed) {
			Rotate(false);
		}
		TryToMove(0, Engine::instance()->dt());
	}
	else if (a_controller == 1) { // gamepad 2
		Engine::instance()->setRepeat(0.05f);
		if (Engine::instance()->getFlags("Player 2 Down DPAD")&buttonFlags::_repeat) {
			tempYChange += 1.0f;
		}
		if (Engine::instance()->getFlags("Player 2 Right DPAD")&buttonFlags::_pushed) {
			TryToMove(1, 0);
		}
		if (Engine::instance()->getFlags("Player 2 Right DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Player 2 Right DPAD")&buttonFlags::_repeat) {
					TryToMove(1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Player 2 Right DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Player 2 Left DPAD")&buttonFlags::_pushed) {
			TryToMove(-1, 0);
		}
		if (Engine::instance()->getFlags("Player 2 Left DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Player 2 Left DPAD")&buttonFlags::_repeat) {
					TryToMove(-1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Player 2 Left DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Player 2 A")&buttonFlags::_pushed) {
			Rotate(true);
		}
		if (Engine::instance()->getFlags("Player 2 B")&buttonFlags::_pushed) {
			Rotate(false);
		}
	}
	tempYChange += (1.0f + (a_speed * speedmultiplier))*Engine::instance()->dt();
	TryToMove(0, tempYChange);
}


void Tetris::Draw(int a_player) {
	D3DXMATRIX translation, scaling;

	renInfo tempinfo;
	tempinfo.type = screenSprite;
	tempinfo.asset = &bluesprite; // set it to blue sprite, just in case.

	// Draw the whole field of solidified blocks.
	// Add offsets later

	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		for (int y = 0; y < FIELD_SIZE_Y; ++y) {	// for each spot in the field,
			if (field[x][y].getStuff() != EMPTY) {	// if the spot ISN'T empty
				if (field[x][y].getStuff() == BLOCK) {
					tempinfo.type = screenSprite;
					tempinfo.asset = &bluesprite;

					// Matrix transformation
					D3DXMatrixIdentity(&translation);
					D3DXMatrixIdentity(&scaling);
					D3DXMatrixIdentity(&tempinfo.matrix);

					if (a_player == 0) {
						D3DXMatrixTranslation(&translation, (bluesprite.rec.right*x + xOffsetP1), (bluesprite.rec.bottom*y + yOffsetP1), 0.0f);
					}
					else {
						D3DXMatrixTranslation(&translation, (bluesprite.rec.right*x + xOffsetP2), (bluesprite.rec.bottom*y + yOffsetP2), 0.0f);
					}
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

					if (a_player == 0) {
						D3DXMatrixTranslation(&translation, (magicsprite.rec.right*x+xOffsetP1), (magicsprite.rec.bottom*y+yOffsetP1), 0.0f);
					}
					else  {
						D3DXMatrixTranslation(&translation, (magicsprite.rec.right*x + xOffsetP2), (magicsprite.rec.bottom*y + yOffsetP2), 0.0f);
					}
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
			tempinfo.asset = &bluesprite;

			// Matrix transformation
			D3DXMatrixIdentity(&translation);
			D3DXMatrixIdentity(&scaling);
			D3DXMatrixIdentity(&tempinfo.matrix);

			if (a_player == 0) {
				D3DXMatrixTranslation(&translation, (bluesprite.rec.right*curtet.getBlock(i).getPos().x+xOffsetP1), (bluesprite.rec.bottom*curtet.getBlock(i).getPos().y+yOffsetP1), 0.0f);
			}
			else {
				D3DXMatrixTranslation(&translation, (bluesprite.rec.right*curtet.getBlock(i).getPos().x + xOffsetP2), (bluesprite.rec.bottom*curtet.getBlock(i).getPos().y + yOffsetP2), 0.0f);
			}
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

			if (a_player == 0) {
				D3DXMatrixTranslation(&translation, (magicsprite.rec.right*curtet.getBlock(i).getPos().x+xOffsetP1), (magicsprite.rec.bottom*curtet.getBlock(i).getPos().y+yOffsetP1), 0.0f);
			}
			else {
				D3DXMatrixTranslation(&translation, (magicsprite.rec.right*curtet.getBlock(i).getPos().x + xOffsetP2), (magicsprite.rec.bottom*curtet.getBlock(i).getPos().y + yOffsetP2), 0.0f);
			}
			D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
			D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);

			Engine::instance()->addRender(tempinfo);
		}

	}




}


void Tetris::Reset() {
	numlines = 0;
	speed = 1;
	linestosend = 0;
	magic = 0;
	//curtet = randomTet();
	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		for (int y = 0; y < FIELD_SIZE_Y; ++y) {
			field[x][y].setStuff(EMPTY);
		}
	}
	timeheld = 0.0f;
	iNeedATetrimino = true;
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
			if (temppos.y - y < 1.0f && temppos.y - y > -1.0f || curtet.getBlock(i).getPos().y - y < 1.0f && curtet.getBlock(i).getPos().y - y > -1.0f) {				// if that y is within 1.0f of the current position,
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
			if (a_y > 0.0f) {
				curtet.Snap(true);
				while(!DoICollide(0,1.0f)) {
					curtet.Move(0,1.0f);
				}
			}
			Solidify();
		}
	}
}


void Tetris::Solidify() {
	int tempx = 0, tempy = 0;
	for (int i = 0; i < TETRIMINO_SIZE; ++i) { // for each block in curtet,
		tempx = curtet.getBlock(i).getPos().x; // save the position of the block, so we don't have to get it again
		tempy = curtet.getBlock(i).getPos().y; // float to int, which is kinda bad but w/e man

		if (curtet.getBlock(i).getMagic())
			field[tempx][tempy].setStuff(NANO);
		else
			field[tempx][tempy].setStuff(BLOCK);
	}

	// tetrimino change used to be here
	linestosend += checkAllLines();
	iNeedATetrimino = true;
}


int Tetris::checkAllLines() {
	int lowestline = 0; // probably don't need this
	int numlines = 0;
	int tempMagic;
	bool tempbool = true;

	for (int y = 0; y < FIELD_SIZE_Y; ++y) { // each row
		tempbool = true;									// reset tembool at each row
		tempMagic = 0;										// reset count at each row
		for (int x = 0; x < FIELD_SIZE_X && tempbool; ++x) { // each column, as long as you don't find an empty space
			if (field[x][y].getStuff() == EMPTY) {			// if there's an empty space
				tempbool = false;							// change tempbool to false
			} else if(field[x][y].getStuff() == NANO) {		//count Nanos in the line
				++tempMagic;
			}
			
											

		}
		if (tempbool) {										// If you made it through the whole row without an empty space,
			removeLine(y);									// remove that line, moving everything above it down, CHANGE THIS FOR RENSA MODE
			++numlines;										// and increment numlines
			magic += tempMagic;								// and add magic cleared
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
			if (clockwise)
				curtet.SetBlockPos(i, fallingpos(temppos[CENTER_TETRIMINO_BLOCK].x - yChange, temppos[CENTER_TETRIMINO_BLOCK].y - xChange));
			else
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


int Tetris::LinesToSend() {
	return linestosend;
}


bool Tetris::needPiece() {
	return iNeedATetrimino;
}

void Tetris::setPiece(Tetrimino& piece) {
	curtet = piece;
	iNeedATetrimino = false;
}
#pragma once
#include "Tetris.h"
#include "TetrisGame.h"
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
	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		for (int y = 0; y < FIELD_SIZE_Y; ++y) {
			if (field[x][y].getStuff() == NANO) {
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
	// Initialize the purple sprite
	purplesprite.image = (imageAsset*)Engine::instance()->getResource("element_purple_square.png", image)->resource;
	purplesprite.rec.top = 0;
	purplesprite.rec.left = 0;
	purplesprite.rec.right = purplesprite.image->texInfo.Width;
	purplesprite.rec.bottom = purplesprite.image->texInfo.Height;
	purplesprite.color = 0xFFFFFFFF;
	purplesprite.center = D3DXVECTOR3(purplesprite.image->texInfo.Width / 2.0f, purplesprite.image->texInfo.Height / 2.0f, 0);
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
	timesliding = 0.0f;
	iNeedATetrimino = true;
	needgarbage = false;

	curtet.Init(LINE, true);
	magic = 0;
	alive = true;


}

TetriminoType Tetris::curType() {
	return curtet.getType();
}

bool Tetris::curTetMagic() {
	return curtet.isMagic();
}


void Tetris::Update(int a_speed, PlayerEffect curEffect) {

	//int random = 0;
	//int random1 = 0;
	//if (Engine::instance()->getBind("Player 1 A")) {
	//	random = rand() % FIELD_SIZE_X;
	//	random1 = rand() % FIELD_SIZE_Y;
	//	field[random][random1].setStuff(BLOCK);
	//}
	float tempYChange = 0.0f;
	if (controller == 0) {
		Engine::instance()->setRepeat(0.05f);
		if (Engine::instance()->getFlags("Key Down")&buttonFlags::_repeat&&curEffect != noDrop) {
			tempYChange += 1.0f;
		}
		if (Engine::instance()->getFlags("Key Right")&buttonFlags::_pushed) {
			TryToMove(1, 0);
		}
		if (Engine::instance()->getFlags("Key Right")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Key Right")&buttonFlags::_repeat) {
					TryToMove(1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Key Right")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Key Left")&buttonFlags::_pushed) {
			TryToMove(-1, 0);
		}
		if (Engine::instance()->getFlags("Key Left")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Key Left")&buttonFlags::_repeat) {
					TryToMove(-1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Key Left")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Key A")&buttonFlags::_pushed&&curEffect != noRot) {
			Rotate(true);
		}
		if (Engine::instance()->getFlags("Key B")&buttonFlags::_pushed&&curEffect != noRot) {
			Rotate(false);
		}
	}
	else if (controller == 1) { // gamepad 1
		Engine::instance()->setRepeat(0.05f);
		if (Engine::instance()->getFlags("Pad 1 Down DPAD")&buttonFlags::_repeat&&curEffect != noDrop) {
			tempYChange += 1.0f;
		}
		if (Engine::instance()->getFlags("Pad 1 Right DPAD")&buttonFlags::_pushed) {
			TryToMove(1, 0);
		}
		if (Engine::instance()->getFlags("Pad 1 Right DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Pad 1 Right DPAD")&buttonFlags::_repeat) {
					TryToMove(1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Pad 1 Right DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Pad 1 Left DPAD")&buttonFlags::_pushed) {
			TryToMove(-1, 0);
		}
		if (Engine::instance()->getFlags("Pad 1 Left DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Pad 1 Left DPAD")&buttonFlags::_repeat) {
					TryToMove(-1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Pad 1 Left DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Pad 1 A")&buttonFlags::_pushed&&curEffect != noRot) {
			Rotate(true);
		}
		if (Engine::instance()->getFlags("Pad 1 B")&buttonFlags::_pushed&&curEffect != noRot) {
			Rotate(false);
		}

	}
	else if (controller == 2) { // gamepad 2
		Engine::instance()->setRepeat(0.05f);
		if (Engine::instance()->getFlags("Pad 2 Down DPAD")&buttonFlags::_repeat&&curEffect != noDrop) {
			tempYChange += 1.0f;
		}
		if (Engine::instance()->getFlags("Pad 2 Right DPAD")&buttonFlags::_pushed) {
			TryToMove(1, 0);
		}
		if (Engine::instance()->getFlags("Pad 2 Right DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Pad 2 Right DPAD")&buttonFlags::_repeat) {
					TryToMove(1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Pad 2 Right DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Pad 2 Left DPAD")&buttonFlags::_pushed) {
			TryToMove(-1, 0);
		}
		if (Engine::instance()->getFlags("Pad 2 Left DPAD")&buttonFlags::_held) {
			timeheld += Engine::instance()->dt();
			if (timeheld >= timetogofastsideways) {
				if (Engine::instance()->getFlags("Pad 2 Left DPAD")&buttonFlags::_repeat) {
					TryToMove(-1, 0);
				}
			}
		}
		else if (Engine::instance()->getFlags("Pad 2 Left DPAD")&buttonFlags::_released)
			timeheld = 0;
		if (Engine::instance()->getFlags("Pad 2 A")&buttonFlags::_pushed&&curEffect != noRot) {
			Rotate(true);
		}
		if (Engine::instance()->getFlags("Pad 2 B")&buttonFlags::_pushed&&curEffect != noRot) {
			Rotate(false);
		}
	}
	//random rotation
	if(curEffect == ranRot) {
		if(rand()%10 == 0) {
			Rotate(rand()%2);
		}
	}
	tempYChange += (1.0f + (a_speed * speedmultiplier))*Engine::instance()->dt();
	TryToMove(0, tempYChange);
}


void Tetris::Draw(int a_player) {
	D3DXMATRIX translation, scaling;

	renInfo tempinfo;
	tempinfo.type = screenSprite;
	tempinfo.asset = &greensprite; // set it to blue sprite, just in case.

	// Draw the whole field of solidified blocks.
	// Add offsets later

	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		for (int y = 0; y < FIELD_SIZE_Y; ++y) {	// for each spot in the field,
			if (field[x][y].getStuff() != EMPTY) {	// if the spot ISN'T empty
				tempinfo.type = screenSprite;
				if (field[x][y].getStuff() == BLOCK) {
					tempinfo.asset = &bluesprite;
				}
				else
					tempinfo.asset = &magicsprite;
					// Matrix transformation
					D3DXMatrixIdentity(&translation);
					D3DXMatrixIdentity(&scaling);
					D3DXMatrixIdentity(&tempinfo.matrix);

					if (a_player == 0) {
						D3DXMatrixTranslation(&translation, (((spriteStruct*)tempinfo.asset)->rec.right*x + xOffsetP1), (((spriteStruct*)tempinfo.asset)->rec.bottom*y + yOffsetP1), 0.0f);
					}
					else {
						D3DXMatrixTranslation(&translation, (((spriteStruct*)tempinfo.asset)->rec.right*x + xOffsetP2), (((spriteStruct*)tempinfo.asset)->rec.bottom*y + yOffsetP2), 0.0f);
					}
					D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
					D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);



					Engine::instance()->addRender(tempinfo);
				
				

			}
		}
	}

	for (int i = 0; i < TETRIMINO_SIZE; ++i) {
		tempinfo.type = screenSprite;
		if (curtet.getBlock(i).getMagic()) {
			tempinfo.asset = &magicsprite;
		}
		else if (curtet.getType() == LINE)
			tempinfo.asset = &bluesprite;
		else if (curtet.getType() == JPIECE)
			tempinfo.asset = &darkbluesprite;
		else if (curtet.getType() == LPIECE)
			tempinfo.asset = &orangesprite;
		else if (curtet.getType() == SQUARE)
			tempinfo.asset = &yellowsprite;
		else if (curtet.getType() == SPIECE)
			tempinfo.asset = &greensprite;
		else if (curtet.getType() == TPIECE)
			tempinfo.asset = &purplesprite;
		else if (curtet.getType() == ZPIECE)
			tempinfo.asset = &redsprite;
		else
			tempinfo.asset = &greysprite;

			// Matrix transformation
			D3DXMatrixIdentity(&translation);
			D3DXMatrixIdentity(&scaling);
			D3DXMatrixIdentity(&tempinfo.matrix);

			if (a_player == 0) {
				D3DXMatrixTranslation(&translation, (((spriteStruct*)tempinfo.asset)->rec.right*curtet.getBlock(i).getPos().x + xOffsetP1), (((spriteStruct*)tempinfo.asset)->rec.bottom*curtet.getBlock(i).getPos().y + yOffsetP1), 0.0f);
			}
			else {
				D3DXMatrixTranslation(&translation, (((spriteStruct*)tempinfo.asset)->rec.right*curtet.getBlock(i).getPos().x + xOffsetP2), (((spriteStruct*)tempinfo.asset)->rec.bottom*curtet.getBlock(i).getPos().y + yOffsetP2), 0.0f);
			}
			D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
			D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);

			Engine::instance()->addRender(tempinfo);




		

	}




}


void Tetris::Reset(int a_controller) {
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
	timesliding = 0.0f;
	iNeedATetrimino = true;
	needgarbage = false;
	alive = true;
	controller = a_controller;
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
			timesliding = 0.0f;
		}
		else {	// if you do collide, snap to grid.
			if (a_y > 0.0f) {
				curtet.Snap(true);
				while (!DoICollide(0, 1.0f)) {
					curtet.Move(0, 1.0f);
				}
			}
			if (timesliding > timetoslide || Engine::instance()->getBind("Pad 1 Down DPAD") && controller == 1 && timesliding > timetoslideholdingdown || Engine::instance()->getBind("Pad 2 Down DPAD") && controller == 2 && timesliding > timetoslideholdingdown) {
				Solidify();
				needgarbage = true;
				timesliding = 0.0f;
			}
			else
				timesliding += Engine::instance()->dt();

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
	int tempdeath = linestosend;
	linestosend += checkAllLines();
	iNeedATetrimino = true;

	// check for death stuff
	tempdeath = linestosend - tempdeath;
	for (int i = 0; i < TETRIMINO_SIZE; ++i) {
		if (curtet.getBlock(i).getPos().y + tempdeath < DEATHZONE)
			alive = false;
	}


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
			}
			else if (field[x][y].getStuff() == NANO) {		//count Nanos in the line
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
	if (curtet.getType() != SQUARE) {
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
		bool outside = DoICollide(0, roundingthing);

		if (outside) { // change it back if it is outside
			for (int i = 0; i < TETRIMINO_SIZE; ++i) {
				curtet.SetBlockPos(i, fallingpos(temppos[i].x, temppos[i].y));
			}
		}

		curtet.Move(0, roundingthing);
	}
	else {// squares
		if (curtet.isMagic()) {
			int newmagic = 0;
			for (int i = 0; i < TETRIMINO_SIZE; ++i) {
				if (curtet.getBlock(i).getMagic()) {
					newmagic = i;
					curtet.SetBlockMagic(i, false);
				}
			}
			if (clockwise) {
				++newmagic;
			}
			else {
				--newmagic;
			}

			if (newmagic < 0)
				newmagic = TETRIMINO_SIZE - 1;
			else if (newmagic >= TETRIMINO_SIZE) {
				newmagic = 0;
			}

			curtet.SetBlockMagic(newmagic, true);
		}



	}

}


int Tetris::LinesToSend() {
	return linestosend;
}


void Tetris::setLinesToSend(int a_lines) {
	linestosend = a_lines;
}


bool Tetris::needPiece() {
	return iNeedATetrimino;
}


bool Tetris::needGarbage() {
	return needgarbage;
}


void Tetris::setPiece(Tetrimino& piece) {
	curtet = piece;
	iNeedATetrimino = false;
}


void Tetris::addGarbage(int a_garbage) {

	if (a_garbage > 0) {
		for (int x = 0; x < FIELD_SIZE_X; ++x) { // for each column,
			for (int y = 0; y < FIELD_SIZE_Y; ++y) { // and each row (starting from the bottom and going up to the DEATHZONE)
				if (y >= FIELD_SIZE_Y - a_garbage) { // if you're within the bottom and a_garbage,
					field[x][y].setStuff(BLOCK); // fill that area in.
				}
				else // if you're above a_garbage, bump things up by a_garbage
					field[x][y].setStuff(field[x][y + a_garbage].getStuff()); // move things up by a_garbage
			}
		}

		int random = rand() % SAMECOLUMNGARBAGECHANCE;
		int temp = 0;
		if (random == 0) { // garbage hole is in the same column as before
			for (int x = 0; x < FIELD_SIZE_X; ++x) { // for each column,
				if (field[x][FIELD_SIZE_Y - a_garbage - 1].getStuff() == EMPTY) {
					temp = x;

				}
			}

		}
		else { // garbage hole is in a random column
			temp = rand() % FIELD_SIZE_X;
		}

		for (int y = FIELD_SIZE_Y - 1; y >= FIELD_SIZE_Y - a_garbage; --y) {
			field[temp][y].setStuff(EMPTY);

		}
	}
	ClearDeathZone();
	needgarbage = false;


}


void Tetris::ClearDeathZone() {
	for (int x = 0; x < FIELD_SIZE_X; ++x) {
		for (int y = 0; y < DEATHZONE; ++y) {
			field[x][y].setStuff(EMPTY);
		}
	}
}


bool Tetris::Living() {
	return alive;
}




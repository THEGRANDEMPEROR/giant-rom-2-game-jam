#pragma once
#include "TetrisGame.h"
#include "Magic.h"





Player::Player() {

}


Player::~Player() {

}


void Player::Init(int a_player) {
	tetris.Init();
	player = a_player;
	for(int i = 0; i < 4; ++i) {
		abilities[i] = noPower;
	}
	magic = 0;
	effectLength = 0;
	magicRunning = 0;
	maxMagic = 20;
	
}


void Player::Update(int a_speed) {
	// draw character?
<<<<<<< HEAD
	tetris.Update(a_speed);
=======
	tetris.Update(controller, a_speed, curEffect);
>>>>>>> origin/master
	magic += tetris.getMagic();
	if(magic > maxMagic) {
		magic = maxMagic;
	}
	tetris.clearMagic();
	if(magicRunning > 0) {
		magicRunning -= Engine::instance()->dt();
		if(magicRunning < 0) {
			magicRunning = 0;
		}
	}
}


void Player::Draw() {
	// draw character portrait?
	tetris.Draw(player);
}

void Player::setMagic(int level, void (*func)(Player*,Player*)) {
	abilities[level] = func;
}

void Player::useMagic(Player* otherPlayer) {
	if(!isUsingMagic()&&!isBlocked()) {
		if(controller == 0) {
			if(Engine::instance()->getFlags("Player 1 Up DPAD")&buttonFlags::_pushed) {
				if(magic >= 4) {
					abilities[3](this,otherPlayer);
				} else {
					if(magic > 0) {
						abilities[magic-1](this,otherPlayer);
					}
				}
			}
		} else {
			if(Engine::instance()->getFlags("Player 2 Up DPAD")&buttonFlags::_pushed) {
				if(magic >= 4) {
					abilities[3](this,otherPlayer);
				} else {
					if(magic > 0) {
						abilities[magic-1](this,otherPlayer);
					}
				}
			}
		}
	}
}


void Player::BindCont(int a_controller) { // 0 keyboard. 1-4 gamepads.
	controller = a_controller;
}


void Player::Reset() {
	curEffect = noEffect;
	effectLength = 0;
	magic = 0;
	magicRunning = 0;
	tetris.Reset(controller);
}

bool Player::needPiece() {
	return tetris.needPiece();
}

void Player::setPiece(Tetrimino& piece) {
	tetris.setPiece(piece);
	if(curEffect != noEffect) {
		--effectLength;
		if(effectLength <= 0) {
			effectLength = 0;
			curEffect = noEffect;
		}
	}
}

TetrisGame* Player::getGame() {
	return game;
}

void Player::subMagic(int dec) {
	magic -= dec;
	if(magic < 0) {
		magic = 0;
	}
}

void Player::setUsingMagic(float timeUsingMagic) {
	magicRunning = timeUsingMagic;
}


int Player::LinesToSend() {
	return tetris.LinesToSend();
}


void Player::setLinesToSend(int a_lines) {
	tetris.setLinesToSend(a_lines);
}


void Player::addGarbage(int a_lines) {
	tetris.addGarbage(a_lines);
}


// returns true if they are about to solidify, and need some garbage lines.
bool Player::needGarbage() {
	return tetris.needGarbage();
}


bool Player::Living() {
	return tetris.Living();
}


TetrisGame::TetrisGame() {

}


TetrisGame::~TetrisGame() {

}


void TetrisGame::Init() {
	for (int i = 0; i < NUMPLAYERS; ++i) {
		players[i].Init(i);
	}
	running = true;
	speed = 0;
	speedtime = 0.0f;
	//moved binds to game.cpp

	p1wins = 0;
	p2wins = 0;

	rensa = false; // default off
	magic = true; // default on

	// initialize sprites
	// Initialize the blue sprite
	bluesprite.image = (imageAsset*)Engine::instance()->getResource("element_blue_square.png", image)->resource;
	bluesprite.rec.top = 0;
	bluesprite.rec.left = 0;
	bluesprite.rec.right = bluesprite.image->texInfo.Width;
	bluesprite.rec.bottom = bluesprite.image->texInfo.Height;
	bluesprite.color = 0xFFFFFFFF;
	bluesprite.center = D3DXVECTOR3(bluesprite.image->texInfo.Width / 2.0f, bluesprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the magic sprite
	magicsprite.image = (imageAsset*)Engine::instance()->getResource("element_bomb_square.png",0x00FFFFFF)->resource;
	magicsprite.rec.top = 0;
	magicsprite.rec.left = 0;
	magicsprite.rec.right = magicsprite.image->texInfo.Width;
	magicsprite.rec.bottom = magicsprite.image->texInfo.Height;
	magicsprite.color = 0xFFFFFFFF;
	magicsprite.center = D3DXVECTOR3(magicsprite.image->texInfo.Width / 2.0f, magicsprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the locked magic sprite
	lockedMagicsprite.image = (imageAsset*)Engine::instance()->getResource("element_bomb_square.png", image)->resource;
	lockedMagicsprite.rec.top = 0;
	lockedMagicsprite.rec.left = 0;
	lockedMagicsprite.rec.right = magicsprite.image->texInfo.Width;
	lockedMagicsprite.rec.bottom = magicsprite.image->texInfo.Height;
	lockedMagicsprite.color = 0xFF7F7F7F;
	lockedMagicsprite.center = D3DXVECTOR3(magicsprite.image->texInfo.Width / 2.0f, magicsprite.image->texInfo.Height / 2.0f, 0);
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

	// initialize tetqueue
	Tetrimino temptet;
	while(tetqueue.size() < 4) {
		temptet = randomTet();
		tetqueue.push_back(temptet);
	}
	// This is where I was initializing the tetqueue

	//BindPlayer(0, a_p1cont); 
	//BindPlayer(1, a_p2cont);
	for(int i = 0; i < 2; ++i) {
		players[i].setGame(this);
	}
}


void TetrisGame::Update() {
	if (running) {
		for (int i = 0; i < NUMPLAYERS; ++i) {
			players[i].Update(speed);
			//use magic
			players[i].useMagic(&players[i==0]);
			if(players[i].needPiece()) {
				players[i].setPiece(tetqueue[0]);
				tetqueue.erase(tetqueue.begin());
				tetqueue.push_back(randomTet());
			}
		}

		CancelOutLines();
		// send garbage if they just solidified a piece.
		if (players[0].needGarbage()) {
			players[0].addGarbage(players[1].LinesToSend());
			players[1].setLinesToSend(0);
		}
		if (players[1].needGarbage()) {
			players[1].addGarbage(players[0].LinesToSend());
			players[0].setLinesToSend(0);
		}


		
		speedtime += Engine::instance()->dt();
		if(speedtime >= TIMETOSPEEDUP) {
			if(speed < MAXSPEED) {
				++speed;
			}
			speedtime = 0;
		}



		// make sure this is at the end
		// Add an animation section probably, not sure how you did that for other states sad aust ANTIMATIONS SON
		if (!players[0].Living()) { // player 1 loss, player 2 wins
			p2wins++;
			if (p2wins < MAXWINS) // p2 doesn't win yet
				Reset(magic, rensa, false);
			else {
				Reset(magic, rensa, true); // MOVE THIS I JUST WANTED IT TO DO SOMETHING SO I PUT THIS HERE
				// move to the Rematch, charselect, main menu screen
			}
		}
		if (!players[1].Living()) { // player 2 loss, player 1 wins
			p1wins++;
			if (p1wins < MAXWINS) // p1 doesn't win yet
				Reset(magic, rensa, false);
			else {
				Reset(magic, rensa, true); // MOVE THIS, I JUST WANTED IT TO DO SOMETHING SO I PUT THIS HERE
				// move to the Rematch, charselect, main menu screen
			}
		}
		
	}
}


void TetrisGame::Draw() {
	renInfo tempInfo;
	if (running) {
		tempInfo.type = screenSprite;
		D3DXMatrixIdentity(&tempInfo.matrix);
		for (int i = 0; i < NUMPLAYERS; ++i) {
			players[i].Draw();
			//draw magic
			if(players[i].isBlocked()) {
				tempInfo.asset = &lockedMagicsprite;
			} else {
				tempInfo.asset = &magicsprite;
			}
			for(int x = 0; x < players[i].getMagic(); ++x) {
				D3DXMatrixTranslation(&tempInfo.matrix,(Engine::instance()->width()/2)-(magicsprite.rec.right*5)+((magicsprite.rec.right*7)*i), Engine::instance()->height()-magicsprite.rec.bottom-(magicsprite.rec.bottom*x),0);
				Engine::instance()->addRender(tempInfo);
			}
		}
		DrawQueue();
	}
}


void TetrisGame::BindPlayer(int a_player, int a_controller) { // 0 keyboard. 1-4 gamepads.
	players[a_player].BindCont(a_controller);
}



void TetrisGame::Reset(bool a_magic, bool a_rensa, bool a_winsreset) {
	for (int i = 0; i < NUMPLAYERS; ++i) {
		players[i].Reset();
	}
	magic = a_magic;
	rensa = a_rensa;
	speed = 0;
	speedtime = 0.0f;
	if (a_winsreset) {
		p1wins = 0;
		p2wins = 0;
	}
}


Tetrimino TetrisGame::randomTet() { // TETQUEUENO returns a random tetrimino
	int random = rand() % NUM_TETRIMINO_TYPES; // chance to be each type
	Tetrimino tet;

	bool a_magic = false;
	if (magic) { // magic in the options, son!
		int random2 = rand() % MAGICCHANCE; // chance to be magic

		if (random2 == 0)
			a_magic = true;
	}
	if (random == 0)
		tet.Init(LINE, a_magic);
	else if (random == 1)
		tet.Init(SQUARE, a_magic);
	else if (random == 2)
		tet.Init(LPIECE, a_magic);
	else if (random == 3)
		tet.Init(JPIECE, a_magic);
	else if (random == 4)
		tet.Init(SPIECE, a_magic);
	else if (random == 5)
		tet.Init(ZPIECE, a_magic);
	else if (random == 6)
		tet.Init(TPIECE, a_magic);


	return tet;


}


void TetrisGame::DrawQueue() {
	D3DXMATRIX translation, scaling;
	renInfo tempinfo;
	tempinfo.type = screenSprite;
	for (int g = 0; g < tetqueue.size(); ++g) {
		for (int i = 0; i < TETRIMINO_SIZE; ++i) {
			// Matrix transformation
			D3DXMatrixIdentity(&translation);
			D3DXMatrixIdentity(&scaling);
			D3DXMatrixIdentity(&tempinfo.matrix);
			if(tetqueue[g].getBlock(i).getMagic()) {
				tempinfo.asset = &magicsprite;
			} else {
				tempinfo.asset = &bluesprite;
			}
			//
			D3DXMatrixTranslation(&translation,(tetqueue[g].getBlock(i).getPos().x*((spriteStruct*)tempinfo.asset)->rec.right)+(Engine::instance()->width()/2)-(((spriteStruct*)tempinfo.asset)->rec.right*4), tetqueue[g].getBlock(i).getPos().y*((spriteStruct*)tempinfo.asset)->rec.bottom+(g*100)+((spriteStruct*)tempinfo.asset)->rec.bottom,0);
			D3DXMatrixScaling(&scaling,1,1,1);
			D3DXMatrixMultiply(&tempinfo.matrix,&scaling,&translation);
			Engine::instance()->addRender(tempinfo);
		}
	}
}


void TetrisGame::CancelOutLines() {
	int temp1 = players[0].LinesToSend();
	int temp2 = players[1].LinesToSend();
	temp1 -= temp2;
	temp2 -= players[0].LinesToSend();
	if (temp1 < 0)
		temp1 = 0;
	if (temp2 < 0)
		temp2 = 0;
	players[0].setLinesToSend(temp1);
	players[1].setLinesToSend(temp2);


}



void TetrisGame::setMagic(int player, int level, void (*func)(Player*,Player*)) {
	players[player].setMagic(level,func);
}

void TetrisGame::fillQueue(TetriminoType type,bool hasmagic, int fill) {
	Tetrimino temp;
	temp.Init(type,hasmagic);
	tetqueue.clear();
	for(int i = 0; i < fill; ++i) {
		tetqueue.push_back(temp);
	}
}
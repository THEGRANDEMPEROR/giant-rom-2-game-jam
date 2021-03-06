#pragma once
#include "TetrisGame.h"





Player::Player() {

}


Player::~Player() {

}


void Player::Init(int a_player) {
	tetris.Init();
	player = a_player;
}


void Player::Update(int a_speed) {
	// draw character?
	tetris.Update(controller, a_speed);
}


void Player::Draw() {
	// draw character portrait?
	tetris.Draw(player);
}


void Player::BindCont(int a_controller) { // 0 keyboard. 1-4 gamepads.
	controller = a_controller;
}


void Player::Reset() {
	tetris.Reset();
}

bool Player::needPiece() {
	return tetris.needPiece();
}

void Player::setPiece(Tetrimino& piece) {
	tetris.setPiece(piece);
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
	// player 1
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
	// player 2
	Engine::instance()->bind(pad2_RIGHT, "Player 2 Right DPAD");
	Engine::instance()->bind(pad2_UP, "Player 2 Up DPAD");
	Engine::instance()->bind(pad2_LEFT, "Player 2 Left DPAD");
	Engine::instance()->bind(pad2_DOWN, "Player 2 Down DPAD");
	Engine::instance()->bind(pad2_A, "Player 2 A");
	Engine::instance()->bind(pad2_B, "Player 2 B");
	Engine::instance()->bind(pad2_X, "Player 2 X");
	Engine::instance()->bind(pad2_Y, "Player 2 Y");
	Engine::instance()->bind(pad2_START, "Player 2 Start");
	Engine::instance()->bind(pad2_BACK, "Player 2 Back");

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
	magicsprite.image = (imageAsset*)Engine::instance()->getResource("element_bomb_square.png", image)->resource;
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



	// initialize tetqueue
	Tetrimino temptet;
	while(tetqueue.size() < 4) {
		temptet = randomTet();
		tetqueue.push_back(temptet);
	}
	// This is where I was initializing the tetqueue

	//BindPlayer(0, a_p1cont); 
	//BindPlayer(1, a_p2cont);
}


void TetrisGame::Update() {
	if (running) {
		for (int i = 0; i < NUMPLAYERS; ++i) {
			players[i].Update(speed);
			if(players[i].needPiece()) {
				players[i].setPiece(tetqueue[0]);
				tetqueue.erase(tetqueue.begin());
				tetqueue.push_back(randomTet());
			}
		}
		speedtime += Engine::instance()->dt();
		if (speedtime >= TIMETOSPEEDUP) {
			if (speed < MAXSPEED) {
				++speed;
			}
			speedtime = 0;
		}
	}
}


void TetrisGame::Draw() {
	if (running) {
		for (int i = 0; i < NUMPLAYERS; ++i) {
			players[i].Draw();
		}
		DrawQueue();
	}
}


void TetrisGame::BindPlayer(int a_player, int a_controller) { // 0 keyboard. 1-4 gamepads.
	players[a_player].BindCont(a_controller);
}



void TetrisGame::Reset(bool a_magic, bool a_rensa) {
	for (int i = 0; i < NUMPLAYERS; ++i) {
		players[i].Reset();
	}
	magic = a_magic;
	rensa = a_rensa;
	speed = 0;
	speedtime = 0.0f;
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
			D3DXMatrixTranslation(&translation,(tetqueue[g].getBlock(i).getPos().x*((spriteStruct*)tempinfo.asset)->rec.right)+200,tetqueue[g].getBlock(i).getPos().y*((spriteStruct*)tempinfo.asset)->rec.bottom+(g*100),0);
			D3DXMatrixScaling(&scaling,1,1,1);
			D3DXMatrixMultiply(&tempinfo.matrix,&scaling,&translation);
			Engine::instance()->addRender(tempinfo);
		}
	}
}



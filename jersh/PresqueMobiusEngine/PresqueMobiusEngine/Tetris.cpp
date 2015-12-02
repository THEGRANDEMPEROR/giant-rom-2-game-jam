#pragma once
#include "Tetris.h"



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
	solidsprite.rec.right = solidsprite.image->texInfo.Width;
	solidsprite.rec.bottom = solidsprite.image->texInfo.Height;
	solidsprite.center = D3DXVECTOR3(solidsprite.image->texInfo.Width / 2.0f, solidsprite.image->texInfo.Height / 2.0f, 0);
	// Initialize the magic sprite
	magicsprite.image = (imageAsset*)Engine::instance()->getResource("element_yellow_square.png", image)->resource;
	magicsprite.rec.right = magicsprite.image->texInfo.Width;
	magicsprite.rec.bottom = magicsprite.image->texInfo.Height;
	magicsprite.center = D3DXVECTOR3(magicsprite.image->texInfo.Width / 2.0f, magicsprite.image->texInfo.Height / 2.0f, 0);

	for (int y = 0; y < FIELD_SIZE_Y; ++y) {
		for (int x = 0; x < FIELD_SIZE_X; ++x) {
			field[x][y].Init(EMPTY, pos(x, y));
		}
	}// initialize the field to be empty

	// test stuff
	field[2][2].setStuff(BLOCK);
	field[2][3].setStuff(BLOCK);
	field[2][4].setStuff(BLOCK);
	field[2][5].setStuff(BLOCK);
	field[2][6].setStuff(NANO);
	// end of test stuff


	lines = 0; // initialize lines

	curtet.Init(LINE, false);





}


void Tetris::Update(int t) {

}


void Tetris::Draw() {
	D3DXMATRIX translation, scaling;
	
	renInfo tempinfo;
	tempinfo.type = screenSprite;
	tempinfo.asset = &solidsprite; // set it to solid sprite, just in case.
	
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
					D3DXMatrixScaling(&scaling, 0.001f, 0.001f, 0.001f);
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
					D3DXMatrixScaling(&scaling, 0.01f, 0.01f, 0.01f);
					D3DXMatrixMultiply(&tempinfo.matrix, &scaling, &translation);

					Engine::instance()->addRender(tempinfo);
				}

			}
		}
	}

}








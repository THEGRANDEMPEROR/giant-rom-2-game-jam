#pragma once
#include "TetrisGame.h"





Player::Player() {
	Init();
}


Player::~Player() {

}


void Player::Init() {
	controller = 0;
	tetris.Init();
}


void Player::Update() {
	// draw character?
	tetris.Update();
}


void Player::Draw() {
	// draw character portrait?
	tetris.Draw();
}





TetrisGame::TetrisGame() {
	for (int i = 0; i < NUMPLAYERS; ++i) {
		players[i].Init();
	}
	running = false;
}


TetrisGame::~TetrisGame() {

}


void TetrisGame::Init() {
	for (int i = 0; i < NUMPLAYERS; ++i) {
		players[i].Init();
	}
	running = true;
}


void TetrisGame::Update() {
	if (running) {
		for (int i = 0; i < NUMPLAYERS; ++i) {
			players[i].Update();
		}
	}
}


void TetrisGame::Draw() {
	if (running) {
		for (int i = 0; i < NUMPLAYERS; ++i) {
			players[i].Draw();
		}
	}
}









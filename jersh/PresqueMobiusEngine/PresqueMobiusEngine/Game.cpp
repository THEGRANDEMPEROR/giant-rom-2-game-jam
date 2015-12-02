#include "Game.h"
#include <fstream>

Game::Game() {
	cam.fov = 90.0f;
	cam.cam_pos = D3DXVECTOR3(0,0,2000);
	cam.cam_up_vec = D3DXVECTOR3(0,1,0);
	cam.cam_look_pos = D3DXVECTOR3(0,0,0);
	cam.drawDist = 5000;

	

	fps = 0;
}

Game::~Game() {
	shutdown();
}

void Game::init() {
	/*
	std::ofstream file;
	file.open("log.txt");
	if(file.is_open()) {
		file<<Engine::instance()->getsFrame()->getVersion()<<std::endl;
		file<<Engine::instance()->getsFrame()->getNumDevices()<<std::endl;
		for(int i = 0; i < Engine::instance()->getsFrame()->getNumDevices(); ++i) {
			file<<Engine::instance()->getsFrame()->getDeviceName(i)<<std::endl;
		}
		file.close();
	}
	*/



	tetristest.Init();


}

void Game::shutdown() {
	
}

bool Game::update() {
	


	tetristest.Draw();


	Engine::instance()->render();
	return true;
}
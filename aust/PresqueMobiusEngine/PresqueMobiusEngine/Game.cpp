#include "Game.h"
#include <fstream>

Game::Game() {
	cam.fov = 90.0f;
	cam.cam_pos = D3DXVECTOR3(0,0,2000);
	cam.cam_up_vec = D3DXVECTOR3(0,1,0);
	cam.cam_look_pos = D3DXVECTOR3(0,0,0);
	cam.drawDist = 5000;

	testInfo.type = screenSprite;
	D3DXMatrixIdentity(&testInfo.matrix);
	testInfo.asset = &testSprite;
	
	testSprite.center = D3DXVECTOR3(0,0,0);
	testSprite.color = D3DCOLOR_RGBA(255,255,255,255);
	testSprite.rec.left = 0;
	testSprite.rec.top = 0;
	testSprite.rec.right = 0;
	testSprite.rec.bottom = 0;

	testText.color = 0xFFFFFFFF;
	testText.flags = DT_TOP | DT_NOCLIP;

	testText.rect.bottom = 0.25f;
	testText.rect.top = 0.0f;
	testText.rect.right = 0.025f;
	testText.rect.left = 0.0f;

	testText.text = "Test Text WEEEEEEEEEEEEEE";

	testLine.vecCount = 5;
	testLine.vec = new D3DXVECTOR2 [testLine.vecCount];
	for(int i = 0; i < testLine.vecCount; ++i) {
		testLine.vec[i] = D3DXVECTOR2((1280/5)*i,(720/5)*i);
	}
	testLine.color = 0xFFFFFFFF;
	testLine.width = 5;

	fps = 0;
}

Game::~Game() {
	shutdown();
}

void Game::init() {
	testSprite.image = (imageAsset*)Engine::instance()->getResource("uvtest.png",image)->resource;
	testSprite.rec.right = testSprite.image->texInfo.Width;
	testSprite.rec.bottom = testSprite.image->texInfo.Height;
	testSprite.center = D3DXVECTOR3(testSprite.image->texInfo.Width/2.0f,testSprite.image->texInfo.Height/2.0f,0);

	testModel = (modelAsset*)Engine::instance()->Engine::getResource("tiny.x",xModel)->resource;
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
}

void Game::shutdown() {
	
}

bool Game::update() {
	testSprite.image = (imageAsset*)Engine::instance()->getResource("uvtest.png",image)->resource;
	Engine::instance()->setCam(&cam);
	testInfo.type = screenSprite;
	testInfo.asset = &testSprite;
	Engine::instance()->addRender(testInfo);

	testInfo.type = worldSprite;
	Engine::instance()->addRender(testInfo);

	fps = 1/Engine::instance()->dt();
	sprintf(buffer,"%f",fps);
	testText.text = buffer;
	testInfo.type = text;
	testInfo.asset = &testText;
	Engine::instance()->addRender(testInfo);

	testInfo.type = xmodel;
	testInfo.asset = testModel;
	Engine::instance()->addRender(testInfo);

	testInfo.type = line;
	testInfo.asset = &testLine;
	Engine::instance()->addRender(testInfo);

	Engine::instance()->render();
	return true;
}
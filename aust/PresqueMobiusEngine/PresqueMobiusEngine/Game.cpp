#include "Game.h"
#include <fstream>

bool play;

void quit() {
	play = false;
}

Game::Game() {
	showFPS = true;
	fpsText.color = 0xFFFFFFFF;
	fpsText.flags = DT_TOP | DT_NOCLIP;

	fpsText.rect.bottom = 0.25f;
	fpsText.rect.top = 0.0f;
	fpsText.rect.right = 0.025f;
	fpsText.rect.left = 0.0f;

	fpsText.text = "ERROR";

	fps = 0;
	play = true;
	
	frect temp;
	temp.top = 0.8f;
	temp.bottom = 0.9f;
	temp.left = 0.33f;
	temp.right = 0.66f;
	menu.addButton(&quit,"Quit",temp,DT_CENTER|DT_VCENTER,0xFFFFFFFF,0xFFFF0000);
	temp.top = 0.1f;
	temp.bottom = 0.2f;
	menu.addButton(NULL,"Play",temp,DT_CENTER|DT_VCENTER,0xFFFFFFFF,0xFFFF0000);

	//game pad menu bind
	Engine::instance()->bind(pad1_LYp,"SelectionUp");
	Engine::instance()->bind(pad1_LYn,"SelectionDown");
	Engine::instance()->bind(pad1_A,"Accept");
	//keyboard
	Engine::instance()->bind(W,"SelectionUp");
	Engine::instance()->bind(S,"SelectionDown");
	Engine::instance()->bind(SPACE,"Accept");
}

Game::~Game() {
	shutdown();
}

void Game::init() {

}

void Game::shutdown() {

}

bool Game::update() {
	menu.update();
	menu.render();
	
	if(showFPS) {
		fps = 1/Engine::instance()->dt();
		sprintf(buffer,"%d",(int)fps);
		fpsText.text = buffer;
		tempInfo.type = text;
		tempInfo.asset = &fpsText;
		Engine::instance()->addRender(tempInfo);
	}

	Engine::instance()->render();
	return play;
}
#include "Game.h"
#include <fstream>

void quit() {
	Engine::instance()->postMessage("Quit");
}

void start() {
	Engine::instance()->postMessage("Start");
}

void mMenu() {
	Engine::instance()->postMessage("MainMenu");
}

void charSelect() {
	Engine::instance()->postMessage("CharSelect");
}

void oMenu() {
	Engine::instance()->postMessage("Options");
}

void hMenu() {
	Engine::instance()->postMessage("Help");
}

void trensa() {
	Engine::instance()->postMessage("ToggleRensa");
}

void tmagic() {
	Engine::instance()->postMessage("ToggleMagic");
}


void Game::createMenu() {
	menu.clear();
	curState = mmenu;
	frect temp;
	temp.left = 0.33f;
	temp.right = 0.66f;

	temp.top = 0.5f;
	temp.bottom = 0.6f;
	menu.addButton(charSelect,"Play",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.6f;
	temp.bottom = 0.7f;
	menu.addButton(oMenu,"Options",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.7f;
	temp.bottom = 0.8f;
	menu.addButton(hMenu,"Help",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.8f;
	temp.bottom = 0.9f;
	menu.addButton(quit,"Quit",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);
}

void Game::createOptions() {
	char buffer[256];
	menu.clear();
	curState = omenu;
	frect temp;
	temp.left = 0.33f;
	temp.right = 0.66f;

	temp.top = 0.5f;
	temp.bottom = 0.6f;
	sprintf(buffer,"Toggle Rensa: %s",_rensa ? "true" : "false");
	menu.addButton(trensa,buffer,temp,DT_LEFT,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.6f;
	temp.bottom = 0.7f;
	sprintf(buffer,"Toggle Magic: %s",_magic ? "true" : "false");
	menu.addButton(tmagic,buffer,temp,DT_LEFT,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.8f;
	temp.bottom = 0.9f;
	menu.addButton(mMenu,"Back",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);
}

void Game::createHelp() {
	menu.clear();
	curState = hmenu;

	frect temp;
	temp.left = 0.33f;
	temp.right = 0.66f;
	temp.top = 0.8f;
	temp.bottom = 0.9f;
	menu.addButton(mMenu,"Back",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);
}

Game::Game() {
	_rensa = false;
	_magic = true;

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
	
	createMenu();

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
	if(curState != gplay) {
		menu.update();
		menu.render();

		//if(Engine::instance()->getMessage("CharSelect"))
		if(Engine::instance()->getMessage("MainMenu")) {
			menu.resetSelection();
			createMenu();
		}
		if(Engine::instance()->getMessage("Options")) {
			menu.resetSelection();
			createOptions();
		}
		if(Engine::instance()->getMessage("Help")) {
			menu.resetSelection();
			createHelp();
		}
		if(Engine::instance()->getMessage("Quit")) {
			play = false;
		}
		if(Engine::instance()->getMessage("ToggleRensa")) {
			_rensa = !_rensa;
			createOptions();
		}
		if(Engine::instance()->getMessage("ToggleMagic")) {
			_magic = !_magic;
			createOptions();
		}
	}

	if(showFPS) {
		fps = 1/Engine::instance()->dt();
		sprintf(buffer,"%d",(int)fps);
		fpsText.text = buffer;
		tempInfo.type = text;
		tempInfo.asset = &fpsText;
		Engine::instance()->addRender(tempInfo);
	}

	Engine::instance()->render();
	Engine::instance()->clearMessages();
	return play;
}
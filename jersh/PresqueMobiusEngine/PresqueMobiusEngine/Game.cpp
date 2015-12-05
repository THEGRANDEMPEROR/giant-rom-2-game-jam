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

//void bindcontrollers() {
//	Engine::instance()->postMessage("BindControllers");
//}




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

	//temp.top = 0.7f;
	//temp.bottom = 0.8f;
	//sprintf(buffer, "Bind Controllers");
	//menu.addButton(bindcontrollers, buffer, temp, DT_LEFT, 0xFFFFFFFF, 0xFFFF0000);

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

void Game::createFinish() {
	menu.clear();
	curState = finish;

	frect temp;
	temp.left = 0.33f;
	temp.right = 0.66f;

	temp.top = 0.5f;
	temp.bottom = 0.6f;
	menu.addButton(NULL,"Replay",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.6f;
	temp.bottom = 0.7f;
	menu.addButton(charSelect,"Character Select",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);

	temp.top = 0.7f;
	temp.bottom = 0.8f;
	menu.addButton(mMenu,"Exit",temp,DT_CENTER,0xFFFFFFFF,0xFFFF0000);
}

Game::Game() {
	srand(time(NULL));
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

	int numControllers = 0;
	XINPUT_STATE tempState;
	for(int i = 0; i < 2; ++i) {
		if(XInputGetState(i,&tempState) != ERROR_DEVICE_NOT_CONNECTED) {
			++numControllers;
		}
	}

	//bind types
	if(numControllers > 1) {
		//two controllers
		//game pad menu bind
		Engine::instance()->bind(pad1_LYp,"SelectionUp");
		Engine::instance()->bind(pad1_LYn,"SelectionDown");
		Engine::instance()->bind(pad1_UP, "SelectionUpDpad");
		Engine::instance()->bind(pad1_DOWN, "SelectionDownDpad");
		Engine::instance()->bind(pad1_A,"Accept");
		//keyboard
		Engine::instance()->bind(W,"SelectionUp");
		Engine::instance()->bind(S,"SelectionDown");
		Engine::instance()->bind(SPACE,"Accept");
		//p2 character select
		Engine::instance()->bind(pad2_LYp,"SelectionUp2");
		Engine::instance()->bind(pad2_LYn,"SelectionDown2");
		Engine::instance()->bind(pad2_UP, "SelectionUp2Dpad");
		Engine::instance()->bind(pad2_DOWN, "SelectionDown2Dpad");
		Engine::instance()->bind(pad2_A,"Accept2");

		// player 1 gamepad 1
		tetris.BindPlayer(0, 1); // first player. gamepads are 1-4 so first gamepad.
		// player 2 gamepad 2
		tetris.BindPlayer(1, 2); // second player. gamepads are 1-4 so second gamepad.

	} else {
		//one controller
		//keyboard
		Engine::instance()->bind(W,"SelectionUp");
		Engine::instance()->bind(S,"SelectionDown");
		Engine::instance()->bind(SPACE,"Accept");
		//p2 character select
		Engine::instance()->bind(pad1_LYp,"SelectionUp2");
		Engine::instance()->bind(pad1_LYn,"SelectionDown2");
		Engine::instance()->bind(pad1_UP, "SelectionUp2Dpad");
		Engine::instance()->bind(pad1_DOWN, "SelectionDown2Dpad");
		Engine::instance()->bind(pad1_A,"Accept2");

		// player 1 keyboard
		tetris.BindPlayer(0, 0); // first player. keyboard is 0.
		// player 2 gamepad 2
		tetris.BindPlayer(1, 1); // second player. gamepads are 1-4 so first gamepad.
	}

	p1Name.flags = DT_CENTER;
	p1Name.color = 0xFFFF0000;

	p2Name.flags = DT_CENTER;
	p2Name.color = 0xFF0000FF;
}

Game::~Game() {
	shutdown();
}

void Game::init() {
	backGround.image = (imageAsset*)Engine::instance()->getResource("LogoAlt.png",D3DXCOLOR(255,0,0,0))->resource;
	backGround.color = 0xFFFFFFFF;
	backGround.rec.left = 0;
	backGround.rec.top = 0;
	backGround.rec.right = backGround.image->texInfo.Width;
	backGround.rec.bottom = backGround.image->texInfo.Height;
	backGround.center = D3DXVECTOR3(backGround.rec.right/2.0f,backGround.rec.bottom/2.0f,0);

	CharacterInfo tempChar;
	tempChar.icon.rec.top = 0;
	tempChar.icon.rec.left = 0;
	tempChar.icon.color = 0xFFFFFFFF;

	tempChar.name = "Drew Scanlon";
	tempChar.icon.image = (imageAsset*)Engine::instance()->getResource("DrewScanlon.jpg",image)->resource;
	tempChar.icon.rec.right = tempChar.icon.image->texInfo.Width;
	tempChar.icon.rec.bottom = tempChar.icon.image->texInfo.Height;
	tempChar.icon.center = D3DXVECTOR3(tempChar.icon.rec.right/2.0f,tempChar.icon.rec.bottom/2.0f,0);

	for(int i = 0; i < 4; ++i) {
		tempChar.abilities[i] = NULL;
	}

	charList.push_back(tempChar);

	//Dan Ryckert
	tempChar.name = "Dan Ryckert";
	tempChar.icon.image = (imageAsset*)Engine::instance()->getResource("DanRyckert.jpg",image)->resource;
	tempChar.icon.rec.right = tempChar.icon.image->texInfo.Width;
	tempChar.icon.rec.bottom = tempChar.icon.image->texInfo.Height;
	tempChar.icon.center = D3DXVECTOR3(tempChar.icon.rec.right/2.0f,tempChar.icon.rec.bottom/2.0f,0);

	for(int i = 0; i < 4; ++i) {
		tempChar.abilities[i] = NULL;
	}

	charList.push_back(tempChar);

	tempChar.name = "Hideo Kojima";
	tempChar.icon.image = (imageAsset*)Engine::instance()->getResource("HideoMB2.jpg",image)->resource;
	tempChar.icon.rec.right = tempChar.icon.image->texInfo.Width;
	tempChar.icon.rec.bottom = tempChar.icon.image->texInfo.Height;
	tempChar.icon.center = D3DXVECTOR3(tempChar.icon.rec.right/2.0f,tempChar.icon.rec.bottom/2.0f,0);

	for(int i = 0; i < 4; ++i) {
		tempChar.abilities[i] = NULL;
	}

	charList.push_back(tempChar);
	Engine::instance()->setRepeat(0.2f);

	tetris.Init();
}

void Game::shutdown() {

}

void Game::startTetris() {
	curState = gplay;
	tetris.Reset(_magic, _rensa);
	//Engine::instance()->setRepeat(0.1f); // maybe change this
}

bool Game::update() {
	frect tempRec;
	if(curState != gplay) {
		if(curState != cselect) {
			menu.update();
			menu.render();
			tempInfo.type = screenSprite;
			tempInfo.asset = &backGround;
			D3DXMatrixIdentity(&tempInfo.matrix);
			D3DXMatrixTranslation(&tempInfo.matrix,1280/2,720/4,0);
			Engine::instance()->addRender(tempInfo);

			if(Engine::instance()->getMessage("CharSelect")) {
				menu.resetSelection();
				p1Lock = false;
				p2Lock = false;
				p1Select = 0;
				p2Select = 0;
				startDelay = 3.0f;
				curState = cselect;
			}
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
			//if (Engine::instance()->getMessage("BindControllers")) {
			//	thought about it, and this is actually not necessary since it's only two controllers that are loaded kinda. fuckit man. fuckit.
			//}
		} else {
			//character select menu
			if(!p1Lock) {
				if (Engine::instance()->getFlags("SelectionUp")&buttonFlags::_repeat || Engine::instance()->getFlags("SelectionUpDpad")&buttonFlags::_repeat) {
					--p1Select;
				}
				else if (Engine::instance()->getFlags("SelectionDown")&buttonFlags::_repeat || Engine::instance()->getFlags("SelectionDownDpad")&buttonFlags::_repeat) {
					++p1Select;
				} else if(Engine::instance()->getFlags("Accept")&buttonFlags::_repeat) {
					p1Lock = true;
				}

				if(p1Select < 0) {
					p1Select = charList.size()-1;
				} else if(p1Select >= charList.size()) {
					p1Select = 0;
				}
			}

			if(!p2Lock) {
				if (Engine::instance()->getFlags("SelectionUp2")&buttonFlags::_repeat || Engine::instance()->getFlags("SelectionUp2Dpad")&buttonFlags::_repeat) {
					--p2Select;
				}
				else if (Engine::instance()->getFlags("SelectionDown2")&buttonFlags::_repeat || Engine::instance()->getFlags("SelectionDown2Dpad")&buttonFlags::_repeat) {
					++p2Select;
				} else if(Engine::instance()->getFlags("Accept2")&buttonFlags::_repeat) {
					p2Lock = true;
				}

				if(p2Select < 0) {
					p2Select = charList.size() - 1;
				} else if(p2Select >= charList.size()) {
					p2Select = 0;
				}
			}

			//draw character select
			tempInfo.type = text;

			if(p1Lock) {
				tempRec.top = 0.1f;
				tempRec.bottom = 0.2f;
				tempRec.left = 0.0f;
				tempRec.right = 0.5f;
				p1Name.text = charList[p1Select].name;
			} else {
				tempRec.top = (p1Select*0.33f);
				tempRec.bottom = tempRec.top + 0.1;
				tempRec.left = 0.4f;
				tempRec.right = 0.6f;
				p1Name.text = "P1";
			}
			p1Name.rect = tempRec;
			tempInfo.asset = &p1Name;
			Engine::instance()->addRender(tempInfo);

			if(p2Lock) {
				tempRec.top = 0.1f;
				tempRec.bottom = 0.2f;
				tempRec.left = 0.5f;
				tempRec.right = 1.0f;
				p2Name.text = charList[p2Select].name;
			} else {
				tempRec.top = 0.2+(p2Select*0.33f);
				tempRec.bottom = tempRec.top + 0.1;
				tempRec.left = 0.4f;
				tempRec.right = 0.6f;
				p2Name.text = "P2";
			}

			p2Name.rect = tempRec;
			tempInfo.asset = &p2Name;
			Engine::instance()->addRender(tempInfo);

			tempInfo.type = screenSprite;
			for(int i = 0; i < charList.size(); ++i) {
				tempInfo.asset = &charList[i].icon;
				D3DXMatrixIdentity(&tempInfo.matrix);
				D3DXMatrixIdentity(&charTrans);
				D3DXMatrixScaling(&tempInfo.matrix,240.0f/charList[i].icon.image->texInfo.Width,240.0f/charList[i].icon.image->texInfo.Height,0);
				D3DXMatrixTranslation(&charTrans,1280.0f/2,120+(i*240),0);
				D3DXMatrixMultiply(&tempInfo.matrix,&tempInfo.matrix,&charTrans);
				Engine::instance()->addRender(tempInfo);
			}
			if(p1Lock&&p2Lock) {
				startDelay -= Engine::instance()->dt();
				if(startDelay <= 0) {
					//start game
					startTetris();
				}
			}

		}
	}
	else { // GPLAY!
		tetris.Update();

		tetris.Draw(); // SAD AUST IT CRASHES BECAUSE OF THIS I'M GOING TO BED WTF IS WRONG AAAAAAAAAAAAHHHHHHHHHHHHHHHHHHH
						// CTRL+F FOR: dammitrender
						// to get to my other comments showing where things are.
						// never mind these comments

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
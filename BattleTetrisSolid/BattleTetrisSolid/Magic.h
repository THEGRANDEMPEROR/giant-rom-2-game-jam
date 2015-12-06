#pragma once
#include "TetrisGame.h"

static void noPower(Player* start,Player* other) {

}

//Drew's magic
//Drew Grenade
static void grenade(Player* start, Player* other) {
	//destory 3x3 block
	//renso drop
	start->subMagic(1);
}

//Drew Good Posture
static void goodPosture(Player* start,Player* other) {
	if(!other->isImmune()) {
		//prevent other player from rotating
		other->setEffect(noRot,5);
	}
	start->subMagic(2);
}

//Drew The Scanlon Special
static void scalonSpecial(Player* start,Player* other) {
	int blocksLeft = 10;
	if(!other->isImmune()) {
		//destroy 10 blocks at random
		other->getTetris();
	}
	start->subMagic(3);
}

//Drew Tricaster Master
static void tricaster(Player* start,Player* other) {
	if(!other->isImmune()) {
		//rotates the other players block at random
		other->setEffect(ranRot,5);
	}
	start->subMagic(4);
}

//Dan's magic
//Dan Pow Block
static void powBlock(Player* start, Player* other) {
	//destroy the bottom 3 lines
	start->getTetris()->clearBottom(3);
	start->subMagic(1);
}

//Dan DMX Goomba
static void dmx(Player* start, Player* other) {
	if(!other->isImmune()) {
		//send 3 junk lines to the other player
		start->setLinesToSend(start->LinesToSend()+3);
	}
	start->subMagic(2);
}

//Dan MarioPartyParty
static void marioParty(Player* start, Player* other) {
	//clear block queue and fill it with current block type
	start->getGame()->fillQueue(start->getTetris()->curType(),start->getTetris()->curTetMagic(),8);
	start->subMagic(3);
}

//Dan Yellow Russian
static void yellowRussian(Player* start, Player* other) {
	if(!other->isImmune()) {
		//destroy 18 blocks at random

		//add 2 junk lines
		start->setLinesToSend(start->LinesToSend()+2);
	}
	start->subMagic(4);
}

//Kojima's magic
//kojima Fulton
static void fulton(Player* start,Player* other) {
	//remove the top 3 lines
	start->getTetris()->clearTop(3);
	start->subMagic(1);
}

//kojima Box
static void cardboardBox(Player* start,Player* other) {
	if(!start->isImmune()) {
		start->setEffect(attackImmune,5);
		start->subMagic(2);
	}
}

//kojima snake what took you so long?
static void tookSoLong(Player* start, Player* other) {
	//prevent the other player from droping block for 5 blocks
	if(!other->isImmune()) {
		other->setEffect(noDrop,5);
	}
	start->subMagic(3);
}

//kojima guns of the patriots
static void gop(Player* start,Player* other) {
	if(!other->isImmune()) {
		other->getTetris()->transformMagic();
		other->setEffect(noMagic,5);
	}
	start->subMagic(4);
}
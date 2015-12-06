#pragma once
#include "TetrisGame.h"

static void noPower(Player* start,Player* other) {

}

//Drew's magic


//Dan's magic


//Kojima's magic
//kojima Fulton

//kojima Box
static void box(Player* start,Player* other) {
	if(!start->isImmune()) {
		start->setImmune(10.0f);
		start->subMagic(2);
	}
}


//kojima guns of the patriots
static void gop(Player* start,Player* other) {
	if(!other->isUsingMagic()) {
		if(!other->isImmune()) {
			other->getTetris()->transformMagic();
			other->setBlocked(10.0f);
		}
		start->subMagic(3);
	}
}
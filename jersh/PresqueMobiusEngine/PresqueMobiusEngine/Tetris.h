#pragma once



const int FIELD_SIZE_X = 10; // the width of a standard tetris field
const int FIELD_SIZE_Y = 22; // the height of a standard tetris field. topmost 2 are hidden, where the new pieces get spawned.
							// Player loss on a block solidifying in those two spaces.



enum spotstuff {
	EMPTY,
	BLOCK,
	NANO
};


struct pos {
	int x, y;
	pos() { x = 0; y = 0; }
	pos(int a_y, int a_x) {
		x = a_x;
		y = a_y;
	}
};


class spot {
private:
	spotstuff stuff;		// can be empty or filled, possibly add ghost or falling
	pos position;			// x,y from the top down. top left corner is 0,0 bottom right corner should be 9,21
	// sprite
public:
	spot() { stuff = EMPTY; position = pos(0, 0); /*sprite*/ }
	spot(spotstuff a_stuff, pos a_position/*, sprite*/) {
		stuff = a_stuff;
		position = a_position;

	};
	spotstuff getStuff();
	pos getPos();
	void setStuff(spotstuff a_stuff);
	// position should never change, so we don't need a set for it.
	// void Draw();
};


class Tetris {
private:
	spot field[FIELD_SIZE_X][FIELD_SIZE_Y];
public:
	Tetris();
	~Tetris();
	void Init();
	void Update(int t);
	void Draw();

};




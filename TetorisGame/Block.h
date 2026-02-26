#ifndef __BLOCK_H__
#define __BLOCK_H__

const int SHAPES[2][4][4][4] = {
	// I
	{
		{{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
		{{0, 0, 0, 0}, {0, 0, 0, 0}, {1,1,1,1}, {0, 0, 0, 0}},
		{{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
		{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}
	},
	// L
	{
		{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}, {1, 1, 1, 1}},
		{{1, 0, 0, 0}, {1, 0, 0, 0}, {1,0,0,0}, {1, 1, 0, 0}},
		{{1, 1, 1, 1}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{{0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}}
	}
};

class Block {
private:
	int type;
	int rotate;
	int x, y;
public:
	Block(int t) : type(t), rotate(0), x(4), y(0) {}

	int getX() const { return x; }
	int getY() const { return y; }
	int getShapeValue(int r, int c) const { return SHAPES[type][rotate][r][c]; }

	void moveDown() { y++; }
	void moveLeft() { x--; }
	void moveRight() { x++; }
};

#endif
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <iostream>
#include <string>
using namespace std;

#include "Board.h"

class Renderer {
private:
	const string block_table[3] = { "  ", "■ ", "▣ " };
public:
	void updateBoard(const Board& board) {
		system("cls");
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				cout << block_table[board.getValue(x, y)];
			} cout << '\n';
		}
	}
};

#endif
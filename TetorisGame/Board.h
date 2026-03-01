#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <algorithm>
using namespace std;

#include "Block.h"

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 21

class Board {
private:
	vector <vector <int>> board;
public:
	Board() {
		board.assign(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 0));
		for (int i = 0; i < BOARD_HEIGHT - 1; ++i) {
			board[i][0] = 3; board[i][BOARD_WIDTH - 1] = 3;
		} fill(board[BOARD_HEIGHT - 1].begin(), board[BOARD_HEIGHT - 1].end(), 3);
	}
	
	int getValue(int x, int y) const { return board[y][x]; }

	void LockBlock(const Block& block) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (block.getShapeValue(i, j) == 1) {
					int bx = block.getX() + j, by = block.getY() + i;
					if (bx >= 0 && bx < BOARD_WIDTH && by >= 0 && by < BOARD_HEIGHT)
						board[by][bx] = 2;
				}
			}
		}
	}

	int CheckLines() {
		int clearedLine = 0;
		for (int y = BOARD_HEIGHT - 2; y >= 0; --y) {
			bool full = 1;
			for (int x = 0; x < BOARD_WIDTH; ++x) { if (board[y][x] == 0) { full = 0; break; } }
			if (full) {
				board.erase(board.begin() + y);
				board.insert(board.begin(), vector<int>(BOARD_WIDTH, 0));
				y++; clearedLine++;
			}
		} return clearedLine;
	}
};

#endif
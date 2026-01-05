#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <algorithm>
using namespace std;

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 21

class Board {
private:
	vector <vector <int>> board;
public:
	Board() {
		board.assign(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 0));
		for (int i = 0; i < BOARD_HEIGHT - 1; ++i) {
			board[i][0] = 2; board[i][BOARD_WIDTH - 1] = 2;
		} fill(board[BOARD_HEIGHT - 1].begin(), board[BOARD_HEIGHT - 1].end(), 2);
	}
	int getValue(int x, int y) const{
		return board[y][x];
	}
};

#endif
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Board.h"
#include "Renderer.h"
#include "Block.h"

class GameManager {
private:
	Board board;
	Renderer renderer;
	Block cur_block;
	Block next_block;
	
	unsigned long long last_time;
	int score;
public:
	GameManager() : cur_block(rand() % 7), next_block(rand() % 7) { renderer.InitGame(); last_time = GetTickCount64(); score = 0; }

	bool CanMove(int nX, int nY) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (cur_block.getShapeValue(i, j) == 1) {
					int targetX = nX + j; int targetY = nY + i;
					if (targetX < 0 || targetX >= BOARD_WIDTH || targetY >= BOARD_HEIGHT) return 0;
					if (board.getValue(targetX, targetY) != 0) return 0;
				}
			}
		} return 1;
	}

	void Update() {
		unsigned long long now = GetTickCount64();
		if (now - last_time > 500) {
			if (CanMove(cur_block.getX(), cur_block.getY() + 1)) cur_block.moveDown();
			else {
				board.lockBlock(cur_block);
				cur_block = next_block;
				next_block = Block(rand() % 7);
			} last_time = now;
		}
	}

	void Render() {
		renderer.updateBoard(board, cur_block, 2, 1);
		renderer.BufferFlip();
	}
};

#endif
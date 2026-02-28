#include "GameScene.h"

bool GameScene::CanMove(int nX, int nY) {
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

void GameScene::BlockUpdate() {
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

void GameScene::Render() {
	getRenderer()->DrawBoard(board, cur_block, 2, 1);
	getRenderer()->BufferFlip();
}

SceneType GameScene::Run() {
	Render(); BlockUpdate(); return SceneType::GAME;
}
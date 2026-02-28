#include "GameScene.h"

void GameScene::InputKey() {
	if (_kbhit()) {
		int key = _getch(), curX = curBlock.getX(), curY = curBlock.getY();
		switch (key) {
		case KEY_LEFT: if (CanMove(curX - 1, curY)) curBlock.MoveLeft(); break;
		case KEY_RIGHT: if (CanMove(curX + 1, curY)) curBlock.MoveRight(); break;
		case KEY_DOWN: if (CanMove(curX, curY + 1)) curBlock.MoveDown(); break;
		case 'Z':
		case 'z':
			if (CanMove(curX, curY, curBlock.getNextShape())) curBlock.Rotate(); break;
		}
	}
}

bool GameScene::CanMove(int nX, int nY, const int (*shape)[4]) {
	if (shape == nullptr) shape = curBlock.getShape();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (shape[i][j] == 1) {
				int targetX = nX + j; int targetY = nY + i;
				if (targetX < 0 || targetX >= BOARD_WIDTH || targetY >= BOARD_HEIGHT) return 0;
				if (targetY >= 0 && board.getValue(targetX, targetY) != 0) return 0;
			}
		}
	} return 1;
}

void GameScene::BlockUpdate() {
	unsigned long long now = GetTickCount64();
	if (now - lastTime > 500) {
		if (CanMove(curBlock.getX(), curBlock.getY() + 1)) curBlock.MoveDown();
		else {
			board.LockBlock(curBlock);
			curBlock = nextBlock;
			nextBlock = Block(rand() % 7);
		} lastTime = now;
	}
}

void GameScene::Render() {
	int ghostY = curBlock.getY(); while (CanMove(curBlock.getX(), ghostY + 1)) ghostY++;
	getRenderer()->DrawBoard(board, curBlock, ghostY, 0, 0);
	getRenderer()->BufferFlip();
}

SceneType GameScene::Run() {
	Render(); 
	InputKey(); 
	BlockUpdate(); 
	return SceneType::GAME;
}
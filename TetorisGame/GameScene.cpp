#include "GameScene.h"

SceneType GameScene::InputKey() {
	if (_kbhit()) {
		if (isGameOver) return SceneType::TITLE;
		int key = _getch(), curX = curBlock.getX(), curY = curBlock.getY();
		switch (key) {
		case KEY_LEFT: if (CanMove(curX - 1, curY)) curBlock.MoveLeft(); break;
		case KEY_RIGHT: if (CanMove(curX + 1, curY)) curBlock.MoveRight(); break;
		case KEY_DOWN: if (CanMove(curX, curY + 1)) curBlock.MoveDown(); break;
		case 'Z':
		case 'z':
			if (CanMove(curX, curY, curBlock.getNextShape())) curBlock.Rotate(); break;
		case KEY_SPACE:
			int dropY = curBlock.getY(); while (CanMove(curBlock.getX(), dropY + 1)) dropY++;
			for (int i = curBlock.getY(); i < dropY; ++i) curBlock.MoveDown();
			break;
		}
	} return SceneType::GAME;
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
	if (isGameOver) return;
	unsigned long long now = GetTickCount64();
	if (now - lastTime > 500) {
		if (CanMove(curBlock.getX(), curBlock.getY() + 1)) curBlock.MoveDown();
		else {
			board.LockBlock(curBlock);

			int lines = board.CheckLines();
			if (lines > 0) score += (lines * 100);

			curBlock = nextBlock;
			nextBlock = Block(rand() % 7);

			if (!CanMove(curBlock.getX(), curBlock.getY())) isGameOver = 1;
		} lastTime = now;
	}
}

void GameScene::Render() {
	int ghostY = curBlock.getY(); while (CanMove(curBlock.getX(), ghostY + 1)) ghostY++;
	getRenderer()->DrawBoard(board, curBlock, ghostY, 0, 0);

	if (isGameOver) {
		getRenderer()->DrawString("======================", 5, 10);
		getRenderer()->DrawString("      GAME OVER       ", 5, 11);
		getRenderer()->DrawString(" Press Any Key to Exit ", 5, 12);
		getRenderer()->DrawString("======================", 5, 13);
	}

	getRenderer()->BufferFlip();
}

SceneType GameScene::Run() {
	Render(); 
	SceneType scene = InputKey(); 
	BlockUpdate(); 
	return scene;
}
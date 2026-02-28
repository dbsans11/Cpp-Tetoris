#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <Windows.h>
#include "Board.h"
#include "Block.h"
#include "BaseScene.h"

class GameScene : public BaseScene {
private:
	Board board;
	Block curBlock;
	Block nextBlock;
	
	unsigned long long lastTime;
	int score;
public:
	GameScene(Renderer* r) : BaseScene(r), curBlock(rand() % 7), nextBlock(rand() % 7) { lastTime = GetTickCount64(); score = 0; }
	SceneType getSceneType() override { return SceneType::GAME; }
	void InputKey();
	bool CanMove(int nX, int nY, const int (*shape)[4] = nullptr);
	void BlockUpdate();
	void Render();
	SceneType Run() override;
};

#endif
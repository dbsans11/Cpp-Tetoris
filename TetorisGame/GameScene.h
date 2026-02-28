#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <Windows.h>

#include "Board.h"
#include "Renderer.h"
#include "Block.h"
#include "BaseScene.h"

class GameScene : public BaseScene {
private:
	Board board;
	Block cur_block;
	Block next_block;
	
	unsigned long long last_time;
	int score;
public:
	GameScene(Renderer* r) : BaseScene(r), cur_block(rand() % 7), next_block(rand() % 7) { last_time = GetTickCount64(); score = 0; }
	SceneType getSceneType() override { return SceneType::GAME; }
	bool CanMove(int nX, int nY);
	void BlockUpdate();
	void Render();
	SceneType Run() override;
};

#endif
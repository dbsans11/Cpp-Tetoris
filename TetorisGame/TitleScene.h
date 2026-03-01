#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "BaseScene.h"

class TitleScene : public BaseScene {
private:
	int menu;
	bool isBlink;
public:
	TitleScene(Renderer* r) : BaseScene(r) { menu = 0; isBlink = 0; }
	SceneType getSceneType() override { return SceneType::TITLE; }
	SceneType InputKey();
	void Render();
	SceneType Run() override;
	~TitleScene() override {}
};

#endif
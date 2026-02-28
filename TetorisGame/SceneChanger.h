#ifndef __SCENE_CHANGER_H__
#define __SCENE_CHANGER_H__

#include "Renderer.h"
#include "BaseScene.h"

class SceneChanger {
private:
	Renderer renderer;
	BaseScene* cur_scene;
	bool isRun;
public:
	SceneChanger(SceneType scene = SceneType::TITLE) : cur_scene(nullptr) { renderer.InitGame(); ChangeScene(scene); isRun = 1; }
	bool getIsRun() { return isRun; }
	void ChangeScene(SceneType type);
	void Update();
	~SceneChanger();
};

#endif
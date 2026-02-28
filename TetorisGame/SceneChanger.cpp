#include "SceneChanger.h"
#include "TitleScene.h"
#include "GameScene.h"

void SceneChanger::ChangeScene(SceneType type) {
	if (type == SceneType::EXIT) { isRun = 0; return; }
	while (_kbhit()) _getch();
	if (cur_scene != nullptr) {
		delete cur_scene;
		renderer.ClearBothBuffers();
	}
	switch (type) {
	case SceneType::TITLE: cur_scene = new TitleScene(&renderer); break;
	case SceneType::GAME: cur_scene = new GameScene(&renderer); break;
	}
}

void SceneChanger::Update() {
	if (cur_scene) {
		SceneType next = cur_scene->Run();
		if (next != cur_scene->getSceneType()) ChangeScene(next);
	}
}

SceneChanger::~SceneChanger() {
	if (cur_scene != nullptr) { delete cur_scene; cur_scene = nullptr; }
	renderer.DestroyGame();
}
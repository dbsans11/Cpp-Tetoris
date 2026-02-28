#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include <conio.h>
#include "Renderer.h"

enum class SceneType {
	TITLE, GAME, SETTING, GAMEOVER, EXIT
};

enum keyCode {
	KEY_UP = 72,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_DOWN = 80,

	KEY_ENTER = 13,
	KEY_SPACE = 32
};

class BaseScene {
private:
	Renderer* renderer;
public:
	BaseScene(Renderer* r) : renderer(r) {}
	Renderer* getRenderer() const { return renderer; }
	virtual SceneType getSceneType() = 0;
	virtual SceneType Run() = 0;
	virtual ~BaseScene() {}
};

#endif
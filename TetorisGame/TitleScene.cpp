#include "TitleScene.h"

SceneType TitleScene::InputKey() {
	if (_kbhit()) {
		int key = _getch();

		if (key == KEY_ENTER) {
			if (menu == 0) return SceneType::GAME;
			if (menu == 2) return SceneType::EXIT;
		}

		if (key == KEY_UP) menu = menu > 0 ? menu - 1 : 2;
		else if (key == KEY_DOWN) menu = menu < 2 ? menu + 1 : 0;
		return SceneType::TITLE;
	}
}

void TitleScene::Render() {
	getRenderer()->DrawString("■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■", 0, 0);
	getRenderer()->DrawString("  ■     ■         ■     ■   ■   ■   ■     ■     ■", 0, 1);
	getRenderer()->DrawString("  ■     ■ ■ ■     ■     ■   ■   ■ ■       ■     ■ ■ ■", 0, 2);
	getRenderer()->DrawString("  ■     ■         ■     ■   ■   ■   ■     ■         ■", 0, 3);
	getRenderer()->DrawString("  ■     ■ ■ ■     ■     ■ ■ ■   ■   ■   ■ ■ ■   ■ ■ ■", 0, 4);

	getRenderer()->DrawString("< press ENTER to play >", 15, 6);

	getRenderer()->DrawString(menu == 0 ? "▶  게임 시작" : "    게임 시작", 20, 8);
	getRenderer()->DrawString(menu == 1 ? "▶  게임 설정" : "    게임 설정", 20, 10);
	getRenderer()->DrawString(menu == 2 ? "▶  게임 종료" : "    게임 종료", 20, 12);

	getRenderer()->BufferFlip();
}

SceneType TitleScene::Run() {
	SceneType scene = InputKey();
	Render();
	return scene;
}
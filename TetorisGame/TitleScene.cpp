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
	} return SceneType::TITLE;
}

void TitleScene::Render() {
	getRenderer()->DrawString("■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■   ■ ■ ■", 4, 2);
	getRenderer()->DrawString("  ■     ■         ■     ■   ■   ■   ■     ■     ■", 4, 3);
	getRenderer()->DrawString("  ■     ■ ■ ■     ■     ■   ■   ■ ■       ■     ■ ■ ■", 4, 4);
	getRenderer()->DrawString("  ■     ■         ■     ■   ■   ■   ■     ■         ■", 4, 5);
	getRenderer()->DrawString("  ■     ■ ■ ■     ■     ■ ■ ■   ■   ■   ■ ■ ■   ■ ■ ■", 4, 6);

	getRenderer()->DrawString(isBlink?"< press ENTER to play >":"                       ", 19, 9);

	getRenderer()->DrawString(menu == 0 ? "> 게임 시작" : "   게임 시작", 22, 12);
	getRenderer()->DrawString(menu == 1 ? "> 게임 설정" : "   게임 설정", 22, 14);
	getRenderer()->DrawString(menu == 2 ? "> 게임 종료" : "   게임 종료", 22, 16);

	getRenderer()->BufferFlip();
}

SceneType TitleScene::Run() {
	static int frame = 0; frame++;
	if (frame >= 15) { isBlink = !isBlink; frame = 0; }
	SceneType scene = InputKey();
	Render();
	return scene;
}
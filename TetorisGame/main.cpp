#include "GameManager.h"
#include <Windows.h>
int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	GameManager game;
	while (1) {
		game.Update();
		game.Render();
		Sleep(33);
	}
	return 0;
}
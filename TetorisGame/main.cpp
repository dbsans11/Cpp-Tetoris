#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include "SceneChanger.h"
#pragma comment(lib, "winmm.lib")

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	PlaySound(L"Bgm.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	SceneChanger sc;
	while (sc.getIsRun()) {
		sc.Update();
		Sleep(33);
	} 
	return 0;
}
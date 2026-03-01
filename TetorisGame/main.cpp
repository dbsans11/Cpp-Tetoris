#include <iostream>
#include <Windows.h>
//#include <mmsystem.h>
#include "SceneChanger.h"
//#pragma comment(lib, "winmm.lib")

int main() {
	//system("mode con: cols=60 lines=30 | title TETORIS");
	srand(static_cast<unsigned int>(time(NULL)));
	//PlaySound(L"Bgm.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	SceneChanger sc;
	while (sc.getIsRun()) {
		sc.Update();
		Sleep(33);
	} 
	return 0;
}
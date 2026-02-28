#include <iostream>
#include <Windows.h>
#include "SceneChanger.h"
int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	SceneChanger sc;
	while (sc.getIsRun()) {
		sc.Update();
		Sleep(33);
	} 
	return 0;
}
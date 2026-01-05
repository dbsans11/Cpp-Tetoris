#ifndef __CONSOLECONFIG_H__
#define __CONSOLECONFIG_H__

#include <Windows.h>

struct stRect {
	int nWidth;
	int nHeight;
};

struct stConsole {
	HANDLE hConsole;
	stRect rtConsole;
	HANDLE hBuffer[2];
	int nCurBuffer;

	stConsole() : hConsole(nullptr), hBuffer{ nullptr, }, nCurBuffer(0) {}
};

#endif
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#include "Board.h"

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

class Renderer {
private:
	stConsole console;
	const char block_table[3][4] = { "  ", "■", "▣"};
public:
	void InitGame(bool blnitConsole = true) {
		if (blnitConsole) {
			console.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			console.nCurBuffer = 0;

			CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE };
			CONSOLE_SCREEN_BUFFER_INFO consoleInfo{ 0, };
			GetConsoleScreenBufferInfo(console.hConsole, &consoleInfo);
			consoleInfo.dwSize.X = 40; consoleInfo.dwSize.Y = 30;

			console.rtConsole.nWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left;
			console.rtConsole.nHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;

			console.hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
			SetConsoleScreenBufferSize(console.hBuffer[0], consoleInfo.dwSize);
			SetConsoleWindowInfo(console.hBuffer[0], TRUE, &consoleInfo.srWindow);
			SetConsoleCursorInfo(console.hBuffer[0], &consoleCursor);
		}
	}

	void DestroyGame() {
		if (console.hBuffer[0] != nullptr) CloseHandle(console.hBuffer[0]);
		if (console.hBuffer[1] != nullptr) CloseHandle(console.hBuffer[1]);
	}

	void ClearScreen() {
		COORD pos{ 0, };
		DWORD dwWritten = 0;
		unsigned size = console.rtConsole.nWidth * console.rtConsole.nHeight;
		FillConsoleOutputCharacter(console.hConsole, ' ', size, pos, &dwWritten);
		SetConsoleCursorPosition(console.hConsole, pos);
	}

	void BufferFlip() {
		SetConsoleActiveScreenBuffer(console.hBuffer[console.nCurBuffer]);
		console.nCurBuffer = console.nCurBuffer ? 0 : 1;
	}

	void updateBoard(const Board& board, int nXOffset=0, int nYOffset=0) {
		COORD coord{ 0, };
		DWORD dw = 0;

		for (int nY = 0; nY < BOARD_HEIGHT; ++nY) {
			for (int nX = 0; nX < BOARD_WIDTH; ++nX) {
				coord.X = nX * 2 + nXOffset;
				coord.Y = nY + nYOffset;
				SetConsoleCursorPosition(console.hBuffer[console.nCurBuffer], coord);
				WriteFile(console.hBuffer[console.nCurBuffer], block_table[board.getValue(nX, nY)], (DWORD)strlen(block_table[board.getValue(nX, nY)]), &dw, NULL);
			}
		}
	}
};

#endif
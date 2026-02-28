#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <Windows.h>
#include "Board.h"
#include "Block.h"

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
	const char block_table[4][4] = { "  ", "■", "□", "▣"};
public:
	void InitGame(bool blnitConsole = true);
	void DestroyGame();
	void ClearScreen();
	void ClearBothBuffers();
	void BufferFlip();

	void DrawString(const char* str, int x = 0, int y = 0);
	void DrawBoard(const Board& board, const Block& block, int x = 0, int y = 0);
};

#endif
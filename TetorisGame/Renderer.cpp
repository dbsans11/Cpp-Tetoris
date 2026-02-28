#include "Renderer.h"

void Renderer::InitGame(bool blnitConsole) {
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

		console.hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(console.hBuffer[1], consoleInfo.dwSize);
		SetConsoleWindowInfo(console.hBuffer[1], TRUE, &consoleInfo.srWindow);
		SetConsoleCursorInfo(console.hBuffer[1], &consoleCursor);
	}
}

void Renderer::DestroyGame() {
	if (console.hBuffer[0] != nullptr) CloseHandle(console.hBuffer[0]);
	if (console.hBuffer[1] != nullptr) CloseHandle(console.hBuffer[1]);
}

void Renderer::ClearScreen() {
	COORD pos{ 0, };
	DWORD dwWritten = 0;
	unsigned size = console.rtConsole.nWidth * console.rtConsole.nHeight;
	FillConsoleOutputCharacter(console.hConsole, ' ', size, pos, &dwWritten);
	SetConsoleCursorPosition(console.hConsole, pos);
}

void Renderer::ClearBothBuffers() {
	COORD pos{ 0, };
	DWORD dwWritten = 0;
	unsigned size = console.rtConsole.nWidth * console.rtConsole.nHeight;
	FillConsoleOutputCharacter(console.hBuffer[0], ' ', size, pos, &dwWritten);
	SetConsoleCursorPosition(console.hBuffer[0], pos);
	FillConsoleOutputCharacter(console.hBuffer[1], ' ', size, pos, &dwWritten);
	SetConsoleCursorPosition(console.hBuffer[1], pos);
}

void Renderer::BufferFlip() {
	SetConsoleActiveScreenBuffer(console.hBuffer[console.nCurBuffer]);
	console.nCurBuffer = console.nCurBuffer ? 0 : 1;
}


void Renderer::DrawString(const char* str, int x, int y) {
	COORD coord{ 0, };
	DWORD dw = 0;
	coord.X = (SHORT)x; coord.Y = (SHORT)y;
	SetConsoleCursorPosition(console.hBuffer[console.nCurBuffer], coord);
	WriteFile(console.hBuffer[console.nCurBuffer], str, (DWORD)strlen(str), &dw, NULL);
}

void Renderer::DrawBoard(const Board& board, const Block& block, int ghostY, int x, int y) {
	COORD coord{ 0, };
	DWORD dw = 0;

	for (int ny = 0; ny < BOARD_HEIGHT; ++ny) {
		for (int nx = 0; nx < BOARD_WIDTH; ++nx) {
			coord.X = nx * 2 + x;
			coord.Y = ny + y;
			SetConsoleCursorPosition(console.hBuffer[console.nCurBuffer], coord);
			WriteFile(console.hBuffer[console.nCurBuffer], block_table[board.getValue(nx, ny)], (DWORD)strlen(block_table[board.getValue(nx, ny)]), &dw, NULL);
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (block.getShapeValue(i, j) == 1) {
				coord.X = (block.getX() + j) * 2 + x;
				coord.Y = ghostY + i;
				SetConsoleCursorPosition(console.hBuffer[console.nCurBuffer], coord);
				WriteFile(console.hBuffer[console.nCurBuffer], block_table[4], (DWORD)strlen(block_table[1]), &dw, NULL);

				coord.Y = (block.getY() + i) + y;
				SetConsoleCursorPosition(console.hBuffer[console.nCurBuffer], coord);
				WriteFile(console.hBuffer[console.nCurBuffer], block_table[1], (DWORD)strlen(block_table[1]), &dw, NULL);
			}
		}
	}
}
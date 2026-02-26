#include "Board.h"
#include "Renderer.h"
#include "Block.h"
#include <Windows.h>
int main() {
	Board board; Renderer renderer; renderer.updateBoard(board); renderer.InitGame();
	while (1) {
		renderer.updateBoard(board, 3, 1);
		renderer.ClearScreen();
		renderer.BufferFlip();
		Sleep(33);
	}
}
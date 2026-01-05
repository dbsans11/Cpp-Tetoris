#include "Board.h"
#include "Renderer.h"
#include <Windows.h>
int main() {
	Board board; Renderer renderer; renderer.updateBoard(board);
	/*while (1) {
		renderer.updateBoard(board);
		Sleep(33);
	}*/
}
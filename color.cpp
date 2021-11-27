#include <windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(int b) {
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | b));
}
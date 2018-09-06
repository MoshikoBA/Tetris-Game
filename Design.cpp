#include "Design.h"
#include <Windows.h>

void changeColor(int num)
{ // change the color of the printing on the screen.

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, num | FOREGROUND_INTENSITY);
}


void hidecursor()
{ // hide the curson on the screen.

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
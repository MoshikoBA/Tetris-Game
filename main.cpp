#include "Tetris.h"

#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

void main()
{

	hidecursor();
	Tetris().printMenu();

	while (_getch() != '1') {}

	Tetris().run();
	system("pause>null");
}

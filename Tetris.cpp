#include "Tetris.h"
#include <conio.h>
#include <typeinfo>

Tetris::Tetris()
{ // Tetris class c'tor.

	numParts = 0;
	score = 0;
	status = RUNNING;
	sleepSpeed = 200;
	currentShape = nullptr;

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if ((i == 21) || (j == 0) || (j == 11))
				gameMat[i][j] = 2;
			else
				gameMat[i][j] = 0;
		}
	}
	printFrame();
}

//======================================================================================================>

void Tetris::createShape(eShape shape)
{ // The function creat the currently tetris's shape randomally.

	switch (shape)
	{
	case Tetris::SQUARE:
		currentShape = new Square('X');
		type = SQUARE;
		break;

	case Tetris::RECTANGLE:
		currentShape = new Rectanglee('X');
		type = RECTANGLE;
		break;

	case Tetris::JOKER:
		currentShape = new Joker('X');
		type = JOKER;
		break;

	case Tetris::BOMB:
		currentShape = new Bomb('@');
		type = BOMB;
		break;

	case Tetris::GUN:
		currentShape = new Gun('X');
		type = GUN;
		break;

	case Tetris::PLUS:
		currentShape = new Plus('X');
		type = PLUS;
		break;

	case Tetris::SNACK:
		currentShape = new Snack('X');
		type = SNACK;
		break;

	}
}

//======================================================================================================>

void Tetris::run()
{  // This function is responsible for running the game. It prints the menu, the frame and information of the game,
   // and takes user clicks and plays the game according to the rules of the Tetris.

	bool gameRun = true;
	printInformation();

	while (gameRun == true) //while the game is not over
	{
		int randShape = rand() % 7;
		createShape(eShape(randShape));
		currentShape->draw();
		bool shapeRunning = true;

		while (shapeRunning == true) // while the shape still in movement.
		{
			keyPressedCare(shapeRunning, gameRun);
		}

		updateBoard(gameRun);
		if (type== BOMB)

			bombTheBoard();

		delete currentShape;
	}
}

//======================================================================================================>

void Tetris::keyPressedCare(bool& shapeRunning, bool& gameRun)
{ // this function get key by the user and move the shape according to the tetris game.

	Sleep(sleepSpeed);

	char keyPressed = 0;
	if (_kbhit()) // checks if there is anything in the buffer
		keyPressed = _getch(); // take the head of the buffe

	if (isASpecialKeyPress(keyPressed) == true) // if the user preesed a special key
		SpecialKeyPressedCare(keyPressed, shapeRunning, gameRun);

	else
	{
		if (_kbhit()) // checks if there is anything in the buffer
			keyPressed = _getch();

		if (keyPressed == Shape::DOWN) // the user pressed to down the shape as possible.
			currentShape->moveDownAsPossible(shapeRunning, gameMat) ;

		else if (currentShape->canMove(Shape::eDirection(keyPressed), shapeRunning,gameMat) == true) // the user move the shape right or left or rotate.
			if ((type != JOKER) && (type != BOMB))
				currentShape->move(Shape::eDirection(keyPressed));
	}
}

//======================================================================================================>

void Tetris::updateBoard(bool& gameRun)
{ // this function care to update the board(the mat), check to full lines and to the end to check if the game is over.

	if (gameRun == true) // if the game is not over
	{
		if (type != BOMB)
			updateMat();

		checkForFullLine();  // check if there are full lines

		if (isGameOver() == true) // if the game is over
		{
			gameRun = false;
			gotoxy(35, 0);
			cout << "GAME OVER!!";
			setStatus(GAME_OVER);
		}
		else
			updateNumParts();   // update the ammount of the parts.
	}
	printInformation();
}

//======================================================================================================>

void Tetris::updateMat()
{ // The function updates the mat in according to the shape's points's coordinates and color.

	for (int i = 0; i < currentShape->size; i++)
		gameMat[currentShape->arr[i].getY()][currentShape->arr[i].getX() - START_COL + 1] = currentShape->typeColor;
}

//======================================================================================================>

void Tetris::printFrame()
{ // print the tetris game's frame on the screen.
	changeColor(Shape::GREEN);

	for (int i = 6; i < 21; i++)
	{
		for (int j = 34; j < 50; j += 11)
		{
			gotoxy(j, i);
			cout << (unsigned char)186;
		}
	}
	gotoxy(34, 21);
	cout << (unsigned char)200;
	gotoxy(35, 21);
	for (int i = 0; i < 10; i++)
	{
		cout << (unsigned char)205;
	}
	cout << (unsigned char)188;
}

//======================================================================================================>

bool Tetris::isASpecialKeyPress(char& keyPressed)
{ // The function returns true if the user pressed a special key, else returns false.

	if ((keyPressed == '2') || (keyPressed == '3') || (keyPressed == '4') || (keyPressed == '5'))
		return true;

	return false;
}

//======================================================================================================>

bool Tetris::isGameOver()
{ // The function returns true if the game is over, else returns false.
	for (int i = 1; i < 11; i++)
	{
		if (gameMat[5][i] != 0)
			return true;
	}

	return false;
}

//======================================================================================================>

void Tetris::checkForFullLine()
{ // The function checks if there are full lines in the game, and takes care of it.

	int i = 20;
	while (i > 5)
	{
		if (isItFullLine(i))
		{
			updateScore();  // updates the game's score.
			removeLine(i);     // removes the full line.
			printMat(i, currentShape->ch);   // prints the new table.
		}
		else
			i--;
	}
}

//======================================================================================================>

bool Tetris::isItFullLine(int line)
{ // The function receives a line's index and returns true if the line is full, else returns false.

	for (int i = 1; i < 11; i++)
	{
		if (gameMat[line][i] == 0)
			return false;
	}
	return true;

}

//======================================================================================================>

void Tetris::removeLine(int line)
{ // The function receives a full line's index and removes it. In addition, the function
  //  subtracts each line above it one row down.

	char space[11] = "          ";
	char b[11] = "----------";

	gotoxy(35, line);
	cout << b;
	Sleep(100);
	gotoxy(35, line);

	cout << space;

	for (int i = line; i > 3; i--)
	{
		for (int j = 1; j<11; j++)
			gameMat[i][j] = gameMat[i - 1][j];
	}
}

//======================================================================================================>

void Tetris::printMat(int line, char ch) const
{ // The function receives line's index and char, and prints the game's table on the screen(according to the char).

	for (int i = line; i >= 5; i--)
	{
		Sleep(100);
		for (int j = 1; j < 11; j++)
		{
			gotoxy(34 + j, i);

			if (gameMat[i][j] != 0)
			{
				changeColor(gameMat[i][j]);
				cout << ch;
			}
			else
				cout << " ";
		}
	}
}

//======================================================================================================>

void Tetris::pauseGame(char& keyPressed)
{ // the function pauses the game.

	setStatus(PAUSE);
	printInformation();
	while (true)
	{
		if (_getch() == '2')
		{
			setStatus(RUNNING);
			printInformation();
			keyPressed = 0;
			break;
		}
	}
}

//======================================================================================================>

void Tetris::increaseSpeed()
{ // increases the speed of the game.

	if (sleepSpeed > 50)
		sleepSpeed -= 50;
}

//======================================================================================================>

void Tetris::decreaseSpeed()
{ // decreases the speed of the game.

	if (sleepSpeed < 500)
		sleepSpeed += 50;
}

//======================================================================================================>

void Tetris::SpecialKeyPressedCare(char& keyPressed, bool& shapeRunning, bool& gameRunning)
{ // The function takes care of special key that the user pressed.

	switch (keyPressed)
	{
	case '2':
		pauseGame(keyPressed);
		break;

	case '3':
		increaseSpeed();
		break;

	case '4':
		decreaseSpeed();
		break;

	case '5':
		exitGame(shapeRunning, gameRunning);
		break;
	}
}

//======================================================================================================>

void Tetris::exitGame(bool& shapeRunning, bool& gameRunning)
{ // The function stops the game.

	shapeRunning = false;
	gameRunning = false;
	gotoxy(35, 0);
	cout << "GAME OVER!!";

	setStatus(EXIT);
}

//======================================================================================================>

void Tetris::updateScore(int points)
{ // the function receives Shape(by ref) and int, and updates the score accordingly.

	if (type == JOKER)
	{
		score += 50;
		return;
	}

	if (type != BOMB)
	{
		score += 100;
		return;
	}
	score -= points;
	printInformation();
}

//======================================================================================================>

void Tetris::printInformation() const
{ // prints the game's information.

	changeColor(Shape::GREEN);
	char space[10] = "        ";
	gotoxy(0, 0);
	cout << "Parts: " << numParts << space << "\n" << "Score: " << score << space << "\n";
	cout << "Game status: " << statuses[status] << space;
}

//======================================================================================================>

void Tetris::bombTheBoard()
{ // The function bomb all the point around the present shape (only if it bomb)  in 3X3 range, and
  // update the score.

	int xLocation = currentShape->arr[0].getX() - START_COL+1;
	int yLocation = currentShape->arr[0].getY();


	short counter = 0;
	for (int i = yLocation - 1; i < yLocation + 2; i++)
	{
		for (int j = xLocation - 1; j < xLocation + 2; j++)
		{
			if (gameMat[i][j] != 2)
			{
				if (gameMat[i][j] != 0)
				{
					counter++;
					gotoxy(j + START_COL - 1, i);
					cout << "-";
					Sleep(50);
				}

				gameMat[i][j] = 0;
				gotoxy(j + START_COL - 1, i);
				cout << " ";
				Sleep(50);
			}
		}
	}
	updateScore(counter * 50);
}

//======================================================================================================>

void Tetris::printMenu() const
{ // prints the game's menu.

	changeColor(0);

	gotoxy(1, 5);
	cout << "MENU\n";
	cout << "   <1> START\n";
	cout << "   <2> PAUSE/PLAY\n";
	cout << "   <3> INCREASE SPEED\n";
	cout << "   <4> DECREASE SPEED\n";
	cout << "   <5> EXIT\n";
}
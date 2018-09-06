#ifndef _TETRIS_H_
#define _TETRIS_H_

#include "Tetris.h"
#include "Shape.h"
#include "Square.h"
#include "Rectangle.h"
#include "Joker.h"
#include "Bomb.h"
#include "Gun.h"
#include "Plus.h"
#include "Snack.h"
#include <conio.h>
#include <typeinfo>
#include <string>


class Tetris
{

public:
	enum eStatus { RUNNING, PAUSE, GAME_OVER, EXIT };
	string statuses[4] = { "Running", "Pause", "Game Over", "Exit" };
	enum eShape { SQUARE, RECTANGLE, JOKER, BOMB, GUN, PLUS, SNACK };


	Tetris();
	void run();
	void printMenu() const;
	void keyPressedCare(bool& shapeRunning, bool& gameRun);
	void updateBoard(bool& gameRun);

private:
	short numParts;
	int score;
	short gameMat[22][12];
	eStatus status;
	short sleepSpeed;
	Shape* currentShape;
	eShape type;

	void printFrame();
	bool isASpecialKeyPress(char& keyPressed);
	bool isGameOver();
	void checkForFullLine();
	bool isItFullLine(int line);
	void removeLine(int line);
	void printMat(int line, char ch) const;
	void pauseGame(char& keyPressed);
	void increaseSpeed();
	void decreaseSpeed();
	void SpecialKeyPressedCare(char& keyPressed, bool& shapeRunning, bool& gameRunning);
	void exitGame(bool& shapeRunning, bool& gameRunning);
	void updateNumParts() { numParts += 1; }; // updates the number of parts.
	void updateScore( int points = 0);
	void printInformation() const;
	void setStatus(eStatus status) { this->status = status; };  // receives eStatus variable and set it as the Tetris's status.
	void bombTheBoard();
	void createShape(eShape shape);
	void updateMat();
};












#endif

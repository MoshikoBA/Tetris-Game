#include "Joker.h"

Joker::Joker(unsigned char ch)
{ // Joker's c'tor

	size = 1;
	this->ch = ch;
	arr = new Point{ ch, 40, 5 };
	typeColor = YELLOW;
	angle = 0;
}

//======================================================================================================>

void Joker::draw(unsigned char ch) const
{ // Prints the shape on the screen.

	changeColor(typeColor);
	for (int i = 0; i < size; i++)
		arr[i].draw(ch);
}

//======================================================================================================>

bool Joker::canMove(eDirection direction, bool& running, const short mat[22][12])
{  // The function returns true if the shape can move according to the direcrion (and moves it), else returns false.

	short tempRow = arr[0].getY(), tempCol = arr[0].getX() - START_COL + 1;

	switch (direction)
	{
	case LEFT:
		for (int i = 0; i < tempCol + 1; i++)
		{
			if (mat[tempRow][tempCol - 1 - i] == 0)
			{
				draw(' ');
				arr[0].setCoordinate(tempCol - 1 - i + START_COL - 1, tempRow);
				draw(this->getChar());
				return true;
			}
		}
		break;

	case RIGHT:
		for (int i = 0; i < 10 - tempCol; i++)
		{
			if (mat[tempRow][tempCol + 1 + i] == 0)
			{
				draw(' ');
				arr[0].setCoordinate(tempCol + 1 + i + START_COL - 1, tempRow);
				draw(this->getChar());
				return true;
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < 21 - tempRow; i++)
		{
			if (mat[tempRow + i + 1][tempCol] == 0)
			{
				Sleep(20);
				draw(' ');
				arr[0].setCoordinate(tempCol + START_COL - 1, tempRow + i + 1);
				draw(this->getChar());
				return true;
			}
		}
		break;

	case 0:
		if (canMove(DOWN, running,mat) == false)
			running = false;
		break;

	case 's':
		running = false;
	}
	return false;
}

//======================================================================================================>

void Joker::moveDownAsPossible(bool& running, const short mat [22][12])
{ // The function drops the shape down as possible.

	while (canMove(DOWN, running, mat)){}
	running = false;
}

#include "Square.h"

Square::Square(unsigned char ch)
{ // Snack's c'tor

	size = 4;
	arr = new Point[size]{ { ch, 39, 4 },{ ch, 40, 4 },{ ch, 39, 5 },{ ch, 40, 5 } };
	typeColor = BLUE;
	this->ch = ch;
	angle = 0;
}

//======================================================================================================>

void Square::draw(unsigned char ch) const
{ // Prints the shape on the screen.

	changeColor(typeColor);
	for (int i = 0; i < size; i++)
		arr[i].draw(ch);
}

//======================================================================================================>

void Square::move(eDirection direction)
{  // The function moves the shape according to the direction.

	draw(' ');
	{
		switch (direction)
		{
		case LEFT:
			for (int i = 0; i < size; i++)
				arr[i].setCoordinate(arr[i].getX() - 1, arr[i].getY());
			break;

		case RIGHT:
			for (int i = 0; i < size; i++)
				arr[i].setCoordinate(arr[i].getX() + 1, arr[i].getY());
			break;

		case DOWN:
		case 0:
			for (int i = 0; i < size; i++)
				arr[i].setCoordinate(arr[i].getX(), arr[i].getY() + 1);
			break;
		}

		draw(this->getChar());
	}
}

//======================================================================================================>

bool Square::canMove(eDirection direction, bool& running, const short mat[22][12])
{  // The function returns true if the shape can move/rotate according to the direcrion, else returns false.

	switch (direction)
	{
	case LEFT:
		for (int i = 0; i < 4; i++)
		{
			int parameterX = arr[i].getX() - 1 - START_COL + 1;
			int parameterY = arr[i].getY();
			if (mat[parameterY][parameterX] != 0)
				return false;

		}
		break;

	case RIGHT:
		for (int i = 0; i < 4; i++)
		{
			int parameterX = arr[i].getX() + 1 - START_COL + 1;
			int parameterY = arr[i].getY();
			if (mat[parameterY][parameterX] != 0)
					return false;

		}
		break;
	case DOWN:
	case 0:
		for (int i = 0; i < 4; i++)
		{
			int parameterX = arr[i].getX() - START_COL + 1;
			int parameterY = arr[i].getY() + 1;
			if (mat[parameterY][parameterX] != 0)
			{
				running = false;
				return false;

			}

		}
		break;
	case UP:
		return false;
		break;

	}
	return true;
}

//======================================================================================================>

void Square::moveDownAsPossible(bool& running, const short mat[22][12])
{ // The function drops the shape down as possible.

	while (canMove(DOWN, running, mat))
	{
		move(DOWN);
		Sleep(20);
	}
	running = false;
}

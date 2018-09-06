#include "Bomb.h"


Bomb::Bomb(unsigned char ch)
{ // Bomb's c'tor

	size = 1;
	this->ch = '@';
	arr = new Point{ ch, 40, 5 };
	typeColor = YELLOW;
	angle = 0;
}

//======================================================================================================>

void Bomb::draw(unsigned char ch) const
{ // Prints the shape on the screen.

	changeColor(typeColor);
	for (int i = 0; i < size; i++)
		arr[i].draw(ch);
}

//======================================================================================================>

void Bomb::move(eDirection direction)
{ // The function moves the shape according to the direction.

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

bool Bomb::canMove(eDirection direction, bool& running, const short mat [22][12])
{  // The function returns true if the shape can move according to the direcrion(and moves it), else returns false.

	switch (direction)
	{
	case LEFT:
		if (mat[arr[0].getY()][arr[0].getX() - 1 - START_COL + 1] == 0)
		{
			move(direction);
			return true;
		}
		else
		{
			if (arr[0].getX() != START_COL)
				running = false;

			return false;
		}
		break;

	case RIGHT:
		if (mat[arr[0].getY()][arr[0].getX() + 1 - START_COL + 1] == 0)
		{
			move(direction);
			return true;
		}
		else
		{
			if (arr[0].getX() != LAST_COL)
				running = false;

			return false;
		}
		break;

	case DOWN:
	case 0:
		if (mat[arr[0].getY() + 1][arr[0].getX() - START_COL + 1] == 0)
		{
			move(direction);
			return true;
		}
		else
		{
			if (arr[0].getX() != LAST_ROW)
				running = false;

			return false;
		}
		break;
	}
	return false;
}

//======================================================================================================>

void Bomb::moveDownAsPossible(bool& running, const short mat [22][12])
{ // The function drops the shape down as possible.

	while (canMove(DOWN, running, mat)) {}
	running = false;
}
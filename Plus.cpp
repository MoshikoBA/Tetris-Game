#include "Plus.h"

Plus::Plus(unsigned char ch)
{ // PLus's c'tor

	size = 4;
	arr = new Point[size]{ { ch, 40, 4 },{ ch, 39, 5 },{ ch, 40, 5 },{ ch, 41, 5 } };
	typeColor = WHITE;
	this->ch = ch;
	angle = 0;
}

//======================================================================================================>

void Plus::draw(unsigned char ch) const
{ // Prints the shape on the screen.

	changeColor(typeColor);
	for (int i = 0; i < size; i++)
		arr[i].draw(ch);
}

//======================================================================================================>

void Plus::move(eDirection direction)
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

bool Plus::canMove(eDirection direction, bool& running, const short mat[22][12])
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
		if (canRotate(mat))
			rotateGun();

		return false;
	}
	return true;
}

//======================================================================================================>

void Plus::moveDownAsPossible(bool& running, const short mat[22][12])
{ // The function drops the shape down as possible.

	while (canMove(DOWN, running, mat))
	{
		move(DOWN);
		Sleep(20);
	}
	running = false;
}

//======================================================================================================>

bool Plus::canRotate(const short mat[22][12])
{  // The function returns true if the shape can rotate, else returns false.

	int parameterX;
	int parameterY;

	switch (angle)
	{
	case 0:
		parameterX = arr[0].getX() - 1 - START_COL + 1;
		parameterY = arr[0].getY() - 1;

		for (int i = 0; i < 3; i++)
			if (mat[parameterY + i][parameterX])
				return false;
		break;

	case 90:
		parameterX = arr[0].getX() -1 - START_COL + 1;
		parameterY = arr[0].getY() - 1;

		for (int i = 0; i < 3; i++)
			if (mat[parameterY][parameterX + i])
				return false;
		break;

	case 180:
		parameterX = arr[0].getX() + 1 - START_COL + 1;
		parameterY = arr[0].getY() - 1;

		for (int i = 0; i < 3; i++)
			if (mat[parameterY - i][parameterX])
				return false;
		break;

	case 270:
		parameterX = arr[0].getX() -1 - START_COL + 1;
		parameterY = arr[0].getY() + 1;

		for (int i = 0; i < 3; i++)
			if (mat[parameterY][parameterX + i])
				return false;
		break;
	}

	return true;
}

//======================================================================================================>

void Plus::rotateGun()
{  // The function rotates the shape 90 degrees

	draw(' ');
	int parameterX;
	int parameterY;


	switch (angle)
	{
	case 0:
		parameterX = arr[0].getX() - 1;
		parameterY = arr[0].getY() - 1;

		for (int i = 0; i < 3; i++)
			arr[i + 1].setCoordinate(parameterX, parameterY+i);
		break;

	case 90:
		parameterX = arr[0].getX() - 1 ;
		parameterY = arr[0].getY() - 1;

		for (int i = 0; i < 3; i++)
			arr[i + 1].setCoordinate(parameterX + i, parameterY);
		break;

	case 180:
		parameterX = arr[0].getX() + 1 ;
		parameterY = arr[0].getY() - 1;

		for (int i = 0; i < 3; i++)
			arr[i + 1].setCoordinate(parameterX, parameterY + i);
		break;

	case 270:
		parameterX = arr[0].getX() - 1 ;
		parameterY = arr[0].getY() + 1;

		for (int i = 0; i < 3; i++)
			arr[i + 1].setCoordinate(parameterX + i, parameterY);
		break;
	}

	updateAngle();
	draw();
}

//======================================================================================================>

void Plus::updateAngle()
{ // The function update the shape's rotation's angle.

	angle = ((angle + 90) % 360);
}
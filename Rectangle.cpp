#include "Rectangle.h"

Rectanglee::Rectanglee(unsigned char ch)
{ // Rectanglee's c'tor

	size = 4;
	arr = new Point[size]{ { ch, 38, 5 },{ ch, 39, 5 },{ ch, 40, 5 },{ ch, 41, 5 } };
	typeColor = PURPLE;
	this->ch = ch;
	angle = 0;
}

//======================================================================================================>

void Rectanglee::draw(unsigned char ch) const
{ // Prints the shape on the screen.

	changeColor(typeColor);
	for (int i = 0; i < size; i++)
		arr[i].draw(ch);
}

//======================================================================================================>

void Rectanglee::move(eDirection direction)
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

bool Rectanglee::canMove(eDirection direction, bool& running, const short mat[22][12])
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
		short direct1 = 0, direct2 = 0;
		if (canRotate(direct1, direct2, mat))
			rotateRectangle(direct1, direct2);

		return false;
		break;



	}
	return true;
}

//======================================================================================================>

void Rectanglee::moveDownAsPossible(bool& running, const short mat[22][12])
{ // The function drops the shape down as possible.

	while (canMove(DOWN, running, mat))
	{
		move(DOWN);
		Sleep(20);

	}
	running = false;
}

//======================================================================================================>

bool Rectanglee::canRotate(short& direct1, short& direct2, const short mat[22][12])
{  // The function returns true if the shape can rotate, else returns false.

	int rowLocation, colLocation;
	switch (angle)
	{
	case 0:
	case 180:
		rowLocation = arr[0].getY();
		colLocation = arr[0].getX() - START_COL + 1;
		for (int i = 1; i < 4; i++)
		{
			if (mat[rowLocation - i][colLocation] != 0)
				break;
			direct1++;
		}
		if (direct1 != 3)
		{
			for (int i = 1; i < 4; i++)
			{
				if (mat[rowLocation + i][colLocation] != 0)
					break;
				direct2++;
			}
		}
		if (direct1 + direct2 >= 3)
			return true;

		return false;
		break;

	case 90:
	case 270:
		rowLocation = arr[3].getY();
		colLocation = arr[3].getX() - START_COL + 1;

		for (int i = 1; i < 4; i++)
		{
			if (mat[rowLocation][colLocation + i] != 0)
				break;
			direct1++;
		}
		if (direct1 != 3)
		{
			for (int i = 1; i < 4; i++)
			{
				if (mat[rowLocation][colLocation - i] != 0)
					break;
				direct2++;
			}
		}

		if (direct1 + direct2 >= 3)
			return true;
		return false;
	}
	return true;
}

//======================================================================================================>

void Rectanglee::rotateRectangle(short& direct1, short& direct2)
{  // The function rotates the shape 90 degrees

	draw(' ');
	switch (angle)
	{
	case 0:
	case 180:
		for (int i = 0; i < 4; i++)
		{
			arr[i].setCoordinate(arr[0].getX(), arr[i].getY() - direct1);
			direct1--;
		}
		break;

	case 90:
	case 270:
		for (int i = 0; i < 4; i++)
		{
			arr[i].setCoordinate(arr[i].getX() + direct1 - 3, arr[3].getY());
			direct1++;
		}

	}
	draw(ch);
	updateAngle();
}

//======================================================================================================>

void Rectanglee::updateAngle()
{ // The function update the shape's rotation's angle.

	angle = ((angle + 90) % 360);
}


//=====================

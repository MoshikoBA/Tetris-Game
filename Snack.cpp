#include "Snack.h"

Snack::Snack(unsigned char ch)
{ // Snack's c'tor
	size = 4;
	arr = new Point[size]{ { ch, 39, 4 },{ ch, 40, 4 },{ ch, 40, 5 },{ ch, 41, 5 } };
	typeColor = RED;
	this->ch = ch;

	angle = 0;
}

//======================================================================================================>

void Snack::draw(unsigned char ch) const
{ // Prints the shape on the screen.

	changeColor(typeColor);
	for (int i = 0; i < size; i++)
		arr[i].draw(ch);
}

//======================================================================================================>

void Snack::move(eDirection direction)
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

bool Snack::canMove(eDirection direction, bool& running, const short mat[22][12])
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
			rotateSnack();

		return false;
	}
	return true;
}

//======================================================================================================>

void Snack::moveDownAsPossible(bool& running, const short mat[22][12])
{ // The function drops the shape down as possible.

	while (canMove(DOWN, running, mat))
	{
		move(DOWN);
		Sleep(20);
	}
	running = false;
}

//======================================================================================================>

bool Snack::canRotate(const short mat[22][12])
{  // The function returns true if the shape can rotate, else returns false.

	switch (angle)
	{
	case 0:
	case 180:
		if ((mat[arr[0].getY() + 1][arr[0].getX() - START_COL + 1]) ||
			(mat[arr[0].getY() + 1][arr[0].getX() - START_COL]) ||
			(mat[arr[0].getY() + 2][arr[0].getX() - START_COL]))
			return false;
		break;

	case 90:
	case 270:
		if ((mat[arr[0].getY()][arr[0].getX() - START_COL + 1]) ||
			(mat[arr[0].getY() + 1][arr[0].getX() - START_COL + 3]))
			return false;
		break;
	}

	return true;
}

//======================================================================================================>

void Snack::rotateSnack()
{  // The function rotates the shape 90 degrees

	draw(' ');
	int parameterX = arr[0].getX();
	int parameterY = arr[0].getY();

	switch (angle)
	{
	case 0:
	case 180:
		arr[1].setCoordinate(parameterX, parameterY + 1);
		arr[2].setCoordinate(parameterX - 1, parameterY + 1);
		arr[3].setCoordinate(parameterX - 1, parameterY + 2);
		break;

	case 90:
	case 270:
		arr[1].setCoordinate(parameterX+1, parameterY);
		arr[2].setCoordinate(parameterX + 1, parameterY + 1);
		arr[3].setCoordinate(parameterX + 2, parameterY + 1);

		break;
	}

	updateAngle();
	draw();
}

//======================================================================================================>

void Snack::updateAngle()
{ // The function update the shape's rotation's angle.

	angle = ((angle + 90) % 360);
}
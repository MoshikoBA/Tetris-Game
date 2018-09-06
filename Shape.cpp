#include "Shape.h"


Shape::Point::Point(unsigned char ch, int x, int y)
{  // Point class's constructor.

	this->x = x;
	this->y = y;
	this->ch = ch;
}

//======================================================================================================>

void Shape::Point::draw(unsigned char ch) const
{ // prints the point on the screen.

	gotoxy(x, y);
	cout << ch;
}

//======================================================================================================>

void Shape::Point::setCoordinate(int x, int y)
{ // set the point's coordinate.

	this->x = x;
	this->y = y;
}

//======================================================================================================>

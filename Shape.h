#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Gotoxy.h"
#include "Design.h"
#include <Windows.h>

using namespace std;
#include <iostream>

const int START_ROW = 6;
const int START_COL = 35;
const int LAST_COL = 44;
const int LAST_ROW = 20;


class Shape {

public:
	enum eColor { BLUE = 1, GREEN = 2, LIGHT_BLUE = 3, RED = 4, PURPLE = 5, YELLOW = 6, WHITE = 7 };
	enum eDirection { LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
	
protected:

	class Point
	{
	private:
		int x;
		int y;
		unsigned char ch;

	public:
		Point(unsigned char  ch = '*', int x = 1, int y = 1);
		void draw(unsigned char ch = '*') const;
		void setCoordinate(int x, int y);
		int getX() { return x; };  // get the x coordinate.
		int getY() { return y; };  // get the y coordinate.
	};

	Point* arr;
	eColor typeColor;
	short angle;
	short size;
	unsigned char ch;

	friend class Tetris;

public:
	Shape() = default;
	virtual ~Shape() = default;  // Shape class destructor.
	virtual unsigned char getChar() const = 0; // gets the Shape's unsigned char.
	virtual short getSize() const = 0;  // gets the Shape's size.(how many points)
	virtual void draw(unsigned char ch = 'X') const = 0;
	virtual void move(eDirection direction) = 0;
	virtual void moveDownAsPossible(bool& running, const short mat [22][12]) = 0;
	virtual bool canMove(eDirection direction, bool& running , const short mat [22][12] ) = 0;
};



#endif

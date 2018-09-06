#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Shape.h"

class Square : public Shape
{
public:

	Square(unsigned char ch);
	~Square() { delete[]arr; }
	unsigned char getChar() const { return ch; }
	short getSize() const { return size; }
	void draw(unsigned char ch = 'X') const;
	void move(eDirection direction);
	void moveDownAsPossible(bool& running, const short mat[22][12]);
	bool canMove(eDirection direction, bool& running, const short mat[22][12]);

};


#endif
#ifndef _BOMB_H_
#define _BOMB_H_

#include "Shape.h"


class Bomb : public Shape
{
public:

	Bomb(unsigned char ch);
	~Bomb() { delete arr; }
	unsigned char getChar() const { return ch; }
	short getSize() const { return size; }
	void draw(unsigned char ch = '@') const;
	void move(eDirection direction);
	void moveDownAsPossible(bool& running, const short mat [22][12] );
	bool canMove(eDirection direction, bool& running, const short mat [22][12] );
};







#endif
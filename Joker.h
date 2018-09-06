#ifndef _JOKER_H_
#define _JOKER_H_

#include "Shape.h"

class Joker : public Shape
{
public:
	Joker(unsigned char ch);
	~Joker() { delete arr; }
	unsigned char getChar() const { return ch; }
	short getSize() const { return size; }
	void draw(unsigned char ch = 'X') const;
	void move(eDirection direction) {}
	void moveDownAsPossible(bool& running, const short mat [22][12] );
	bool canMove(eDirection direction, bool& running, const short mat[22][12]);
};










#endif

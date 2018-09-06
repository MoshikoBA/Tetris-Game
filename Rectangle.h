#ifndef _Rectanglee_H_
#define _Rectanglee_H_

#include "Shape.h"

class Rectanglee : public Shape
{
public:

	Rectanglee(unsigned char ch);
	~Rectanglee() { delete[]arr; }
	unsigned char getChar() const { return ch; }
	short getSize() const { return size; }
	void draw(unsigned char ch = '*') const;
	void move(eDirection direction);
	void moveDownAsPossible(bool& running, const short mat[22][12]);
	bool canMove(eDirection direction, bool& running, const short mat[22][12]);

private:

	bool canRotate(short& direct1, short& direct2, const short mat[22][12]);
	void rotateRectangle(short& direct1, short& direct2);
	void updateAngle();



};

#endif;

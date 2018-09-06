#ifndef _SNACK_H_
#define _SNACK_H_

#include "Shape.h"

class Snack : public Shape
{
public:

	Snack(unsigned char ch);
	~Snack() { delete[]arr; }
	unsigned char getChar() const { return ch; }
	short getSize() const { return size; }
	void draw(unsigned char ch = 'X') const;
	void move(eDirection direction);
	void moveDownAsPossible(bool& running, const short mat[22][12]);
	bool canMove(eDirection direction, bool& running, const short mat[22][12]);

private:
	bool canRotate(const short mat[22][12]);
	void rotateSnack();
	void updateAngle();
};


#endif



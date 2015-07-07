#ifndef CAO_H
#define CAO_H
#include  "Piece.h"

class Cao :
	public Piece
{
public:
	virtual bool init();
	CREATE_FUNC(Cao);
	Cao();

	virtual void getSize(int& width, int& height);
	virtual bool Move();
};

#endif
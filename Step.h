#ifndef STEP_H
#define STEP_H
#include"def.h"
class Step :
	public Object
{
public:
	int operID;
	float preX;
	float preY;
	float afteX;
	float afteY;
	Step();
	static Step* create(int operID, float preX, float preY, float aftX, float aftY);
	Step* comeBack();
};

#endif
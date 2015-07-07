#include "Step.h"

Step::Step()
{
}

Step* Step::create(int operID, float preX, float preY, float aftX, float aftY)
{
	Step* s = new Step;
	s->preX = preX;
	s->preY = preY;
	s->afteX = aftX;
	s->afteY = aftY;
	s->operID = operID;  
	return s;
}

Step* Step::comeBack()
{
	Step* s = new Step();
	s->afteX = this->preX;
	s->afteY = this->preY;
	s->preX = this->afteX;
	s->preY = this->afteY;
	s->operID = operID;
	return s;
}
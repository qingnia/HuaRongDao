#include "Cao.h"

Cao::Cao()
{
}


bool Cao::init()
{
	_type = TYPE::Caocao;
	_x = 2;
	_y = 3;
	_width = 2;
	_height = 2;
	return true;
}

void Cao::getSize(int& width, int& height)
{
	width = this->_width;
	height = this->_height;
}

bool Cao::Move()
{
	return true;
}

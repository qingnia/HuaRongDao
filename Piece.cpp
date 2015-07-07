#include "Piece.h"

Piece::Role Piece::role[7] = {
	{ TYPE::Caocao, 1, 3, 2, 2, CAOCAO },
	{ TYPE::Guanyu, 1, 2, 2, 1, GUANYU },
	{ TYPE::Huangzhong, 3, 1, 1, 2, HUANGZHONG },
	{ TYPE::Machao, 3, 3, 1, 2, MACHAO },
	{ TYPE::Zhangfei, 0, 3, 1, 2, ZHANGFEI },
	{ TYPE::Zhaoyun, 0, 1, 1, 2, ZHAOYUN },
	{ TYPE::Zu, 0, 0, 1, 1, ZU }
};

Piece::Piece()
{
}

Piece* Piece::create(int id)
{
	Piece* pRet = new Piece();
	if (pRet && pRet->init(id))
	{ 
	pRet->autorelease();
	return pRet; 
	} 
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Piece::init(int id)
{
	_id = id;
	Role r = Piece::role[_id];
	Sprite::initWithFile(r._photoName);
	_width = r.width;
	_height = r.height;
	_x = r.x;
	_y = r.y;
	return true;
}

Vec2 Piece::getRealPos()
{
	return Vec2(_x * 120, _y * 100);
}

Rect* Piece::getRectangle()
{
	return new Rect(_x, _y, _width, _height);
}

bool Piece::virtualMove()
{
	switch (getDir())
	{
	case Dir::Up:
		setY(getY() + 1);
		break;
	case Dir::Down:
		setY(getY() - 1);
		break;
	case Dir::Left:
		setX(getX() - 1);
		break;
	case Dir::Right:
		setX(getX() + 1);
		break;
	default:
		break;
	}
	return true;
}

void Piece::flashRun()
{
	MoveTo* mt = MoveTo::create(0.5, getRealPos() + ORIGIN);
	this->runAction(mt);
}

void Piece::virtualComeBack()
{
	switch (getDir())
	{
	case Dir::Up:
		setDir(Dir::Down);
	case Dir::Down:
		setDir(Dir::Up);
	case Dir::Left:
		setDir(Dir::Right);
	case Dir::Right:
		setDir(Dir::Left);
	default:
		break;
	}
}
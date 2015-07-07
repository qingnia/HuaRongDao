#include "AI.h"


AI::AI(GameScene* gs) :_game(gs)
{
	vec = Vector<Step*>(100);
	pieceIndex = new int[100]();
	count = 0;
	vecIndex = 0;
	nullVec = new float[][2];
}

bool AI::calAlg()
{
	return getNextStep(pieceIndex[count], vecIndex);
}

int AI::getNextStep(int& index,int& nullVecIndex)
{
	count++;
	int i = 0;
	int state = 2;
	if (1 == _game->_p[0]->getX() && 0 == _game->_p[0]->getY())
		state = 0;
	for (float x = 0.5; x < 3; x++)
	{
 		for (float y = 0.5; y < 4; y++)
		{
			if (_game->isNull(x, y))
			{
				nullVec[nullVecIndex + i][0] = x;
				nullVec[nullVecIndex + i][1] = y;
				i++;
			}
		}
	}
	for (index; index < 10; index++)
	{
		if (_game->canMove(index, Vec2(nullVec[nullVecIndex][0],nullVec[nullVecIndex][1])))
		{
			state = 1;
			float preX = _game->_p[index]->getX() + 0.5;
			float preY = _game->_p[index]->getX() + 0.5;
			_game->_p[index]->virtualMove();
			float afteX = _game->_p[index]->getX() + 0.5;
			float afteY = _game->_p[index]->getX() + 0.5;
			vec.pushBack(Step::create(index, preX, preY, afteX, afteY));
			break;
		}
	}
	if (2 == state)
	{
		for (index; index < 10; index++)
		{
			if (_game->canMove(index, Vec2(nullVec[nullVecIndex + 1][0], nullVec[nullVecIndex + 1][1])))
			{
				state = 1;
				float preX = _game->_p[index]->getX() + 0.5;
				float preY = _game->_p[index]->getX() + 0.5;
				_game->_p[index]->virtualMove();
				float afteX = _game->_p[index]->getX() + 0.5;
				float afteY = _game->_p[index]->getX() + 0.5;
				vec.pushBack(Step::create(index, preX, preY, afteX, afteY));
			}
			break;
		}
	}
	if (0 == state)
	{
		return true;
	}
	if (1 == state)
	{
		nullVecIndex = nullVecIndex + 2;
		getNextStep(this->pieceIndex[count], nullVecIndex);
	}
	if (2 == state)
	{
		nullVecIndex = nullVecIndex - 2;
		_game->_p[index]->virtualComeBack();
		_game->_p[index]->virtualMove();
		vec.popBack();
		getNextStep(index, nullVecIndex);
	}
	return state;
}

AI::~AI()
{
}

#include "GameScene.h"

GameScene::GameScene()
{
}

Scene* GameScene::createScene()
{
	Scene* s = Scene::create();
	GameScene* layer = GameScene::create();
	s->addChild(layer);
	return s;
}

bool GameScene::init()
{
	Origin = Vec2(200, 0); 
	initDesk();
	initPiece();
	initMenu();
	return true;
}

void GameScene::initDesk()
{
	Sprite* desk = Sprite::create(DESK);
	desk->setAnchorPoint(Vec2::ZERO);
	desk->setPosition(Origin);
	addChild(desk);
}

void GameScene::initPiece()
{
	for (int i = 0; i < 6; i++)
	{
		_p[i] = Piece::create(i);
	}
	for (int i = 0; i < 4; i++)
	{
		_p[i + 6] = Piece::create(6);
		_p[i + 6]->setX(i);
		_p[i + 6]->setY((i % 3) == 0 ? 0 : 1);
	}
	for (int i = 0; i < 10; i++)
	{
		_p[i]->setAnchorPoint(Vec2::ZERO);
		addChild(_p[i]);
		_p[i]->setPosition(_p[i]->getRealPos() + Origin);
	}
	setTouchFunc();
}

void GameScene::setTouchFunc()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
 
bool GameScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Vec2 vec = pTouch->getLocation();
	TransToVirtulePos(vec);
	if (vec.x < 0 || vec.x >= 4 || vec.y < 0 || vec.y >= 5)
		return false;
	int id = getClickPos(vec);
	if (-1 == id && !getIsReady())
		return false;
	if (-1 != id)
	{
		setSelectID(id);
		return false;
	}
	if (canMove(getSelectID(), vec))
	{
		_p[getSelectID()]->virtualMove();
		_p[getSelectID()]->flashRun();
	}
	return true; 
}

void GameScene::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	return;
}
void GameScene::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	return;
}

int GameScene::getClickPos(Vec2& vec)
{
	for (int i = 0; i < 10; i++)
	{
		if (_p[i]->getRectangle()->containsPoint(vec))
			return i;
		continue;
	}
	return -1;
}

bool GameScene::isNull(float x, float y)
{
	if (getClickPos(Vec2(x, y)) == -1)
		return true;
	return false;
}

bool GameScene::canMove(int id, Vec2& vec)
{
	if (id > 5)
	{
		if (vec.x < _p[id]->getX() && vec.x > _p[id]->getX() - 1)
		{
			_p[id]->setDir(Dir::Left);
			return true;
		}
		if (vec.x > _p[id]->getX() + 1 && vec.x < _p[id]->getX() + 2)
		{
			_p[id]->setDir(Dir::Right);
			return true;
		}
		if (vec.y < _p[id]->getY() && vec.y > _p[id]->getY() - 1)
		{
			_p[id]->setDir(Dir::Down);
			return true;
		}
		if (vec.y > _p[id]->getY() + 1 && vec.y < _p[id]->getY() + 2)
		{
			_p[id]->setDir(Dir::Up);
			return true;
		}
		return false;
	}
	float difY = vec.y - _p[id]->getY();
	if (vec.x < _p[id]->getX() && vec.x > _p[id]->getX() - 1)
	{
		if (vec.y < _p[id]->getY() || vec.y > _p[id]->getY() + _p[id]->getHeight())
			return false;
		if (1 == _p[id]->getHeight())
		{
			_p[id]->setDir(Dir::Left);
			return true;
		}
		if (2 == _p[id]->getHeight())
			if (isNull(vec.x, _p[id]->getY() + 0.5) && isNull(vec.x, _p[id]->getY() + 1.5))
			{
				_p[id]->setDir(Dir::Left);
				return true;
			}
			else
				return false;
	}
	if (vec.x > _p[id]->getX() + _p[id]->getWidth() && vec.x < _p[id]->getX() + _p[id]->getWidth() + 1)
	{
		if (vec.y < _p[id]->getY() || vec.y > _p[id]->getY() + _p[id]->getHeight())
			return false;
		if (1 == _p[id]->getHeight())
		{
			_p[id]->setDir(Dir::Right);
			return true;
		}
		if (2 == _p[id]->getHeight())
			if (1 == _p[id]->getWidth())
			{
				if (isNull(vec.x, _p[id]->getY() + 1.5) && isNull(vec.x, _p[id]->getY() + 1.5))
				{
					_p[id]->setDir(Dir::Right);
					return true;
				}
			}
			else if (isNull(vec.x, _p[id]->getY() + 0.5) && isNull(vec.x, _p[id]->getY() + 1.5))
			{
				_p[id]->setDir(Dir::Right);
				return true; 
			}
			else
				return false; 
	}
	if (vec.y < _p[id]->getY() && vec.y > _p[id]->getY() - 1)
	{
		if (vec.x < _p[id]->getX() || vec.x > _p[id]->getX() + _p[id]->getWidth())
			return false;
		if (1 == _p[id]->getWidth())
		{
			_p[id]->setDir(Dir::Down);
			return true;
		}
		if (2 == _p[id]->getWidth())
			if (isNull(vec.x, _p[id]->getY() - 0.5) && isNull(vec.x + 1, _p[id]->getY() - 0.5))
			{
				_p[id]->setDir(Dir::Down);
				return true;
			}
			else
				return false;
	}
	if (vec.y > _p[id]->getY() + _p[id]->getHeight() && vec.y < _p[id]->getY() + _p[id]->getHeight() + 1)
	{
		if (vec.x < _p[id]->getX() || vec.x > _p[id]->getX() + _p[id]->getWidth())
			return false;
		if (1 == _p[id]->getWidth())
		{
			_p[id]->setDir(Dir::Up);
			return true;
		}
		if (2 == _p[id]->getWidth())
			if (1 == _p[id]->getHeight())
			{
				if (isNull(vec.x, _p[id]->getY() + 1.5) && isNull(vec.x + 1, _p[id]->getY() + 1.5))
				{
					_p[id]->setDir(Dir::Up);
					return true;
				}
			}
			else if (isNull(vec.x, _p[id]->getY() + 2.5) && isNull(vec.x + 1, _p[id]->getY() + 2.5))
			{
				_p[id]->setDir(Dir::Up);
				return true;
			}
			else
				return false;
	} 
	return false;
}

void GameScene::TransToVirtulePos(Vec2& vec)
{
	vec = vec - Origin;
	vec.x = vec.x / 120;
	vec.y = vec.y / 100;
}

void GameScene::initMenu()
{
	Menu* menu = Menu::create();
	MenuItemFont* autoCal = MenuItemFont::create("aotoCal",this,menu_selector(GameScene::calRoutine));
	menu->addChild(autoCal);
	addChild(menu);
	autoCal->setPosition(Origin + Vec2(20, 20));
}

void GameScene::calRoutine(Ref*)
{
	this->_ai = new AI(this);
	bool ret = _ai->calAlg();
	cocos2d::log("ret is :%d", ret);
}
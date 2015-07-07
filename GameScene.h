#ifndef GAMESCENE_H
#define GAMESCENE_H
#include"def.h"
#include "Piece.h"
#include"Step.h"
#include"AI.h"

class AI;
#define DESK "desk.jpg"

class GameScene :
	public Layer
{
	Vec2 Origin;
	AI* _ai;

	CC_SYNTHESIZE(bool, _isReady, IsReady);
	CC_SYNTHESIZE(int, _selectID, SelectID);

	void initDesk();
	void initPiece();
	void initMenu();
	int getClickPos(Vec2& vec);
	bool canMove(int id, Vec2& vec);
	bool inline isNull(float x, float y);
	void TransToVirtulePos(Vec2& vec);

	void setTouchFunc();
	bool GameScene::onTouchBegan(Touch *pTouch, Event *pEvent);
	void GameScene::onTouchMoved(Touch *pTouch, Event *pEvent);
	void GameScene::onTouchEnded(Touch *pTouch, Event *pEvent);

	void calRoutine(Ref*);

public:
	Piece* _p[10];

	CREATE_FUNC(GameScene);
	GameScene();
	static Scene* createScene();
	bool init();
};

#endif
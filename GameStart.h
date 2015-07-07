#ifndef GAMESTART_H
#define GAMEATART_H
#include "def.h"
#include "GameScene.h"
#define BEGIN "Begin.jpg"

class GameStart :
	public Layer
{
public:
	static Scene* createScene();
	bool init();
	CREATE_FUNC(GameStart);

	void initStartScene();

	void GameStart::menuGameStart(Ref* pSender);
	GameStart();
};

#endif
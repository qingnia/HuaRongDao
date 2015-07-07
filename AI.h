#ifndef AI_H
#define AI_H
#include"Step.h"
#include"GameScene.h"

class GameScene;
class Step;

class AI
{
	Vector<Step*> vec;
	GameScene* _game;
	int* pieceIndex;
	int count;
	float(*nullVec)[2];
	int vecIndex;
	
	int getNextStep(int& i, int& nullVecIndex);
public:
	
	AI(GameScene* gs);
	bool calAlg();
	~AI();
};

#endif
#ifndef PIECE_H
#define PIECE_H
#include "def.h"

#define CAOCAO "caoCao.jpg"
#define GUANYU "guanYu.jpg"
#define ZHAOYUN "zhaoYun.jpg"
#define ZHANGFEI "zhangFei.jpg"
#define HUANGZHONG "huangZhong.jpg"
#define MACHAO "maChao.jpg"
#define ZU "soldiers.jpg"
#define ORIGIN Vec2(200,0)

class Piece :
	public Sprite
{
	static Vec2 Origin;
	enum TYPE
	{
		Caocao, Guanyu, Zhangfei, Zhaoyun, Machao, Huangzhong, Zu
	};
	static struct Role
	{
		TYPE _type;
		int x;
		int y;
		int width;
		int height;
		char* _photoName;
	}role[7];

	CC_SYNTHESIZE(int, _x, X);
	CC_SYNTHESIZE(int, _y, Y);
	CC_SYNTHESIZE(int, _width, Width);
	CC_SYNTHESIZE(int, _height, Height);
	CC_SYNTHESIZE(int, _id, Id);
	CC_SYNTHESIZE(Role, _myrole, myRole);
	CC_SYNTHESIZE(bool, _selected, Selected);
	CC_SYNTHESIZE(Dir, _direction, Dir);

	Vec2 getRealPos();
public:
	static Piece* create(int id);
	virtual	bool init(int id);
	Piece();

	Rect* getRectangle();
	bool virtualMove();
	void virtualComeBack();
	void flashRun();
};

#endif
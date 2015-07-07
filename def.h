#ifndef DEF_H
#define DEF_H

#include"cocos2d.h"
USING_NS_CC;

#define winSize Director::getInstance()->getWinSize()

enum Dir { Up, Down, Left, Right };

static void replaceLayer(Layer* layer)
{
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

static void runWithLayer(Layer* layer)
{
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->runWithScene(scene);
}

static Sprite* addSprite(Node* parent, const char* filename, int zorder = 0, int tag = 0)
{
	Sprite* sprite = Sprite::create(filename);
	parent->addChild(sprite);
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	sprite->setZOrder(zorder);
	sprite->setTag(tag);
	return sprite;
}

static void scaleToFitWindow(Node* node)
{
	node->setScaleX(winSize.width / node->getContentSize().width);
	node->setScaleY(winSize.height / node->getContentSize().height);
}

static void scaleToFitWindowY(Node* node, float margin = 0.0f)
{
	node->setScale((winSize.height - margin * 2) / node->getContentSize().height);
}

#endif
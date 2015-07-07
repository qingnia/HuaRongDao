#include "GameStart.h"

GameStart::GameStart()
{
}

Scene* GameStart::createScene()
{
	Scene* scene = Scene::create();
	auto layer = GameStart::create();
	scene->addChild(layer);
	return scene;
}

bool GameStart::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initStartScene();
	return true;
}

void GameStart::initStartScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto StartItem = MenuItemImage::create(
		BEGIN,
		BEGIN,
		CC_CALLBACK_1(GameStart::menuGameStart, this));

	StartItem->setPosition(Vec2(origin.x + visibleSize.width - StartItem->getContentSize().width / 2,
		origin.y + StartItem->getContentSize().height / 2));

	auto menu = Menu::create(StartItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void GameStart::menuGameStart(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->replaceScene(GameScene::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

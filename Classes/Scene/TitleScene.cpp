
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "TitleScene.h"
#include "GameScene.h"//遷移先のシーンをインクルード

#else

#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"//遷移先のシーンをインクルード

#endif

USING_NS_CC;
using namespace TapGun;

/*
タイトルシーン
タッチするとゲームシーンに遷移するようにしていますが、現在は使用していません
*/

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener -> setSwallowTouches( _swallowsTouches);
	listener -> onTouchBegan = CC_CALLBACK_2( TitleScene::onTouchBegan, this);
	_eventDispatcher -> addEventListenerWithSceneGraphPriority( listener, this);
   
	return true;
}

bool TitleScene::onTouchBegan( Touch *touch, Event *unused_event)
{
	auto scene = GameScene::CreateScene();
	auto tran = TransitionCrossFade::create( 1, scene);
	Director::getInstance() -> replaceScene( tran);
	return true;
}
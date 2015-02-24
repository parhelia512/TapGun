
#include <sstream>
#include <iostream>
#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "Define.h"
//#include "Main.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"
#include "Errorfunc.h"
#include "Sound.h"
#include "UI.h"

#else

#include "Base/UI.h"
#include "Base/Sprite3D.h"
#include "System/Directory.h"
#include "System/Errorfunc.h"
#include "System/Sound.h"

#endif

USING_NS_CC;
//using namespace ADX2;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

Sprite3D* sprite3d;

Scene* Test::createScene()
{
	SystemValue::windowSize = Director::getInstance() -> getVisibleSize();
	SystemValue::origin = Director::getInstance() -> getVisibleOrigin();
	auto scene = Scene::create();
	auto layer = Test::create();
	scene -> addChild( layer);
	return scene;
}

bool Test::init()
{
	if ( !Layer::init()) { return false; }

	auto cache = SpriteFrameCache::getInstance();
	
	cache -> addSpriteFramesWithFile( "P_Hit.plist");
	cache -> addSpriteFramesWithFile( "E_Hit.plist");
	
	auto billboard =  BillBoard::create();
	
	
	auto sprite = Sprite::createWithSpriteFrameName( "E_Hit01.png");
//	sprite -> setPosition( Vec2( 640, 500));
	
	auto animation = Animation::create();
	
	for( int i = 0; i < 8; i++)
	{
		char buf[256];
		sprintf( buf, "E_Hit%02d.png", i + 1);
		animation -> addSpriteFrame( cache -> getSpriteFrameByName( buf));
	}
	

	
	animation -> setDelayPerUnit( 0.05f);
	animation -> setRestoreOriginalFrame( true);
	
	auto action = Animate::create( animation);
	sprite -> runAction( RepeatForever::create( action));
	
	billboard -> setPosition3D( Vec3( 1, 0.5, 1));
	billboard -> addChild( sprite);
	
	//現在はタッチイベントのリスナーをここに用意しています
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	listener = EventListenerTouchOneByOne::create();
	listener -> onTouchBegan = CC_CALLBACK_2( Test::onTouchBegan, this);
	listener -> onTouchMoved = CC_CALLBACK_2( Test::onTouchMoved, this);
	listener -> onTouchEnded = CC_CALLBACK_2( Test::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
	schedule( schedule_selector(Test::moveTime), 0.016f);

	sprite3d = Sprite3D::create( "enemy.c3b");
	sprite3d -> setPosition( 640, 200);
	sprite3d -> setRotation3D( Vec3( 0.0f, 60.0f, 0.0f));
	sprite3d -> setScale( 300.0f);
	sprite -> setScale( 0.003f);
	sprite3d -> addChild( billboard);
	addChild( sprite3d);

	return true;
}

void Test::update( float delta)
{
//	Manager::getInstance() -> update();
	static int count = 0;
	sprite3d -> setRotation3D(( Vec3( 0.0f, count, 0.0f)));
	count++;
}

void Test::moveTime( float delta)
{

}

bool Test::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return true;
}


void Test::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
}



void Test::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
}
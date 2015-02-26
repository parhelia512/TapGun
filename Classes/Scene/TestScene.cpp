
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

	//現在はタッチイベントのリスナーをここに用意しています
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	listener = EventListenerTouchOneByOne::create();
	listener -> onTouchBegan = CC_CALLBACK_2( Test::onTouchBegan, this);
	listener -> onTouchMoved = CC_CALLBACK_2( Test::onTouchMoved, this);
	listener -> onTouchEnded = CC_CALLBACK_2( Test::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
	schedule( schedule_selector(Test::moveTime), 0.016f);

//	Manager::initialize();

//	_cueSheet = CueSheet::create("sample.acf", "sample.acb");
//	_cueSheet->playCueByID( 0);

	return true;
}

void Test::update( float delta)
{
//	Manager::getInstance() -> update();
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

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "TitleScene.h"
#include "CreditSceneScene.h"

#else

#include "Scene/TitleScene.h"
#include "Scene/CreditScene.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

Scene* CreditScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CreditScene::create();
	scene -> addChild( layer);
	return scene;
}

bool CreditScene::init()
{
	if ( !Layer::init()) { return false; }

	auto visibleSize = Director::getInstance() -> getVisibleSize();

	//現在はタッチイベントのリスナーをここに用意しています
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	listener = EventListenerTouchOneByOne::create();
	listener -> onTouchBegan = CC_CALLBACK_2( CreditScene::onTouchBegan, this);
	listener -> onTouchMoved = CC_CALLBACK_2( CreditScene::onTouchMoved, this);
	listener -> onTouchEnded = CC_CALLBACK_2( CreditScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto label = Label::createWithTTF( "Credit Scene", "fonts/arial.ttf", 60);
	label -> setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2));
	addChild( label, 1);

	scheduleUpdate();
	schedule( schedule_selector( CreditScene::moveTime), 0.016f);

	return true;
}

void CreditScene::update( float delta)
{
}

void CreditScene::moveTime( float delta)
{

}

bool CreditScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return true;
}


void CreditScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
}

void CreditScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
}
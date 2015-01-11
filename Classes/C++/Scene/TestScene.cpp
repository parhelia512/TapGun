
#include <sstream>
#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Errorfunc.h"
#include "Sound.h"

#else

#include "C++/System/Errorfunc.h"
#include "C++/System/Sound.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

Sprite3D* sprite3D;

Scene* Test::createScene()
{
	SystemValue::windowSize = Director::getInstance() -> getVisibleSize();
	SystemValue::origin = Director::getInstance() -> getVisibleOrigin();
	auto scene = Scene::create();
	auto layer = Test::create();
	scene -> addChild(layer);
	return scene;
}

bool Test::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	setCocos();
	auto bg = LayerColor::create( Color4B::WHITE, SystemValue::windowSize.width, SystemValue::windowSize.height);
//	this -> addChild( bg, 0);
	auto sound = Sound::getInstance();

	sprite3D = Sprite3D::create( "BBOX");//, "BBOX.texture");
	sprite3D -> setTexture( "01.png");
//	sprite3D -> setShaderFile( "toon");
	auto animation = Animation3D::create( "Graph/Models/test.c3t");
	auto animate = Animate3D::create( animation);
//	sprite3D -> runAction( RepeatForever::create( animate));
//	sprite3D -> startAnimationLoop("Test");
	sprite3D -> setPosition3D( Vec3( SystemValue::windowSize.width / 2, SystemValue::windowSize.height / 2, 0));
	sprite3D -> setRotation3D( Vec3( 270.0f, 90.0f, 0.0f));
	sprite3D -> setScale( 10.0f);
	this -> addChild( sprite3D);
	
	return true;
}

void Test::update( float delta)
{
//	this -> scheduleUpdate();
}

void Test::moveTime( float delta)
{
//	this -> schedule(schedule_selector(Test::moveTime), 0.016f);
}

void Test::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	Director::getInstance() -> end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Test::setCocos( void)
{
	auto closeItem = MenuItemImage::create( "CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1( Test::menuCloseCallback, this));
	closeItem -> setPosition( Vec2( SystemValue::origin.x + SystemValue::windowSize.width - closeItem->getContentSize().width/2 ,
								SystemValue::origin.y + closeItem->getContentSize().height/2));
	auto menu = Menu::create( closeItem, NULL);
	menu -> setPosition( Vec2::ZERO);
	this -> addChild( menu, 1);
	
	auto label = LabelTTF::create( "Hello World", "Arial", 24);
	label -> setPosition( Vec2( SystemValue::origin.x + SystemValue::windowSize.width/2,
							SystemValue::origin.y + SystemValue::windowSize.height - label->getContentSize().height));
	this -> addChild( label, 1);
}
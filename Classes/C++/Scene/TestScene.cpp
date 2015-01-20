
#include <sstream>
#include <iostream>
#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"
#include "Errorfunc.h"
#include "Sound.h"

#else

#include "C++/Base/Sprite3D.h"
#include "C++/System/Directory.h"
#include "C++/System/Errorfunc.h"
#include "C++/System/Sound.h"

#endif

//#define CAMERA3D//3DÂ∫ßÊ®ô„Åß‰ΩúÊ•≠„Åó„Åü„ÅÑ„Å®„Åç„Å´‰ΩøÁî®„Åó„Å¶‰∏ã„Åï„ÅÑ

USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

cocos2d::Layer* Test::lay;
cocos2d::Camera* Camera3D;

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
	if ( !Layer::init() )
	{
		return false;
	}
	setCocos();
	lay = this;
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto sprite3D = _Sprite3D::create( "enemy", "Enemy.anime");
#else
	//auto sprite3D = Sprite3D::create( "stage.c3t");//, "bock_gurand2.png");
	auto sprite3D = _Sprite3D::create("enemy/enemy", "Enemy.anime");

#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FILE *fp;
	auto file = FileUtils::getInstance();
	
	AAssetManager* mgr = FileUtilsAndroid::assetmanager;
	AAssetDir* assetDir = AAssetManager_openDir( mgr, "Graph");
	const char* filePath = AAssetDir_getNextFileName( assetDir);
//	const char* filePath = "";
//	string filePath = getFilesDir();
//	string filePath = "Tap-Gun/Resources/Parameter/Animation/Enemy.anime";
//	file -> fullPathForFilename( filePath.c_str());
//	fp = fopen( filePath.c_str(), "r");
//	if( fp == NULL)
	if( strlen(filePath))
	{
		auto label = LabelTTF::create( "Hello World", "Arial", 24);
		label -> setPosition( Vec2( SystemValue::origin.x + SystemValue::windowSize.width/2,
		SystemValue::origin.y + SystemValue::windowSize.height - label->getContentSize().height));
		this -> addChild( label, 1);
	}
#endif

	sprite3D -> startAnimationReverse( "dei1");
	sprite3D -> setPosition3D( Vec3( SystemValue::windowSize.width / 2, SystemValue::windowSize.height / 4, 0));
	sprite3D -> setRotation3D( Vec3( 0.0f, 0.0f, 0.0f));
	sprite3D -> setScale( 250.0f);
	this -> addChild( sprite3D);

	auto light = AmbientLight::create (Color3B::RED);
//	auto light = PointLight::create(Vec3(0.0f, 0.0f, 0.0f), Color3B::RED, 10000.0f);
//	auto light = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B::RED);
	addChild (light);

//	auto light = SpotLight::create(Vec3(-1.0f, -1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f),Color3B::RED, 0.0, 0.5, 10000.0f) ;

	#ifdef CAMERA3D//3DÂ∫ßÊ®ô„Åß‰ΩúÊ•≠„Åó„Åü„ÅÑ„Å®„Åç„Å´‰ΩøÁî®„Åó„Å¶‰∏ã„Åï„ÅÑ
	auto screenSize = Director::getInstance()->getWinSize();//„Çπ„ÇØ„É™„Éº„É≥„Çµ„Ç§„Ç∫„ÇíÂèñÂæó

	//„Ç´„É°„É©ÂÆöÁæ©
	Camera3D = Camera::createPerspective(20, (GLfloat)screenSize.width / screenSize.height, 1, 1000);
	Camera3D->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0, 1, 0));
	Camera3D->setPosition3D(Vec3(0.0f, 0.0f, 20.0f));//Â∫ßÊ®ô„ÅØÈÅ©ÂÆúË™øÊï¥
	addChild(Camera3D);

	//sprite3D„ÅÆÂ∫ßÊ®ô„Çí3D„Å´ÂØæÂøú
	sprite3D->setPosition3D(Vec3(0.0f, 0.0f, -20.0f));//Â∫ßÊ®ô„ÅØÈÅ©ÂÆúË™øÊï¥
	sprite3D->setScale(0.1f);
	sprite3D->setRotation3D(Vec3(0.0f, 60.0f, 0.0f));
	#endif
	//this -> scheduleUpdate();
	return true;
}

void Test::update( float delta)
{
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
//	this -> addChild( label, 1);
}

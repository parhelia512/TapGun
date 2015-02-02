
#include <sstream>
#include <iostream>
#include "TestScene.h"
#include "SimpleAudioEngine.h"


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

#define CAMERA3D//

//一時的に定義する
#define PERSE 35//カメラ視野角
#define SETX 0.4f
#define SETY 1.85f
#define SETZ 3.3f

#define ROTX -8.0f
#define ROTY -10.0f
#define ROTZ 0.0f

//プレイヤー
#define PPOSX 5.5f
#define PPOSY 0.0f
#define PPOSZ 4.0f

#define PROTX 0.0f
#define PROTY 85.0f
#define PROTZ 0.0f


USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

//_Sprite3D* sprite3D;
cocos2d::Layer* Test::lay;
cocos2d::Camera* Camera3D;
cocos2d::Node* CamNode;

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
	sprite3D = _Sprite3D::create( "StageVer5.c3t");
#else
	auto spriteMap = _Sprite3D::create( "Stage/StageVer5");//, "Enemy.anime");
	auto spritePlayer = _Sprite3D::create("Player/player","player.anime");
	auto spriteEnemy1 = _Sprite3D::create("enemy/enemy", "Enemy.anime");
	auto spriteEnemy2 = _Sprite3D::create("enemy/enemy", "Enemy.anime");

#endif
	//マップ
	spriteMap->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	addChild(spriteMap);

	//エネミー
	spriteEnemy1->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
	spriteEnemy1->setPosition3D(Vec3(15.0f, 0.0f, 5.5f));
	addChild(spriteEnemy1);

	//プレイヤー
	spritePlayer->setPosition3D(Vec3(PPOSX, PPOSY, PPOSZ));
	spritePlayer->setRotation3D(Vec3(0.0f, PROTY, 0.0f));
	addChild(spritePlayer);

#ifdef CAMERA3D//
	
	auto screenSize = Director::getInstance()->getWinSize();//

	CamNode = Node::create();
	Camera3D = Camera::createPerspective(PERSE, (GLfloat)screenSize.width / screenSize.height, 1, 1000);
	addChild(CamNode);
	CamNode->addChild(Camera3D);

	//カメラ設定
	Camera3D->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0, 1, 0));

	//カメラ座標と回転
	CamNode->setPosition3D(Vec3(SETX, SETY, SETZ));//プレイヤー（親ノード）とカメラの位置関係をセット
	CamNode->setPosition3D(Vec3(ROTX, ROTY, ROTZ));

	//カメラとプレイヤーの距離
	Camera3D->setPosition3D(Vec3(SETX, SETY, SETZ));
	Camera3D->setRotation3D(Vec3(ROTX, ROTY, ROTZ));

//	Camera3D->setCameraFlag(CameraFlag::USER1);//USER1を3D用にする
#endif

//	this -> scheduleUpdate();

	return true;
}

void Test::update( float delta)
{
	static int count = 0;
	if( count % 20 == 0)
	{
	}
	count++;
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
	auto closeItem = MenuItemImage::create( "Graph/Pictures/CloseNormal.png", "Graph/Pictures/CloseSelected.png", CC_CALLBACK_1( Test::menuCloseCallback, this));
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


void loadSoundFile( void)
{
	auto sound = Sound::getInstance();
	sound -> loadBGM( "testBGM.mp3");
	sound -> playBGMLoop( 0.3f);

	sound -> loadSE( "Enemy/Shot.wav");
	sound -> loadSE( "Enemy/Reload.mp3");
	sound -> loadSE( "Enemy/Damage_01.wav");
	sound -> loadSE( "Enemy/Damage_02.wav");
	sound -> loadSE( "Enemy/Damage_03.wav");
	sound -> loadSE( "Enemy/Damage_04.wav");
}

void playSoundFile( void)
{
	auto sound = Sound::getInstance();

	sound -> playSE( "Enemy/Shot.wav");
	sound -> playSE( "Enemy/Replay.mp3");
	sound -> playSE( "Enemy/Damage_01.wav");
	sound -> playSE( "Enemy/Damage_02.wav");
	sound -> playSE( "Enemy/Damage_03.wav");
	sound -> playSE( "Enemy/Damage_04.wav");

=======
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

#define CAMERA3D//

//一時的に定義する
#define PERSE 35//カメラ視野角
#define SETX 0.4f
#define SETY 1.85f
#define SETZ 3.3f

#define ROTX -8.0f
#define ROTY -10.0f
#define ROTZ 0.0f

//プレイヤー
#define PPOSX 5.5f
#define PPOSY 0.0f
#define PPOSZ 4.0f

#define PROTX 0.0f
#define PROTY 85.0f
#define PROTZ 0.0f


USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

//_Sprite3D* sprite3D;
cocos2d::Layer* Test::lay;
cocos2d::Camera* Camera3D;
cocos2d::Node* CamNode;

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
	sprite3D = _Sprite3D::create( "StageVer5.c3t");
#else
	auto spriteMap = _Sprite3D::create( "Stage/StageVer5");//, "Enemy.anime");
	auto spritePlayer = _Sprite3D::create("Player/player","player.anime");
	auto spriteEnemy1 = _Sprite3D::create("enemy/enemy", "Enemy.anime");
	auto spriteEnemy2 = _Sprite3D::create("enemy/enemy", "Enemy.anime");

#endif
	//マップ
	spriteMap->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	addChild(spriteMap);

	//エネミー
	spriteEnemy1->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
	spriteEnemy1->setPosition3D(Vec3(15.0f, 0.0f, 5.5f));
	addChild(spriteEnemy1);

	//プレイヤー
	spritePlayer->setPosition3D(Vec3(PPOSX, PPOSY, PPOSZ));
	spritePlayer->setRotation3D(Vec3(0.0f, PROTY, 0.0f));
	addChild(spritePlayer);

#ifdef CAMERA3D//
	
	auto screenSize = Director::getInstance()->getWinSize();//

	CamNode = Node::create();
	Camera3D = Camera::createPerspective(PERSE, (GLfloat)screenSize.width / screenSize.height, 1, 1000);
	addChild(CamNode);
	CamNode->addChild(Camera3D);

	//カメラ設定
	Camera3D->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0, 1, 0));

	//カメラ座標と回転
	CamNode->setPosition3D(Vec3(SETX, SETY, SETZ));//プレイヤー（親ノード）とカメラの位置関係をセット
	CamNode->setPosition3D(Vec3(ROTX, ROTY, ROTZ));

	//カメラとプレイヤーの距離
	Camera3D->setPosition3D(Vec3(SETX, SETY, SETZ));
	Camera3D->setRotation3D(Vec3(ROTX, ROTY, ROTZ));

//	Camera3D->setCameraFlag(CameraFlag::USER1);//USER1を3D用にする
#endif

//	this -> scheduleUpdate();

	return true;
}

void Test::update( float delta)
{
	static int count = 0;
	if( count % 20 == 0)
	{
	}
	count++;
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
	auto closeItem = MenuItemImage::create( "Graph/Pictures/CloseNormal.png", "Graph/Pictures/CloseSelected.png", CC_CALLBACK_1( Test::menuCloseCallback, this));
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


void loadSoundFile( void)
{
	auto sound = Sound::getInstance();
	sound -> loadBGM( "testBGM.mp3");
	sound -> playBGMLoop( 0.3f);

	sound -> loadSE( "Enemy/Shot.wav");
	sound -> loadSE( "Enemy/Reload.mp3");
	sound -> loadSE( "Enemy/Damage_01.wav");
	sound -> loadSE( "Enemy/Damage_02.wav");
	sound -> loadSE( "Enemy/Damage_03.wav");
	sound -> loadSE( "Enemy/Damage_04.wav");
}

void playSoundFile( void)
{
	auto sound = Sound::getInstance();

	sound -> playSE( "Enemy/Shot.wav");
	sound -> playSE( "Enemy/Replay.mp3");
	sound -> playSE( "Enemy/Damage_01.wav");
	sound -> playSE( "Enemy/Damage_02.wav");
	sound -> playSE( "Enemy/Damage_03.wav");
	sound -> playSE( "Enemy/Damage_04.wav");


}
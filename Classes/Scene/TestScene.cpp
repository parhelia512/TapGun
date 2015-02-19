
#include <sstream>
#include <iostream>
#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "Define.h"

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
Sprite3D* spriteBullet[20];
_Sprite3D* spritePlayer;// = _Sprite3D::create("player/player");

Animation3D* tHideShotLeft;// = Animation3D::create("Graph/Models/player/mot_player_hide_shot_left.c3b");
Animate3D* teHideShotLeft;// = Animate3D::create(aHideShotLeft);
Animate3D* teHideShotLeftR;// = Animate3D::create(aHideShotLeft);

int tFlag;
int aFlag;
//cocos2d::Node* CamNode;

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


	//現在はタッチイベントのリスナーをここに用意しています
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Test::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Test::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Test::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto sprite3d = _Sprite3D::create( "StageVer5.c3t");
#else
//	auto spriteMap = _Sprite3D::create( "Stage/map507");
	spritePlayer = _Sprite3D::create("player/player");
//	auto spriteEnemy1 = _Sprite3D::create("enemy/enemy", "Enemy.anime");
//	auto spriteEnemy2 = _Sprite3D::create("enemy/enemy", "Enemy.anime");

	//for (int i = 0; i < 20; i++)
	//{
	//	spriteBullet[i] = Sprite3D::create("Graph/Models/Bullet/bullet.c3t");
	//}

#endif
	//マップ
	//spriteMap->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	//addChild(spriteMap);
	//spriteMap->setCameraMask(1);

	//エネミー
	//spriteEnemy1->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
	//spriteEnemy1->setPosition3D(Vec3(15.0f, 0.0f, 5.5f));
	//addChild(spriteEnemy1);

	//プレイヤー
	spritePlayer->setPosition3D(Vec3(0, 0, 5.0f));
	spritePlayer->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	addChild(spritePlayer);
	spritePlayer->setCameraMask(1);


	//アニメーションロード
	tHideShotLeft = Animation3D::create("Graph/Models/player/mot_player_hide_shot_left.c3t");
	teHideShotLeft = Animate3D::create(tHideShotLeft);
	teHideShotLeftR = Animate3D::create(tHideShotLeft);
	teHideShotLeftR->setSpeed(-1.0f);


	//弾
	//for (int i = 0; i < 20; i++)
	//{
	//	spriteBullet[i]->setPosition3D(Vec3(-1.5f + 0.2f * i, 0.0f, 1.0f + 0.6f * i));
	//	spriteBullet[i]->setRotation3D(Vec3(-90.0f, 0.0f, 0.0f));


	//	spriteBullet[i]->setPosition3D(Vec3(-0.6f + 0.05f * i, 0.0f, 2.85f + 0.03f * i));
	//	spriteBullet[i]->setRotation3D(Vec3(-90.0f, 180.0f, 0.0f));

	//	spriteBullet[i]->setScale(2.0f);

	//	addChild(spriteBullet[i]);
	//	spriteBullet[i]->setCameraMask(1);
	//}

//	LifeUI::getInstance() -> init( this);
//	LogoUI::getInstance() -> init( this);
	
#ifdef CAMERA3D//
	
	auto screenSize = Director::getInstance()->getWinSize();//

//	CamNode = Node::create();
	Camera3D = Camera::createPerspective(PERSE, (GLfloat)screenSize.width / screenSize.height, 1, 1000);
//	addChild(CamNode);
//	CamNode->addChild(Camera3D);
	addChild(Camera3D);


	//カメラ設定
	Camera3D->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0, 1, 0));
	//カメラ座標と回転
//	CamNode->setPosition3D(Vec3(SETX, SETY, SETZ));//プレイヤー（親ノード）とカメラの位置関係をセット
//	CamNode->setPosition3D(Vec3(ROTX, ROTY, ROTZ));

	//カメラとプレイヤーの距離
	Camera3D->setPosition3D(Vec3(0.0f, 0.0f, 80.0f));//足場ブロック確認
	Camera3D->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));

	Camera3D->setPosition3D(Vec3(-13.0f, 8.0f, 65.0f));//足場ブロック確認
	Camera3D->setRotation3D(Vec3(-30.0f, 0.0f, 0.0f));

	Camera3D->setPosition3D(Vec3(-2.0f, 2.0f, 53.0f));//足場ブロック確認
	Camera3D->setRotation3D(Vec3(-0.0f, -18.0f, 0.0f));


	Camera3D->setPosition3D(Vec3(0.0f, 0.0f, 5.0f));//敵弾描画確認
	Camera3D->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));

	Camera3D->setPosition3D(Vec3(0.0f, 0.0f, 15.0f));//敵弾描画確認
	Camera3D->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));

	Camera3D->setCameraFlag(CameraFlag::DEFAULT);//USER1を3D用にする
#endif

//	this -> scheduleUpdate();
	this -> schedule(schedule_selector(Test::moveTime), 0.016f);

	return true;
}

void Test::update( float delta)
{
	
}

void Test::moveTime( float delta)
{

	if(tFlag == 1 && aFlag == 0)
	{
	//	spritePlayer->stopAllActions();
		spritePlayer->runAction(teHideShotLeft);
		aFlag = 1;
	}
	int a = 0;
	a++;
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


bool Test::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	tFlag = 1;
	return true;
}


void Test::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	tFlag = 0;
}



void Test::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	aFlag = 0;
	tFlag = 0;
}
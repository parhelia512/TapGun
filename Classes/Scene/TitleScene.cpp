
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"
#include "TitleScene.h"
#include "GameScene.h"//遷移先のシーンをインクルード
#include "CreditScene.h"
#include "ResourceLoader.h"
#include "Sound.h"

#else

#include "Base/Sprite3D.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"//遷移先のシーンをインクルード
#include "Scene/CreditScene.h"
#include "System/ResourceLoader.h"
#include "System/Sound.h"

#endif

USING_NS_CC;
using namespace TapGun;

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init()) { return false; }

	alphaCount = 0;
	logoAlphaFlag = false;
	logoAlphaCount = 0;
	logoAlphaWaitCount = 0;
	frame = 0;

	auto cache = SpriteFrameCache::getInstance();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	cache -> addSpriteFramesWithFile( "Title.plist");
	cache -> addSpriteFramesWithFile( "P_Hit.plist");
	cache -> addSpriteFramesWithFile( "E_Hit.plist");
#else
	cache -> addSpriteFramesWithFile( "Graph/Pictures/Title.plist");
	cache -> addSpriteFramesWithFile( "Graph/Pictures/P_Hit.plist");
	cache -> addSpriteFramesWithFile( "Graph/Pictures/E_Hit.plist");
#endif
	menuFlag = TeamLogo;

	auto listener = EventListenerTouchOneByOne::create();
	listener -> setSwallowTouches(_swallowsTouches);
	listener -> onTouchBegan = CC_CALLBACK_2( TitleScene::onTouchBegan, this);
	listener -> onTouchMoved = CC_CALLBACK_2( TitleScene::onTouchMoved, this);
	listener -> onTouchEnded = CC_CALLBACK_2( TitleScene::onTouchEnded, this);
	_eventDispatcher -> addEventListenerWithSceneGraphPriority( listener, this);
	
	loadSound();
	setSprite();
	setMenu();

	scheduleUpdate();
//	schedule( schedule_selector( TitleScene::moveTime), 0.016f * 8);

	return true;
}

void TitleScene::update( float delta)
{
	_Sprite3D* sp;
	static bool modelLoadFlag = false;
	auto sound = Sound::getInstance();
	auto cache = SpriteFrameCache::getInstance();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if( frame == ResourceLoader::Map)
	{
		ResourceLoader::getInstance() -> loadModel( "map507");
	}
	else if( frame >= ResourceLoader::EnemyStart && frame <= ResourceLoader::EnemyEnd)
	{
		ResourceLoader::getInstance() -> loadModel( "enemy", "", "Enemy.anime");
	}
	else if( frame >= ResourceLoader::BulletStart && frame <= ResourceLoader::BulletEnd)
	{
		ResourceLoader::getInstance() -> loadModel( "tama");
	}
	else if( frame == ResourceLoader::Player)
	{
		ResourceLoader::getInstance() -> loadModel( "player", "", "Player.anime");
	}
#else
	if( frame == ResourceLoader::Map)
	{
		ResourceLoader::getInstance() -> loadModel( "Stage/map507");
	}
	else if( frame >= ResourceLoader::EnemyStart && frame <= ResourceLoader::EnemyEnd)
	{
		ResourceLoader::getInstance() -> loadModel( "enemy/enemy", "", "Enemy.anime");
	}
	else if( frame >= ResourceLoader::BulletStart && frame <= ResourceLoader::BulletEnd)
	{
		ResourceLoader::getInstance() -> loadModel( "Bullet/tama");
	}
	else if( frame == ResourceLoader::Player)
	{
		ResourceLoader::getInstance() -> loadModel( "player/player", "", "Player.anime");
	}
#endif

	switch( menuFlag)
	{
	case TeamLogo:
		if( modelLoadFlag == false && ( sp = ResourceLoader::getInstance() -> getSprite3D( ResourceLoader::BulletStart)) != nullptr)
		{
			modelLoadFlag = true;
			sp -> setPosition3D( Vec3( 640, 200, 0));
			sp -> setScale( 300.0f);
			addChild( sp);
		}
		teamLogoAction();		
		break;

	case TitleLogoIn:
		alphaCount += 4;
		for( auto &p : sprite) { p -> setOpacity( alphaCount); }
		if( alphaCount > 180)
		{
			menuFlag = TitleLogoOK;
			sound -> playBGMLoop();
		}
		break;

	case TitleLogoOK:
		sprite[Menu] -> setVisible( true);
		if( logoAlphaFlag) 
		{ 
			sprite[Menu] -> setOpacity( logoAlphaCount);
			if( logoAlphaCount == 0) { logoAlphaWaitCount++; }
			else { logoAlphaCount -= 5; }
		}
		else
		{
			sprite[Menu] -> setOpacity( logoAlphaCount);
			if( logoAlphaCount == 250) { logoAlphaWaitCount++; }
			else { logoAlphaCount += 5; }
		}
		if( ( logoAlphaCount == 250 && logoAlphaWaitCount == 20) || ( logoAlphaCount == 0 && logoAlphaWaitCount == 5)) 
		{
			logoAlphaFlag = !logoAlphaFlag;
			logoAlphaWaitCount = 0;
		}
		break;

	case MenuIn:
		break;

	case MenuOK:
		break;

	case TitleEnd:
		break;

	default:
		log( "Title : FlagError");
		break;
	}
	frame++;
}

void TitleScene::moveTime( float delta)
{
}

bool TitleScene::onTouchBegan( Touch *touch, Event *unused_event)
{
	return true;
}

void TitleScene::onTouchMoved( Touch *pTouch, Event *pEvent)
{
}

void TitleScene::onTouchEnded( Touch *pTouch, Event *pEvent)
{
	auto sound = Sound::getInstance();

	if( menuFlag == TitleLogoOK)
	{ 
		menuFlag = MenuIn;
		sprite[Logo] -> runAction( MoveTo::create( 1, Point( 3000, sprite[Logo] -> getPositionY())));
		auto action = Blink::create( 0.2, 3);
		sound -> playSE( "MoveSE.mp3");
		auto func = CallFunc::create( [&](void) -> void { sprite[Menu] -> setVisible( false); menuAction(); });
		sprite[Menu] -> runAction( Sequence::create( action, func, NULL));
	}
}

void TitleScene::teamLogoAction( void)
{
	if( teamLogoState == LogoIn)
	{
		alphaCount += AlphaValue;
		if( teamLogo -> getOpacity() == AlphaValue * 50) { teamLogoState = LogoOut; }
		teamLogo -> setOpacity( alphaCount);
	}
	else if( teamLogoState == LogoOut)
	{
		if( waitCount > WaitTime) { alphaCount -= AlphaValue; }
		else { waitCount++; }
		if( teamLogo -> getOpacity() == 0) 
		{
			waitCount = 0;
			teamLogoState = Wait;
			teamLogo -> setVisible( false);
		}		
		teamLogo -> setOpacity( alphaCount);
	}
	else if( teamLogoState == Wait)
	{
		if( waitCount > 50) 
		{ 
			alphaCount = 0;
			menuFlag = TitleLogoIn;
		}
		waitCount++;
	}
}

void TitleScene::setSprite( void)
{
	auto visibleSize = Director::getInstance() -> getVisibleSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	teamLogo = Sprite::create( "ty.png");
#else
	teamLogo = Sprite::create( "Graph/Pictures/ty.png");
#endif
	teamLogo -> setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2));
	teamLogo -> setOpacity( 0);
	addChild( teamLogo);

	sprite[BG] = Sprite::createWithSpriteFrameName( "title_haikei.png");
	sprite[Frame] = Sprite::createWithSpriteFrameName( "title_waku.png");
	sprite[Logo] = Sprite::createWithSpriteFrameName( "title_log.png");
	sprite[Menu] = Sprite::createWithSpriteFrameName( "title_touchscreen.png");
	
	for( auto &p : sprite)
	{
		p -> setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2));
		p -> setOpacity( 0);
		addChild( p);
	}
	sprite[Menu] -> setVisible( false);
}

void TitleScene::setMenu( void)
{
	auto visibleSize = Director::getInstance() -> getVisibleSize();
	auto cache = SpriteFrameCache::getInstance();

	auto item = MenuItemSprite::create( Sprite::createWithSpriteFrameName( "title_start.png"), 
				Sprite::createWithSpriteFrameName( "title_start_push.png"), CC_CALLBACK_1( TitleScene::menuStartCallback, this));
	menu[Start] = Menu::create( item, NULL);
	menu[Start] -> setPosition( Vec2( -1200, visibleSize.height - 270));
	addChild( menu[Start]);

	item = MenuItemSprite::create( Sprite::createWithSpriteFrameName( "title_end.png"), 
				Sprite::createWithSpriteFrameName( "title_end_push.png"), CC_CALLBACK_1( TitleScene::menuEndCallback, this));
	menu[End] = Menu::create( item, NULL);
	menu[End] -> setPosition( Vec2( -1200, visibleSize.height / 2));
	addChild( menu[End]);
	
	item = MenuItemSprite::create( Sprite::createWithSpriteFrameName( "title_credit.png"), 
				Sprite::createWithSpriteFrameName( "title_credit_push.png"), CC_CALLBACK_1( TitleScene::menuCreditCallback, this));
	menu[Credit] = Menu::create( item, NULL);
	menu[Credit] -> setPosition( Vec2( -1200, visibleSize.height - 530));
	addChild( menu[Credit]);
}

void TitleScene::menuAction( void)
{
	auto visibleSize = Director::getInstance() -> getVisibleSize();

	for( auto &p : menu)
	{
		auto action = MoveTo::create( 1, Vec2(  visibleSize.width / 2, p -> getPositionY()));
		p -> runAction( action);
	}
}

void TitleScene::menuStartCallback( Ref* pSender)
{
	auto sound = Sound::getInstance();
	sound -> stopBGM();
	sound -> playSE( "MoveSE.mp3");
	auto scene = GameScene::CreateScene();
	auto tran = TransitionCrossFade::create( 1, scene);
	Director::getInstance() -> replaceScene( tran);
}

void TitleScene::menuEndCallback( Ref* pSender)
{
	auto sound = Sound::getInstance();
	sound -> stopBGM();
	sound -> playSE( "MoveSE.mp3");
	Director::getInstance() -> end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void TitleScene::menuCreditCallback( Ref* pSender)
{
	auto sound = Sound::getInstance();
	sound -> stopBGM();
	sound -> playSE( "MoveSE.mp3");
	auto scene = CreditScene::createScene();
	auto tran = TransitionCrossFade::create( 1, scene);
	Director::getInstance() -> replaceScene( tran);
}

void TitleScene::loadSound( void)
{
	auto sound = Sound::getInstance();

	sound -> loadBGM( "Title.mp3");
	sound -> loadSE( "MoveSE.mp3");
}

template<class P> bool TitleScene::checkFlag( P* flag, const P number) { return ( ( *flag & number) != 0); }
template<class P> void TitleScene::setFlag( P* flag, const P number) { *flag |= number; }
template<class P> void TitleScene::resetFlag( P* flag, const P number) { *flag &= ~number; }

template bool TitleScene::checkFlag( unsigned char* a, const unsigned char b);
template void TitleScene::setFlag( unsigned char* a, const unsigned char b);
template void TitleScene::resetFlag( unsigned char* a, const unsigned char b);

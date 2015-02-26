
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

	menuFlag = 0;
	alphaCount = 0;
	logoAlphaFlag = false;
	logoAlphaCount = 0;
	logoAlphaWaitCount = 0;
	frame = 0;

	setFlag( &menuFlag, (unsigned char)Idle);

	auto listener = EventListenerTouchOneByOne::create();
	listener -> setSwallowTouches(_swallowsTouches);
	listener -> onTouchBegan = CC_CALLBACK_2( TitleScene::onTouchBegan, this);
	listener -> onTouchMoved = CC_CALLBACK_2( TitleScene::onTouchMoved, this);
	listener -> onTouchEnded = CC_CALLBACK_2( TitleScene::onTouchEnded, this);
	_eventDispatcher -> addEventListenerWithSceneGraphPriority( listener, this);

	setSprite();

	scheduleUpdate();
	schedule( schedule_selector( TitleScene::moveTime), 0.016f);

	return true;
}

void TitleScene::update( float delta)
{
	switch( menuFlag)
	{
	case Idle:
		break;

	case LogoIn:
		alphaCount += 4;
		for( auto &p : sprite) { p -> setOpacity( alphaCount); }
		if( alphaCount > 180)
		{
			resetFlag( &menuFlag, (unsigned char)LogoIn);
			setFlag( &menuFlag, (unsigned char)LogoOK);
		}
		break;

	case LogoOK:
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
	if( checkFlag( &menuFlag, (unsigned char)Idle))
	{ 
		resetFlag( &menuFlag, (unsigned char)Idle);
		setFlag( &menuFlag, (unsigned char)LogoIn);
	}
	if( checkFlag( &menuFlag, (unsigned char)LogoOK))
	{ 
		resetFlag( &menuFlag, (unsigned char)LogoOK);
		setFlag( &menuFlag, (unsigned char)MenuIn);
		sprite[Logo] -> runAction( MoveTo::create( 1, Point( 3000, sprite[Logo] -> getPositionY())));
		auto action = Blink::create( 0.2, 3);
		auto func = CallFunc::create( [&](void) -> void { sprite[Menu] -> setVisible( false); });
		sprite[Menu] -> runAction( Sequence::create( action, func, NULL));
	}
}

void TitleScene::setSprite( void)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto cache = SpriteFrameCache::getInstance();
	cache -> addSpriteFramesWithFile( "Graph/Pictures/Title.plist");

	sprite[BG] = Sprite::createWithSpriteFrameName( "title_haikei.png");
	sprite[Frame] = Sprite::createWithSpriteFrameName( "title_waku.png");
	sprite[Logo] = Sprite::createWithSpriteFrameName( "title_log.png");
	sprite[Menu] = Sprite::createWithSpriteFrameName( "title_touchscreen.png");
	
	for( int i = 0; i < SpriteNum; i++)
	{
		sprite[i] -> setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2));
		sprite[i] -> setOpacity( 0);
		addChild( sprite[i]);
	}
	sprite[Menu] -> setVisible( false);

	menu[0];
}

template<class P> bool TitleScene::checkFlag( P* flag, const P number) { return ( ( *flag & number) != 0); }

template<class P> void TitleScene::setFlag( P* flag, const P number) { *flag |= number; }

template<class P> void TitleScene::resetFlag( P* flag, const P number) { *flag &= ~number; }

template bool TitleScene::checkFlag( unsigned char* a, const unsigned char b);
template void TitleScene::setFlag( unsigned char* a, const unsigned char b);
template void TitleScene::resetFlag( unsigned char* a, const unsigned char b);

//auto scene = GameScene::CreateScene();
//auto tran = TransitionCrossFade::create( 1, scene);
//Director::getInstance() -> replaceScene( tran);
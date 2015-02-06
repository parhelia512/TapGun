#include"UI.h"

#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
#include "GameUILayer.h"

#else

#include "C++/Base/GameMaster.h"
#include "C++/Scene/GameUILayer.h"

#endif


using namespace TapGun;
USING_NS_CC;


/**
*	インクリメント
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
//UI::UI(void)
//{
//	初期化内容は随時更新します
//
//	管理フラグ
//	valid = FALSE;
//	kind = UIKIND_NONE;//UI種別をNONEに
//
//	変数
//	speed = 0.0f;//移動速度
//	speedVec = Vec2(0.0f, 0.0f);//移動ベクトル
//	targetPos = Vec2(0.0f, 0.0f);//移動目標
//
//	frame = 0;//管理フレーム
//}


/**
*	UIクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::Init(void)
{
	//初期化内容は随時更新します

	//管理フラグ
	valid = FALSE;
	kind = UIKIND_NONE;//UI種別をNONEに

	//変数
	//speed = 0.0f;//移動速度
	//speedVec = Vec3(0, 0, 0);//移動ベクトル
	//targetPos = Vec3(0, 0, 0);//移動目標

	frame = 0;//管理フレーム
}







/**
*	UIクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	UI配列の番号,UI種別
*	@return	正常終了:1 初期化エラー:-1
*	@date	1/8 Ver 1.0
*/
int UI::Init(int num, int utype)
{
	//初期化内容は随時更新します


	//num番のUI構造体が使用されているか初期化されていない、またはUI種別が不正、または配列外の場合はエラー
	if(FALSE != valid || 0 > utype || UIKIND_NUM <= utype || 0 > num || MAX_UI <= num)
	{
		return FALSE;
	}

	//フラグの初期化
	valid = TRUE;
	kind = utype;

	//変数
	speed = 0.0f;
	//speedVec = Vec3(0, 0, 0);
	//targetPos = Vec3(0, 0, 0);

	frame = 0;//管理フレーム

	//モデルの種別によって当たり判定の設定を行う
	//敵や弾の種類（副種別）によってさらに条件分けする
	switch(utype)
	{
	case UIKIND_ARROW:

		break;
	default:

		break;
	}
}




//UI* UI::Create( void)
//{
//	auto sprite = new UI();
//	return sprite;
//}





/**
*	当たり判定の初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::SetCollision(void)
{

}




/**
*	速度をもとにしたUI移動
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::UpdatePos(void)
{

}



/**
*	引数座標へのUI移動
*
*	@author	sasebon
*	@param	座標
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::UpdatePos(Vec2 pos)
{
}

LifeUI* LifeUI::getInstance( void)
{
	static LifeUI* P;
	if( !P) P = new LifeUI;
	return P;
}

LifeUI::LifeUI()
{
}

void LifeUI::init( Layer* layer)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Life.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Logo.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Number.plist");
	frame = Sprite::create( "lifekara.png");
	bullet = Sprite::create( "Bullet.png");
#else
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Life/Life.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Life/Logo.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Number/Number.plist");
	frame = Sprite::create( "Graph/Pictures/Life/lifekara.png");
	bullet = Sprite::create( "Graph/Pictures/Life/Bullet.png");
#endif
	frame -> setScale( 0.05f);
	frame -> setPosition3D( Vec3( 640 - 5, 800 - 100, 0));
	
	bullet -> setScale( 0.05f);
	bullet -> setPosition3D( Vec3( 640, 60, 0));
	
	life[Up] = Sprite::createWithSpriteFrameName( "life4.png");
	life[Up] -> setPosition( Vec2( 2130, 3280));
	life[Up] -> setScale( 1.9f);
	life[Up] -> setColor( Color3B::GREEN);
	life[Down] = Sprite::createWithSpriteFrameName( "life2.png");
	life[Down] -> setPosition( Vec2( 2160, 1160));
	life[Down] -> setScale( 1.9f);
	life[Down] -> setColor( Color3B::GREEN);
	life[Left] = Sprite::createWithSpriteFrameName( "life1.png");
	life[Left] -> setPosition( Vec2( 620, 1810));
	life[Left] -> setScale( 1.9f);
	life[Left] -> setColor( Color3B::GREEN);
	life[Right] = Sprite::createWithSpriteFrameName( "life3.png");
	life[Right] -> setPosition( Vec2( 3700, 2220));
	life[Right] -> setScale( 1.9f);
	life[Right] -> setColor( Color3B::GREEN);

	for( auto &p : life) { frame -> addChild( p); }
	
	number[0] = Sprite::createWithSpriteFrameName( "Num1.png");
	number[0] -> setPosition( Vec2( 1330, 2180));
	number[0] -> setScale( 1.9f);
	number[1] = Sprite::createWithSpriteFrameName( "Num0.png");
	number[1] -> setPosition( Vec2( 1830, 2200));
	number[1] -> setScale( 1.9f);
	number[2] = Sprite::createWithSpriteFrameName( "Num0.png");
	number[2] -> setPosition( Vec2( 2330, 2200));
	number[2] -> setScale( 1.9f);
	number[3] = Sprite::createWithSpriteFrameName( "Num0.png");
	number[3] -> setPosition( Vec2( 2900, 1920));
	number[3] -> setScale( 1.0f);
	number[4] = Sprite::createWithSpriteFrameName( "Num0.png");
	number[4] -> setPosition( Vec2( 3200, 1920));
	number[4] -> setScale( 1.0f);
	
	for( auto &p : number) { frame -> addChild( p); }
	
	// auto time = GameMaster::GetInstance() -> gameTime;
	
	/*
	if( time > 100)
	{
		number[0] = Sprite::createWithSpriteFrameName( "Num1.png");
		number[0] -> setVisible( true);
	}
	else if( time >= 90 && time < 100)
	{
		number[0] -> setVisible( false);
		number[1] = Sprite::createWithSpriteFrameName( "Num9.png");
	}*/
	
	layer -> addChild( frame);
	layer -> addChild( bullet);
}

void LifeUI::update( void)
{

}


LogoUI* LogoUI::getInstance( void)
{
	static LogoUI* P;
	if( !P) P = new LogoUI;
	return P;
}

LogoUI::LogoUI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Logo.plist");
#else
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Life/Logo.plist");
#endif
	logo[Action] = Sprite::createWithSpriteFrameName( "action.png");
	logo[Wait] = Sprite::createWithSpriteFrameName( "wait.png");
	logo[Reload] = Sprite::createWithSpriteFrameName( "rerode.png");
	for( auto &p : logo)
	{
		p -> setScale( 0.3f);
		p -> setPosition( Vec2( 1280 / 2, 800 / 3));
		p -> setVisible( false);
	}
}

void LogoUI::init( Layer* layer)
{
	for( auto &p : logo) { layer -> addChild( p); }
}

void LogoUI::update( void)
{

}

void LogoUI::setLogo( LogoNumber num)
{
	logo[num] -> setVisible(true);
	logo[num] -> runAction(Sequence::create( DelayTime::create( 1.5f), Hide::create(), NULL));
}

void LogoUI::resetLogo( LogoNumber num)
{
	logo[num] -> setVisible(false);
}


#include"UI.h"

#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameUILayer.h"

#else

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Life.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Logo.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Number.plist");
	this -> frame = Sprite::create( "lifekara.png");
#else
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Life/Life.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Life/Logo.plist");
	SpriteFrameCache::getInstance() -> addSpriteFramesWithFile( "Graph/Pictures/Number/Number.plist");
	this -> frame = Sprite::create( "Graph/Pictures/Life/lifekara.png");
#endif
	frame -> setPosition( Vec2( SystemValue::windowSize.width / 2, frame -> getContentSize().height));
	
	life[Up] = Sprite::createWithSpriteFrameName( "life4.png");
	life[Down] = Sprite::createWithSpriteFrameName( "life2.png");
	life[Left] = Sprite::createWithSpriteFrameName( "life1.png");
	life[Right] = Sprite::createWithSpriteFrameName( "life3.png");
	for( auto &p : life) { frame -> addChild( p); }
}

void LifeUI::init( Layer* layer)
{
	layer -> addChild( frame);
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
	for( auto &p : logo) { p -> setVisible( false); }
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
	logo[num] -> runAction(Sequence::create( DelayTime::create(0.5f), Hide::create(), NULL));
}
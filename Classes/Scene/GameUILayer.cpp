
#include "GameUILayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
#include "UI.h"

#else

#include "Base/GameMaster.h"
#include "Base/UI.h"

#endif


USING_NS_CC;
using namespace TapGun;

GameMaster* GameMasterL;//変数名は今後考慮する


/**
*	ゲーム本編のUIレイヤーを初期化
*
*	@author	sasebon
*	@param	なし
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
bool GameUILayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	GameMasterL = GameMaster::GetInstance();//ゲームパラメータクラスの初期化
	return true;
}


/**
*	ゲーム本編のUIレイヤーの各種数値初期化
*
*	@author	sasebon
*	@param	なし
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
void GameUILayer::InitLayer(void)
{
	InitAllUI();
	LoadUISprite();
	SetUI();
}


/**
*	ゲーム本編のUIレイヤーの各種数値初期化
*
*	@author	sasebon
*	@param	なし
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
int GameUILayer::SerchFreeUI()
{
	for (int i = 0; i < MAX_UI; i++)
	{
		if (FALSE == Ui[i].valid)
		{
			return i;
		}
	}
	return -1;//全てのUISpriteが使用されていたら-1を返す
}


/**
*	UIスプライトの生成
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	2/5 Ver 1.0
*/
void GameUILayer::LoadUISprite()
{
	std::string fileName1;

	//レティクルの生成
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "reticle.png";
#else
	fileName1 = "Graph/Pictures/reticle.png";
#endif
	UIBillBoard[UIKIND_RETICLE] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);


	//リロードアラートの生成
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "reload.png";
#else
	fileName1 = "Graph/Pictures/reload.png";
#endif
	UIBillBoard[UIKIND_RELOAD] = cocos2d::BillBoard::createWithTexture( 
		Sprite::createWithSpriteFrameName( "rerode.png") -> getTexture(), BillBoard::Mode::VIEW_PLANE_ORIENTED);


	//アクションUIの生成
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "action.png";
#else
	fileName1 = "Graph/Pictures/action.png";
#endif
	UIBillBoard[UIKIND_ACTION] = cocos2d::BillBoard::createWithTexture( 
		Sprite::createWithSpriteFrameName( "action.png") -> getTexture(), BillBoard::Mode::VIEW_PLANE_ORIENTED);


	//ウェイトUIの生成
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "wait.png";
#else
	fileName1 = "Graph/Pictures/wait.png";
#endif
	UIBillBoard[UIKIND_WAIT] = cocos2d::BillBoard::createWithTexture( 
		Sprite::createWithSpriteFrameName( "wait.png") -> getTexture(), BillBoard::Mode::VIEW_PLANE_ORIENTED);


	//回避アイコンの生成
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "wait.png";
#else
	fileName1 = "Graph/Pictures/wait.png";
#endif
}


/**
*	UIの配置
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameUILayer::SetUI()
{
	auto s = Director::getInstance()->getWinSize();//スクリーンサイズを取得

	//レティクルの設定
	UIBillBoard[UIKIND_RETICLE]->setPosition(s.width / 2, s.height / 2);
	UIBillBoard[UIKIND_RETICLE]->setScale(0.4f);
	addChild(UIBillBoard[UIKIND_RETICLE]);

	Ui[UIKIND_RETICLE].Init(UIKIND_RETICLE, UIKIND_RETICLE);
	valid[UIKIND_RETICLE] = TRUE;

	//ウェイトUIの設定
	UIBillBoard[UIKIND_WAIT]->setPosition(s.width / 2, s.height / 2);
	UIBillBoard[UIKIND_WAIT]->setScale(0.1f);
	UIBillBoard[UIKIND_WAIT]->setVisible(false);
	addChild(UIBillBoard[UIKIND_WAIT]);

	Ui[UKIND_BULLET_B].Init(UKIND_BULLET_B, UKIND_BULLET_B);
	valid[UKIND_BULLET_B] = TRUE;

	//アクションUIの設定
	UIBillBoard[UIKIND_ACTION]->setPosition(s.width / 2, s.height / 2);
	UIBillBoard[UIKIND_ACTION]->setScale(0.1f);
	UIBillBoard[UIKIND_ACTION]->setVisible(false);
	addChild(UIBillBoard[UIKIND_ACTION]);

	Ui[UIKIND_ACTION].Init(UIKIND_ACTION, UIKIND_ACTION);
	valid[UIKIND_ACTION] = TRUE;


	//リロードアラートの設定
	UIBillBoard[UIKIND_RELOAD]->setPosition(s.width / 2, s.height / 2);
	UIBillBoard[UIKIND_RELOAD]->setScale(0.1f);
	addChild(UIBillBoard[UIKIND_RELOAD]);
	UIBillBoard[UIKIND_RELOAD]->setVisible(false);

	Ui[UIKIND_RELOAD].Init(UIKIND_RELOAD, UIKIND_RELOAD);
	valid[UIKIND_RELOAD] = TRUE;


	Sprite* sprite[4];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sprite[0] = Sprite::create("four4096.png");
	//	sprite[1] = Sprite::create("time.png");
	//	sprite[2] = Sprite::create("kaihiai.png");
	//	sprite[3] = Sprite::create("timelogo.png");
#else
	//	sprite[0] = Sprite::create("Graph/Pictures/four2048.png");
	//	sprite[1] = Sprite::create("Graph/Pictures/time.png");
	//	sprite[2] = Sprite::create("Graph/Pictures/kaihiai.png");
	//	sprite[3] = Sprite::create("Graph/Pictures/timelogo.png");
#endif
	//	sprite[0]->setPosition(Vec2(285, 695));
	//	sprite[0]->setScale(0.3f);

	//	sprite[1]->setPosition(Vec2(1085, 760));
	//	sprite[2]->setPosition(Vec2(100, 150));
	//	sprite[3]->setPosition(Vec2(250, 80));

	//	addChild(sprite[0]);

	//	for(auto &p : sprite) addChild(p);
}




/**
*	UI系の数値初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameUILayer::InitAllUI()
{
	for(int i = 0; i < MAX_UI; i++)
	{
		Ui[i].Init();
	}
}



/**
*	UIの更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
void GameUILayer::UpdateLayer( void)
{
	GameUILayer::MoveReticle();
}



/**
*	レティクルの移動
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameUILayer::MoveReticle(void)
{
	static bool flag = false;
	if (TRUE == valid[UIKIND_RETICLE])//初期化チェックは不要ならば消す
	{
		if (flag == false)
		{
			LifeUI::getInstance()->init(this);
			LogoUI::getInstance()->init(this);
			flag = true;
		}

		Vec2 tPos;
		auto size = Director::getInstance()->getWinSize();//ウィンドウサイズを取得
		//レティクルの挙動
		//プレイヤーの状態を取得して場合分け
		switch (GameMasterL->GetPlayerState())
		{
		case PSTATE_SHOT://攻撃中はレティクルを移動させる

			tPos = GameMasterL->GetTouchPos();//タッチ座標を取得
			tPos.y += size.height * GameMasterL->reticleAjust;//
			if (tPos.y >= size.height)
			{
				tPos.y = size.height;
			}

			UIBillBoard[UIKIND_RETICLE]->setPosition(tPos);

			break;
		case PSTATE_IDLE://アイドル状態

			UIBillBoard[UIKIND_RETICLE]->setVisible(true);
			break;
		case PSTATE_HIDE://隠れているa
		case PSTATE_APPEAR://隠れた状態から出る
		case PSTATE_DAMAGED://ダメージを受けた
			break;
		case PSTATE_RUN://走っている（Wait時）
			UIBillBoard[UIKIND_RETICLE]->setVisible(false);

			break;
		case PSTATE_DEAD://死亡
			//ウェイト時と死亡時はGSTATE_PLAYではないので、他のステート時は一括でUIの非表示を管理した方がよい
			//現在はここにも記述しておく
			UIBillBoard[UIKIND_RETICLE]->setVisible(false);
			break;
		}
	}


	

	//リロードアラートの挙動
	//プレイヤーの状態を取得して場合分け
	switch (GameMasterL->GetPlayerState())
	{
	case PSTATE_SHOT:
	case PSTATE_IDLE:
	case PSTATE_DAMAGED:
	case PSTATE_DODGE:
	case PSTATE_APPEAR://隠れた状態から出る
		if (GameMasterL->GetPlayerBullets() <= 0)
		{
			LogoUI::getInstance()->setLogo(LogoUI::Reload);
		}
		else
		{
			LogoUI::getInstance()->resetLogo(LogoUI::Reload);
		}
		/*
		if(GameMasterL->nowBullets <= 0)
		{
		UIBillBoard[UIKIND_RELOAD]->setVisible(true);
		}
		else
		{
		UIBillBoard[UIKIND_RELOAD]->setVisible(false);
		}
		*/
		break;
	case PSTATE_HIDE://隠れている
		LogoUI::getInstance()->resetLogo(LogoUI::Reload);
		//			UIBillBoard[UIKIND_RELOAD]->setVisible(false);
		break;
	case PSTATE_RUN://走っている（Wait時）
		LogoUI::getInstance()->resetLogo(LogoUI::Reload);
		//			UIBillBoard[UIKIND_RELOAD]->setVisible(false);
		break;
	case PSTATE_DEAD://死亡
		//ウェイト時と死亡時はGSTATE_PLAYではないので、他のステート時は一括でUIの非表示を管理した方がよい
		//現在はここにも記述しておく
		LogoUI::getInstance()->resetLogo(LogoUI::Reload);
		//			UIBillBoard[UIKIND_RELOAD]->setVisible(false);
		break;
	}


	//ウェイトUIの挙動
	//プレイヤーの状態を取得して場合分け
	switch (GameMasterL->GetPlayerState())
	{
		//		case PSTATE_SHOT:
		//		case PSTATE_IDLE:
		//		case PSTATE_DAMAGED:
		//		case PSTATE_DODGE:
		//		case PSTATE_APPEAR://隠れた状態から出る
		//		case PSTATE_HIDE://隠れている
		//		case PSTATE_DEAD://死亡
		//			LogoUI::getInstance() -> resetLogo( LogoUI::Wait);
		////			UIBillBoard[UIKIND_WAIT]->setVisible(false);
		//			break;
		//		case PSTATE_RUN://走っている（Wait時）
		//			static int count = 0;
		//			if( count % 60 == 0)
		//			{
		//				LogoUI::getInstance() -> setLogo( LogoUI::Wait);				
		//			}
		//			count++;
		////			UIBillBoard[UIKIND_WAIT]->setVisible(true);
		//			break;
	}

	//ウェイトUIとアクションUIの挙動
	//ゲームの状態を取得して場合分け
	switch (GameMasterL->GetGameState())
	{

	case GSTATE_INIT://
		break;
	case GSTATE_WAIT://ウェイト時
	{
		static int count = 0;
		if (count % 60 == 0)
		{
			LogoUI::getInstance()->setLogo(LogoUI::Wait);
		}
		count++;
		//			UIBillBoard[UIKIND_WAIT]->setVisible(true);
	}
		break;
	case GSTATE_PLAY_SET://戦闘開始前の待ち時間（敵の配置にのみ使用する）
		break;
	case GSTATE_PLAY_ACTION://戦闘開始前の待ち時間（ActionのUIを描画するときに使用する）
		LogoUI::getInstance()->setLogo(LogoUI::Action);
		break;
	case GSTATE_PLAY:
		break;
	case GSTATE_PAUSE:
		break;
	case GSTATE_CONTINUE:
		break;
	case GSTATE_GAMEOVER:
		break;
	case GSTATE_EVENT://ムービーイベントなどを進行させるときに使用する？（現在未使用）
		break;
	default:
		break;
	}


	//アクションUIの挙動
	//プレイヤーの状態を取得して場合分け
	switch (GameMasterL->GetPlayerState())
	{
	case PSTATE_SHOT:
	case PSTATE_IDLE:
	case PSTATE_DAMAGED:
	case PSTATE_DODGE:
	case PSTATE_APPEAR://隠れた状態から出る
	case PSTATE_HIDE://隠れている
	case PSTATE_RUN://走っている（Wait時）
	case PSTATE_DEAD://死亡

		break;
	}

}



/*
現在は親シーンのupdateで更新系の関数を呼び出しているので、レイヤー固有のmoveTime関数は使用していません
*/
void GameUILayer::moveTime(float delta)
{

}


/*
現在は親シーンのupdateで更新系の関数を呼び出しているので、レイヤー固有のUpdate関数は使用していません
*/
void GameUILayer::update(float delta)
{

}


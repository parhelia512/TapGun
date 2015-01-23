
#include "GameUILayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
//#include "C++/Base/UI.h"

#else

#include "C++/Base/GameMaster.h"
//#include "C++/Base/UI.h"

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
	for(int i = 0; i < MAX_UI; i++)
	{
		if(FALSE == Ui[i].valid)
		{
			return i;
		}
	}
	return -1;//全てのUISpriteが使用されていたら-1を返す
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "reticle.png";
#else
	std::string fileName1 = "Graph/Pictures/reticle.png";
#endif
	int num = SerchFreeUI();
	//レティクル
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "reticle.png";
#else
	fileName1 = "Graph/Pictures/reticle.png";
#endif
	
	auto s = Director::getInstance()->getWinSize();//スクリーンサイズを取得
	UIBillBoard[UIKIND_RETICLE] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
	UIBillBoard[UIKIND_RETICLE]->setPosition(s.width / 2, s.height / 2);
	UIBillBoard[UIKIND_RETICLE]->setScale(0.3f);
	addChild(UIBillBoard[UIKIND_RETICLE]);

	Ui[UIKIND_RETICLE].Init(num, UIKIND_RETICLE);
	valid[UIKIND_RETICLE] = TRUE;

	////矢印の初期化
	//fileName1 = "Graph/Pictures/kaihiai.png";
	//UIBillBoard[UIKIND_ARROW] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
	//UIBillBoard[UIKIND_ARROW]->setPosition(120.0f, 100.0f);
	//UIBillBoard[UIKIND_ARROW]->setScale(1.0f);
	//addChild(UIBillBoard[UIKIND_ARROW]);

	//Ui[UIKIND_ARROW].Init(UIKIND_ARROW, UIKIND_ARROW);
	//valid[UIKIND_ARROW] = TRUE;

	////ライフバーの初期化
	//fileName1 = "Graph/Pictures/tairyoku_tama.png";
	//UIBillBoard[UIKIND_LIFEBAR] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
	//UIBillBoard[UIKIND_LIFEBAR]->setPosition(100, 150);
	//UIBillBoard[UIKIND_LIFEBAR]->setScale(1.0f);
	//addChild(UIBillBoard[UIKIND_LIFEBAR]);

	//Ui[UIKIND_LIFEBAR].Init(UIKIND_LIFEBAR, UIKIND_LIFEBAR);
	//valid[UIKIND_LIFEBAR] = TRUE;

	////弾数Ａ（アイコン）
	//fileName1 = "Graph/Pictures/time.png";
	//UIBillBoard[UKIND_BULLET_A] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
	//UIBillBoard[UKIND_BULLET_A]->setPosition(1085, 760);
	//UIBillBoard[UKIND_BULLET_A]->setScale(1.0f);
	//addChild(UIBillBoard[UKIND_BULLET_A]);

	//Ui[UKIND_BULLET_A].Init(UKIND_BULLET_A, UKIND_BULLET_A);
	//valid[UKIND_BULLET_A] = TRUE;

	////弾数Ｂ（数字）
	//fileName1 = "Graph/Pictures/timelogo.png";
	//UIBillBoard[UKIND_BULLET_B] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
	//UIBillBoard[UKIND_BULLET_B]->setPosition(250, 80);
	//UIBillBoard[UKIND_BULLET_B]->setScale(1.0f);
	//addChild(UIBillBoard[UKIND_BULLET_B]);

	//Ui[UKIND_BULLET_B].Init(UKIND_BULLET_B, UKIND_BULLET_B);
	//valid[UKIND_BULLET_B] = TRUE;
	Sprite* sprite[4];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sprite[0] = Sprite::create("tairyoku_tama.png");
	sprite[1] = Sprite::create("time.png");
	sprite[2] = Sprite::create("kaihiai.png");
	sprite[3] = Sprite::create("timelogo.png");
#else
	sprite[0] = Sprite::create("Graph/Pictures/tairyoku_tama.png");
	sprite[1] = Sprite::create("Graph/Pictures/time.png");
	sprite[2] = Sprite::create("Graph/Pictures/kaihiai.png");
	sprite[3] = Sprite::create("Graph/Pictures/timelogo.png");
#endif
	sprite[0]->setPosition(Vec2(285, 695));
	sprite[1]->setPosition(Vec2(1085, 760));
	sprite[2]->setPosition(Vec2(100, 150));
	sprite[3]->setPosition(Vec2(250, 80));

	for(auto &p : sprite) addChild(p);
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
	if(TRUE == valid[UIKIND_RETICLE])//初期化チェックは不要にならば消す
	{
		Vec2 tPos;
		int a = 0;
		//プレイヤーの状態を取得して場合分け
		switch(GameMasterL->GetPlayerState())
		{
		case PSTATE_SHOT://攻撃中はレティクルを移動させる

			tPos = GameMasterL->GetTouchPos();//
//			tPos = GameMasterL->GetTouchPosInView();//
			UIBillBoard[UIKIND_RETICLE]->setPosition(tPos);
			break;

		case PSTATE_IDLE://アイドル状態
			UIBillBoard[UIKIND_RETICLE]->setVisible(true);/*b*/
			break;
 		case PSTATE_HIDE://隠れている
		case PSTATE_APPEAR://隠れた状態から出る
		case PSTATE_DAMAGED://ダメージを受けた
			break;
		case PSTATE_RUN://走っている（Wait時）
			UIBillBoard[UIKIND_RETICLE]->setVisible(false);/*b*/
			break;
		case PSTATE_DEAD://死亡
			//ウェイト時と死亡時はGSTATE_PLAYではないので、他のステート時は一括でUIの非表示を管理した方がよい
			//現在はここにも記述しておく
			UIBillBoard[UIKIND_RETICLE]->setVisible(false);/*-*/
			break;
		}
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


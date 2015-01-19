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

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameUILayer::moveTime), 0.016f);

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



void GameUILayer::SetUI()
{
	std::string fileName1 = "Graph/Pictures/lifebar.png";
	int num = SerchFreeUI();

	//ライフバーの初期化
	if(-1 != num)
	{
		UIBillBoard[num] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
		UIBillBoard[num]->setPosition(230.0f, 750.0f);
		UIBillBoard[num]->setScale(0.8f);
		addChild(UIBillBoard[num]);
		
		Ui[num].Init(num,UIKIND_LIFEBAR);
		valid[num] = TRUE;
	}

	fileName1 = "Graph/Pictures/arrow.png";
	num = SerchFreeUI();
	//矢印の初期化
	if(-1 != num)
	{
		UIBillBoard[num] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
		UIBillBoard[num]->setPosition(50.0f, 50.0f);
		UIBillBoard[num]->setScale(0.5f);
		addChild(UIBillBoard[num]);

		Ui[num].Init(num, UIKIND_ARROW);
		valid[num] = TRUE;
	}


	fileName1 = "Graph/Pictures/reticle.png";
	num = SerchFreeUI();
	//レティクル
	if(-1 != num)
	{
		UIBillBoard[num] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
		UIBillBoard[num]->setPosition(850.0f, 400.0f);
		UIBillBoard[num]->setScale(0.25f);
		addChild(UIBillBoard[num]);

		Ui[num].Init(num, UIKIND_RETICLE);
		valid[num] = TRUE;
	}
}


void GameUILayer::InitAllUI()
{
	for(int i = 0; i < MAX_UI; i++)
	{
		Ui[i].Init();
	}
}


void GameUILayer::UpdateUI(float camX, float camY, float camZ, float rotX, float rotY, float rotZ)
{
	Vec3 camPos;
	camPos.x = camX;
	camPos.y = camY;
	camPos.z = camZ;

	Vec3 camRot;
	camRot.x = rotX;
	camRot.y = rotY;
	camRot.z = rotZ;


	for(int i = 0; i < MAX_UI; i++)
	{
		if(FALSE != Ui[i].valid)
		{
			//UINode[i]->setPosition3D(camPos);
			//UINode[i]->setRotation3D(camRot);
		}
	}
}




void GameUILayer::MoveReticle(void)
{
	for(int i = 0; i < MAX_UI; i++)
	{
		if(FALSE != Ui[i].valid)
		{
			//UINode[i]->setPosition3D(camPos);
			//UINode[i]->setRotation3D(camRot);
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




bool GameUILayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{


	return true;
}


void GameUILayer::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	Director *pDirector;
	Point touchPoint;
	Node *pNode;
	Rect spRect;

}


void GameUILayer::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{

}


//void GameUILayer::onTouchCancelled = CC_CALLBACK_2(GameUILayer::onTouchCancelled, this);
//{
//
//	//画面をタッチした時の処理
//
//}
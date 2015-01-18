#include "GameUILayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
#include "C++/Base/UI.h"

#else

#include "C++/Base/GameMaster.h"
#include "C++/Base/UI.h"

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
		if(FALSE == UISprite[i]->valid)
		{
			return i;
		}
	}
	return -1;//全てのUISpriteが使用されていたら-1を返す
}



void GameUILayer::SetUI()
{
	std::string fileName1 = "Graph/Pictures/ty.png";

	int num = SerchFreeUI();

	//ライフバーの初期化
	if (-1 != num)
	{
		//UISprite[num] = new UI;
		//UISprite[num];

		//valid[num] = 1;
		//UIBillBoard[num] = cocos2d::BillBoard::create(fileName1, BillBoard::Mode::VIEW_PLANE_ORIENTED);
		//UIBillBoard[num]->setPosition(30.0f, 30.0f);
		//UIBillBoard[num]->setScale(0.5f);
		//UINode[num] = Node::create();//モデルの親ノード
		//UINode[num]->addChild(UIBillBoard[num]);
		//addChild(UINode[num]);
		//UIBillBoard[num]->setCameraMask(CAMFLAG_3D);
	}
}


void GameUILayer::InitAllUI()
{
	for(int i = 0; i < MAX_UI; i++)
	{
		UISprite[i]->valid = false;
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
		if(FALSE != UISprite[i]->valid)
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
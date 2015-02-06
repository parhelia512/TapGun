#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include"GameMaster.h"

#else

#include"C++/Base/GameMaster.h"
 
#endif

//#define CN//カメラノードを使用するテスト

USING_NS_CC;
using namespace TapGun;

//実態をNULLで初期化
Camera* GameMaster::camera3D = NULL;
Camera* GameMaster::camera2D = NULL;
Node* GameMaster::CamNode = NULL;

/**
*	ゲームパラメータクラスの生成
*
*	@author	sasebon
*	@param	なし
*	@return	パラメータクラスの値
*	@date	1/16 Ver 1.0
*/
GameMaster* GameMaster::GetInstance(void)
{
	static GameMaster* P;
	if(!P)
	{
		P = new GameMaster;

	}
	return P;
}


/**
*	スクリーンサイズの取得
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::InitScreenSize(void)
{
	//引数なしの場合は自動取得
	//引数を指定することで、スクリーンサイズを任意の値に設定できるようにする？
	screenSize = Director::getInstance()->getWinSize();//スクリーンサイズを取得
}


/**
*	2Dカメラのインスタンス
*
*	@author	sasebon
*	@param	なし
*	@return	2D用カメラ
*	@date	1/16 Ver 1.0
*/
Camera* GameMaster::Get2DCamInstance(void)
{
	if(!camera2D)
	{
		GameMaster::camera2D = Camera::create();
	}
	return camera2D;
}



/**
*	3Dカメラのインスタンス
*
*	@author	sasebon
*	@param	なし
*	@return	3D用カメラ
*	@date	1/16 Ver 1.0
*/
Camera* GameMaster::Get3DCamInstance(void)
{
	if(!camera3D)
	{
		GameMaster::camera3D = Camera::create();
		GameMaster::CamNode = Node::create();
	}
//	return CamNode;
	return camera3D;
}




Node* GameMaster::GetCamNodeInstance(void)
{
	if(!CamNode)
	{
		GameMaster::CamNode = Node::create();
	}
	return CamNode;
}



//====set=====================================


/**
*	ゲームパラメータの初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::InitParam()
{
	playerState = PSTATE_IDLE;
	gameState = GSTATE_INIT;
	wave = 0;
	playerHP = 6;

	touchState = TSTATE_OFF;
	touchFlag = TFLAG_OFF;

	gameTime = 100;
	
	sPoint = 0;
	//プレイヤーの移動ポイントを設定する
	for(int i = 0; i < 100; i++)
	{
		//初期化
		stagePoint[i].pos = Vec3(0.0f, 0.0f, 0.0f);
		stagePoint[i].rot = Vec3(0.0f, 0.0f, 0.0f);
		stagePoint[i].pointType = POINT_NONE;
		stagePoint[i].playerSide = PSIDE_RIGHT;//初期化は全てRIGHT
	}
	//stagePointの定義

	//ゲーム開始地点
	stagePoint[POINT_START].pos = Vec3(-12.0f, 0.0f, 43.0f);//
	stagePoint[POINT_START].rot = Vec3(0.0f, 140.0f, 0.0f);
	stagePoint[POINT_START].pointType = POINT_NONE;

	//ステージ１
//	stagePoint[POINT_STAGE1].pos = Vec3(-3.8f, 0.0f, 34.0f);//
//	stagePoint[POINT_STAGE1].rot = Vec3(0.0f, 165.0f, 0.0f);
	stagePoint[POINT_STAGE1].pos = Vec3(-3.9f, 0.0f, 37.0f);//
	stagePoint[POINT_STAGE1].rot = Vec3(0.0f, 180.0f, 0.0f);

	//一時的
//	stagePoint[POINT_START].pos = Vec3(5.0f, 0.0f, 2.0f);//
//	stagePoint[POINT_STAGE1].pos = Vec3(5.0f, 0.0f, 2.0f);//
//	stagePoint[POINT_STAGE1].rot = Vec3(0.0f, -60.0f, 0.0f);


	stagePoint[POINT_STAGE1].pointType = POINT_BATTLE;
	stagePoint[POINT_STAGE1].playerSide = PSIDE_LEFT;
	stagePoint[POINT_STAGE1].hidePoint = setHidePoint(stagePoint[POINT_STAGE1]);

	//連結ポイント
	stagePoint[POINT_S2_1].pos = Vec3(14.1f, 0.0f, 5.0f);
	stagePoint[POINT_S2_1].rot = Vec3(0.0f, 170.0f, 0.0f);
	stagePoint[POINT_S2_1].pointType = POINT_CHANGE;

	//ステージ２
	stagePoint[POINT_STAGE2].pos = Vec3(13.8f, 0.0f, 3.3f);
	stagePoint[POINT_STAGE2].rot = Vec3(0.0f, 175.0f, 0.0f);
	stagePoint[POINT_STAGE2].pointType = POINT_BATTLE;

	//連結ポイント
	stagePoint[POINT_S3_1].pos = Vec3(16.2f, 0.0f, 1.3f);
	stagePoint[POINT_S3_1].rot = Vec3(0.0f, 185.0f, 0.0f);
	stagePoint[POINT_S3_1].pointType = POINT_CHANGE;

	//クリア
	stagePoint[POINT_FINISH].pos = Vec3(14.7f, 0.0f, -4.5f);
	stagePoint[POINT_FINISH].rot = Vec3(0.0f, 165.0f, 0.0f);
	stagePoint[POINT_FINISH].pointType = POINT_NONE;
}



/**
*	ゲームパラメータクラスの初期化
*
*	@author	sasebon
*	@param	指定したウェーブ番号
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::InitParam(int wave)
{

}


/**
*	2D用カメラの座標セット
*
*	@author	sasebon
*	@param	指定の3次元ベクトル
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetCamera2DPos(cocos2d::Vec3 pos)
{
	camera2D->setPosition3D(pos);
}


/**
*	3D用カメラの座標セット
*
*	@author	sasebon
*	@param	カメラ座標
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetCamera3DPos(cocos2d::Vec3 pos)
{
	camera3D->setPosition3D(pos);
}



/**
*	3D用カメラの角度セット
*
*	@author	sasebon
*	@param	カメラ角度
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetCamera3DRot(cocos2d::Vec3 rot)
{
	//この関数は基本的に使わず、親ノードの回転で対応する
	camera3D->setRotation3D(rot);
}


/**
*	3D用カメラの座標加算
*
*	@author	sasebon
*	@param	加算するカメラ座標
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::AddCamera3DPos(cocos2d::Vec3 pos)
{
	camera3D->setPosition3D(camera3D->getPosition3D() + pos);
}


/**
*	3D用カメラの角度加算
*
*	@author	sasebon
*	@param	加算するカメラ角度
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::AddCamera3DRot(cocos2d::Vec3 rot)
{
	//この関数は基本的に使わず、親ノードの回転で対応する
	camera3D->setRotation3D(camera3D->getRotation3D() + rot);
}




/**
*	3D用カメラのノード座標セット
*
*	@author	sasebon
*	@param	カメラ座標
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetCameraNodePos(cocos2d::Vec3 pos)
{
	CamNode->setPosition3D(pos);
}



/**
*	3D用カメラのノード角度セット
*
*	@author	sasebon
*	@param	カメラ角度
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetCameraNodeRot(cocos2d::Vec3 rot)
{
	//カメラの回転は基本的にこちらを使用する
	CamNode->setRotation3D(rot);
}


/**
*	3D用カメラのノード座標加算
*
*	@author	sasebon
*	@param	加算するカメラ座標
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::AddCameraNodePos(cocos2d::Vec3 pos)
{
	CamNode->setPosition3D(camera3D->getPosition3D() + pos);
}


/**
*	3D用カメラのノード角度加算
*
*	@author	sasebon
*	@param	加算するカメラ角度
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::AddCameraNodeRot(cocos2d::Vec3 rot)
{
	CamNode->setRotation3D(camera3D->getRotation3D() + rot);
}



/**
*	3D用カメラの初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::InitCamera3D()
{
	//今後、ゲームやプレイヤーの状態などで様々なカメラセットが出来るようにする？
	//camera3D->createPerspective(20, (GLfloat)s.width / s.height, 1, 1000);

	//

	CamNode = Node::create();
	camera3D = Camera::createPerspective(C_PERSE_L, (GLfloat)screenSize.width / screenSize.height, 1, 1000);

	//

	camera3D->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0, 1, 0));//lookAtは原点に置き、setPositionで視点を動かします。
	camera3D->setCameraFlag(CameraFlag::USER1);//USER1を3D用にする

	CamNode->addChild(camera3D);
}


/**
*	2D用カメラの初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::InitCamera2D()
{
	//今後、ゲームやプレイヤーの状態などで様々なカメラセットが出来るようにする？
	//camera3D->createPerspective(20, (GLfloat)s.width / s.height, 1, 1000);

	//
	camera2D = Camera::createOrthographic(screenSize.width, screenSize.height, 0, 100);//
	camera2D->setCameraFlag(CameraFlag::DEFAULT);//
}


/**
*	プレイヤー状態のセット
*
*	@author	sasebon
*	@param	playerState
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetPlayerState(int state)
{
	playerState = state;
}



/**
*	タッチ座標のセット
*
*	@author	sasebon
*	@param	なし
*	@return	タッチ座標の二次元ベクトル
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetTouchPos(Touch* tch)
{
	touch = tch;
}




/**
*	タッチマネージャーの更新
*
*	@author	sasebon
*	@param	タッチ状態
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::UpdateTouchManager( void)
{
	switch(touchState)
	{
	case TSTATE_OFF://タッチしていない状態で

		if(TFLAG_ON == touchFlag)//タッチフラグが立った
		{
			touchState = TSTATE_ON;//タッチした状態にする
		}
		break;
	case TSTATE_ON://タッチした状態で

		if(TFLAG_MOVE == touchFlag)//移動した
		{
			touchState = TSTATE_MOVE;//移動した状態にする
		}
		else if(TFLAG_RELEASE == touchFlag)//離した
		{
			touchState = TSTATE_RELEASE;//離した状態にする
			touchFlag = TFLAG_OFF;//タッチフラグもOFFにする
		}
		else//それ以外の場合
		{
			touchState = TSTATE_ON;//タッチした状態のまま
		}

		break;
	case TSTATE_MOVE://移動中

		if(TFLAG_MOVE == touchFlag)//移動した
		{
			touchState = TSTATE_MOVE;//移動した状態のまま
		}
		else if(TFLAG_RELEASE == touchFlag)//離した
		{
			touchState = TSTATE_RELEASE;//離した状態にする
			touchFlag = TFLAG_OFF;//タッチフラグもOFFにする
		}
		else//それ以外の場合
		{
			touchState = TSTATE_ON;//タッチした状態にする
		}
		break;
	case TSTATE_RELEASE:
		touchState = TSTATE_OFF;
		touchFlag = TFLAG_OFF;//タッチフラグもOFFにする
		break;
	}
}


/**
*	タッチフラグのセット
*
*	@author	sasebon
*	@param	指定のタッチフラグ
*	@return	1:引数が正常 -1:無効な引数
*	@date	1/16 Ver 1.0
*/
int GameMaster::SetTouchFlag(int flag)
{
	if(TFLAG_NUM <= flag || 0 > flag)
	{
		touchFlag = 0;//
		return FALSE;
	}
	touchFlag = flag;
	return TRUE;
}


/**
*	2D用カメラの取得
*
*	@author	sasebon
*	@param	なし
*	@return	2D用Cemera
*	@date	1/16 Ver 1.0
*/
Camera* GameMaster::GetCamera2D(void)
{
	return camera2D;
}


/**
*	3D用カメラの取得
*
*	@author	sasebon
*	@param	なし
*	@return	3D用Cemera
*	@date	1/16 Ver 1.0
*/
Camera* GameMaster::GetCamera3D(void)
{
	return camera3D;
}



/**
*	3D用カメラの親ノードの取得
*
*	@author	sasebon
*	@param	なし
*	@return	3D用Cemera
*	@date	1/16 Ver 1.0
*/
const Node* GameMaster::GetCameraNode(void)
{
	return CamNode;
}


/**
*	プレイヤー状態の取得
*
*	@author	sasebon
*	@param	なし
*	@return	現在のplayerState
*	@date	1/16 Ver 1.0
*/
int GameMaster::GetPlayerState(void)
{
	return playerState;
}





/**
*	ゲーム状態のセット
*
*	@author	sasebon
*	@param	gameState
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetGameState(int gState)
{
	gameState = gState;
	if(GSTATE_WAIT == gState)
	{
		waitFlag = 0;//ウェイトフラグも一緒に初期化する
	}
}


/**
*	ゲーム状態の取得
*
*	@author	sasebon
*	@param	なし
*	@return	現在のGameState
*	@date	1/16 Ver 1.0
*/
int GameMaster::GetGameState(void)
{
	return gameState;
}




/**
*	タッチ座標の取得
*
*	@author	sasebon
*	@param	なし
*	@return	タッチ座標の二次元ベクトル
*	@date	1/16 Ver 1.0
*/
Vec2 GameMaster::GetTouchPosInView()
{
	return touch->getLocationInView();
}


/**
*	タッチ座標の取得
*
*	@author	sasebon
*	@param	なし
*	@return	タッチ座標の二次元ベクトル
*	@date	1/16 Ver 1.0
*/
Vec2 GameMaster::GetTouchPos()
{
	return touch->getLocation();
}



/**
*	タッチ状態の取得
*
*	@author	sasebon
*	@param	なし
*	@return	タッチ座標の二次元ベクトル
*	@date	1/16 Ver 1.0
*/
int GameMaster::GetTouchFlag(void)
{
	return touchFlag;
}



/**
*	タッチ状態の取得
*
*	@author	sasebon
*	@param	なし
*	@return	タッチ座標の二次元ベクトル
*	@date	1/16 Ver 1.0
*/
int GameMaster::GetTouchState(void)
{
	return touchState;
}





/**
*	回避動作の軸座標の計算
*
*	@author	sasebon
*	@param	stagePoint
*	@return	軸座標
*	@date	2/1 Ver 1.0
*/
Vec2 GameMaster::setHidePoint(StagePoint stagePoint)
{
	Vec2 hidePoint = Vec2(-HIDEPOINT_X, -HIDEPOINT_Y);

	if(PSIDE_LEFT == stagePoint.playerSide)
	{
		hidePoint.x = hidePoint.x * cosf(stagePoint.rot.y) - hidePoint.y * sinf(stagePoint.rot.y);
		hidePoint.y = hidePoint.x * sinf(stagePoint.rot.y) + hidePoint.y * cosf(stagePoint.rot.y);
	}
	else
	{
		hidePoint = Vec2(HIDEPOINT_X, -HIDEPOINT_Y);

		hidePoint.x = hidePoint.x * cosf(stagePoint.rot.y) - hidePoint.y * sinf(stagePoint.rot.y);
		hidePoint.y = hidePoint.x * sinf(stagePoint.rot.y) + hidePoint.y * cosf(stagePoint.rot.y);
	}
	return hidePoint;
}


/**
*	プレイヤーHPのゲッター
*
*	@author	minaka
*	@param	なし
*	@return	HP
*	@date	2/6 Ver 1.0
*/
float GameMaster::GetPlayerHP(void)
{
	return playerHP;
}

/**
*	プレイヤーHPのセッター
*
*	@author	minaka
*	@param	パラメーター
*	@return	なし
*	@date	2/6 Ver 1.0
*/
void GameMaster::SetPlayerHP(float value)
{
	playerHP = value;
}
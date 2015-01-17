
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include"GameMaster.h"

#else

#include "C++/System/GameMaster.h"
 
#endif

USING_NS_CC;
using namespace TapGun;


Camera* GameMaster::camera3D = Camera::create();
Camera* GameMaster::camera2D = Camera::create();

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
*	2Dカメラのインスタンス
*
*	@author	sasebon
*	@param	なし
*	@return	2D用カメラ
*	@date	1/16 Ver 1.0
*/
void GameMaster::InitScreenSize(void)
{
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
	return camera3D;
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
	touchPos = Vec2(0.0f, 0.0f);
	wave = 0;
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
void GameMaster::SetCamera2D(cocos2d::Vec3 pos)
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
	camera3D->setRotation3D(camera3D->getRotation3D() + rot);
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
	camera3D = Camera::createPerspective(20, (GLfloat)screenSize.width / screenSize.height, 1, 1000);
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
*	ゲーム状態のセット
*
*	@author	sasebon
*	@param	gameState
*	@return	なし
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetGameState(int state)
{
	gameState = state;
}

/**
*	タッチ座標のセット
*
*	@author	sasebon
*	@param	なし
*	@return	タッチ座標の二次元ベクトル
*	@date	1/16 Ver 1.0
*/
void GameMaster::SetTouchPos(Vec2 tPos)
{
	touchPos = tPos;
}


//====get=====================================


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
Vec2 GameMaster::GetTouchPos(void)
{
	return touchPos;
}

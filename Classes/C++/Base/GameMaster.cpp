#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include"GameMaster.h"

#else

#include"C++/Base/GameMaster.h"
 
#endif


USING_NS_CC;
using namespace TapGun;

//実態をNULLで初期化
Camera* GameMaster::camera3D = NULL;
Camera* GameMaster::camera2D = NULL;


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
	}

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
	wave = 0;

	touchState = TSTATE_OFF;
	touchFlag = TFLAG_OFF;
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
	camera3D->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0, 1, 0));//lookAtは原点に置き、setPositionで視点を動かします。
	camera3D->setCameraFlag(CameraFlag::USER1);//USER1を3D用にする
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

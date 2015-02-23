
#include "GameScene.h"

//各レイヤーを管理するソースコードをインクルードしておく

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameModelsLayer.h"
#include "GameUILayer.h"
#include "GameMaster.h"
#include "Sound.h"

#else

#include "Scene/GameModelsLayer.h"
#include "Scene/GameUILayer.h"
#include "Base/GameMaster.h"
#include "System/Sound.h"

#endif

USING_NS_CC;
using namespace TapGun;

Sound* sound;



/*
GameScene
（将来的にGameSceneなどに名前を変更する）
ゲーム本編の更新処理を行う
ここで処理された内容を元に、モデルデータを扱うレイヤーとＵＩを扱うレイヤーで描画を行う
*/

GameMaster* GameMasterS;//とりあえず名前を変えるか名前空間で区別する

GameModelsLayer* gGameLayer;
GameUILayer* gUILayer;

static GameScene *multiSceneLayerInstance;

/**
*	ゲーム管理シーンクリエイト
*
*	@author	sasebon
*	@param	なし
*	@return	シーンのポインタ
*	@date	1/8 Ver 1.0
*/
Scene* GameScene::CreateScene()
{
	Scene *scene = Scene::create();//GameSceneのシーンを作成
	GameScene *layer = GameScene::create();//上記シーンに

	scene->addChild(layer);

	return scene;
};




/**
*	ゲームシーン初期化
*
*	@author	sasebon
*	@param	なし
*	@return	正常:1 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
bool GameScene::init()
{
	//レイヤー初期化
	if (!Layer::init())
	{
		return false;
	}

	//ゲームレイヤーを作成
	gGameLayer = GameModelsLayer::create();
	this->addChild(gGameLayer);


	//UIレイヤーを作成
	gUILayer = GameUILayer::create();
	this->addChild(gUILayer);


	GameMasterS = GameMaster::GetInstance();//ゲームパラメータクラスのインスタンス生成
	GameMasterS->InitScreenSize();//スクリーンサイズのセット
	GameMasterS->InitParam();//ゲームパラメータの初期化


	//現在はタッチイベントのリスナーをここに用意しています
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	sound = Sound::getInstance();

	//sound -> loadBGM( "testBGM.mp3");
	//sound -> playBGM();
	sound->loadSE("Shot.wav");
	sound->loadSE("Damage_01.wav");
	sound->loadSE("Damage_02.wav");
	sound->loadSE("Damage_03.wav");
	sound->loadSE("Damage_04.wav");

	this->scheduleUpdate();
	//	this->schedule(schedule_selector(GameScene::moveTime), 0.016f);//1秒60Fでゲーム更新


	//時間取得のための変数を初期化
	GameMasterS->nowTV = new timeval;
	GameMasterS->preTV = new timeval;
	gettimeofday(GameMasterS->nowTV, nullptr);
	gettimeofday(GameMasterS->preTV, nullptr);
	GameMasterS->loopTime = 0.0166f;
	//
	GameMasterS->reticleAjust = 0.1f;//

	return true;
}


/**
*	ゲームシーンのカメラ初期化
*
*	@author	sasebon
*	@param	なし
*	@return	正常:1
*	@date	1/8 Ver 1.0
*/
int GameScene::InitCamera()
{
	auto s = Director::getInstance()->getWinSize();

	//2D用カメラの実装
	if (NULL != gUILayer)
	{
		GameMasterS->InitCamera2D();//カメラを初期化
		gUILayer->setCameraMask(CAMFLAG_DEFAULT);
		addChild(GameMasterS->Get2DCamInstance());
	}

	//3D用カメラの実装
	if (NULL != gGameLayer)
	{
		GameMasterS->InitCamera3D();//カメラを初期化（ノードにaddChildもする）
		gGameLayer->setCameraMask(CAMFLAG_3D);

		//プレイヤーの座標取得はとりあえずこのような形で記述しています
		Vec3 cameraPos = gGameLayer->player.wrapper->getPosition3D() - gGameLayer->player.sprite3d->getPosition3D();


		//ノードを意識する座標
		GameMasterS->SetCameraNodePos(cameraPos);//ノードは常にプレイヤーの座標に一致
		GameMasterS->SetCameraNodeRot(gGameLayer->player.sprite3d->getRotation3D());//ノード回転もプレイヤーをもとに設定

		GameMasterS->SetCamera3DPos(Vec3(C_SETX_L, C_SETY_L, C_SETZ_L));//プレイヤー（親ノード）とカメラの位置関係をセット
		GameMasterS->SetCamera3DRot(Vec3(C_ROTX_L, C_ROTY_L, C_ROTZ_L));

		GameMasterS->GetCameraNode();
		GameMasterS->Get3DCamInstance();
		addChild(GameMasterS->GetCamNodeInstance());
	}
	return TRUE;
}



/**
*	指定フレームごとのゲームシーン更新（現在使用していません）
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameScene::moveTime(float delta)
{
}



/**
*	ゲームシーン更新（ゲームタイミング更新にはこちらを使用します）
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameScene::update(float delta)
{
	GameMasterS->gameTime -= 0.8f;
	GameMasterS->UpdateTouchManager();//タッチ情報を更新


	//1ループ前の時刻を取得
	GameMasterS->preTV->tv_sec = GameMasterS->nowTV->tv_sec;
	GameMasterS->preTV->tv_usec = GameMasterS->nowTV->tv_usec;

	//現在時刻を取得
	gettimeofday(GameMasterS->nowTV, nullptr);
	//現在時刻を計算

	GameMasterS->preTime = GameMasterS->preTV->tv_sec * 1000.0f + GameMasterS->preTV->tv_usec * 0.001f;
	GameMasterS->nowTime = GameMasterS->nowTV->tv_sec * 1000.0f + GameMasterS->nowTV->tv_usec * 0.001f;

	//ループにかかった時間を計測(秒)
	GameMasterS->loopTime = (GameMasterS->nowTime - GameMasterS->preTime) * 0.001f;

	auto d = Director::getInstance()->getDeltaTime();



	//現在のゲームの状態でゲーム分岐
	switch(GameMasterS->GetGameState())
	{
		//ゲームの残り時間はGameModelsLayer内で管理します

	case GSTATE_INIT:
		if(NULL != gGameLayer)//現在は子レイヤーをクリエイトしたかを確認する
		{
			gGameLayer->InitLayer();//
		}
		if(NULL != gUILayer)//現在は子レイヤーをクリエイトしたかを確認する
		{
			gUILayer->InitLayer();//
		}

		InitCamera();
		GameMasterS->SetGameState(GSTATE_WAIT);
		GameMasterS->SetPlayerState(PSTATE_RUN);

		break;

	case GSTATE_WAIT:

		gGameLayer->UpdateWait();
		//gGameLayer->UpdatePlayer();//プレイヤーの更新はUpdateWait内で行います

		gUILayer->UpdateLayer();
		UpdateCamera();//モデルの移動をもとにカメラ移動

		break;
	case GSTATE_PLAY_SET://ウェイト終了後プレイ前の処理

		//敵の配置を行う
		gGameLayer->SetEnemy();
		GameMasterS->SetGameState(GSTATE_PLAY_ACTION);
		timeCount = 0.0f;
		break;
	case GSTATE_PLAY_ACTION:

		//シーン切り替え用の変数
		timeCount += GameMasterS->loopTime;//

		if(timeCount >= TIME_ACTION_UI)
		{
			//一定時間経過したらウェーブを開始する
			timeCount = 0.0f;
			GameMasterS->SetGameState(GSTATE_PLAY);
		}
		else
		{
			if(NULL != gUILayer)//現在は初期化チェック確認する
			{
				gUILayer->UpdateLayer();
			}
		}
		break;
	case GSTATE_PLAY:

		gGameLayer->UpdatePlayer();//プレイヤーの更新
		gGameLayer->UpdateEnemy();//エネミーの更新
		gGameLayer->UpdateBullets();//敵弾の更新
		gGameLayer->CheckHit();//当たり判定とダメージのチェック

		//プレイヤーが死亡したら
		if(PSTATE_CONTINUE == GameMasterS->GetPlayerState())
		{
			GameMasterS->SetGameState(GSTATE_CONTINUE_INIT);
			break;
		}
		else
		{
			gGameLayer->CheckNextStage();//
		}

		gUILayer->UpdateLayer();
		UpdateCamera();//モデルの移動をもとにカメラ移動

		break;

	case GSTATE_PAUSE:
		//ポーズ中は専用のレイヤーを描画する？
		//モデルの更新処理を制限する

		break;
	case GSTATE_CONTINUE_INIT:
		//コンティニュー前の準備



		break;
	case GSTATE_CONTINUE:

		break;
	case GSTATE_GAMEOVER:

		//ゲームオーバー用シーンに切り替える

		break;
	case GSTATE_EVENT:

		break;
	}
}



/**
*	ゲームシーンのカメラ更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
int GameScene::UpdateCamera()
{
	if(NULL != gUILayer)
	{
		//
	}

	if(NULL != gGameLayer)
	{
		//プレイヤーの座標取得はとりあえずこのような形で記述しています
		Vec3 cameraPos;
		Vec3 cameraRot;
		//プレイヤーの状態でカメラの位置を調整する
		switch(GameMasterS->GetPlayerState())
		{

		case PSTATE_DODGE:
			cameraPos = gGameLayer->player.wrapper->getPosition3D() + gGameLayer->player.sprite3d->getPosition3D() + gGameLayer->player.cameraAjust;
			cameraRot = gGameLayer->player.wrapper->getRotation3D() + gGameLayer->player.sprite3d->getRotation3D();


			//		プレイヤーの座標にカメラのノードを置く
			//GameMasterS->SetCameraNodePos(gGameLayer->player.cameraAjust);
			GameMasterS->SetCameraNodePos(cameraPos);

			//		カメラを公転させる
			cameraRot.y -= 180.0f;//プレイヤーは180度回転させているので補正を行う
			GameMasterS->SetCameraNodeRot(cameraRot);
			break;
		case PSTATE_HIDE:

			cameraPos = gGameLayer->player.wrapper->getPosition3D() + gGameLayer->player.sprite3d->getPosition3D() + gGameLayer->player.cameraAjust;
			cameraRot = gGameLayer->player.wrapper->getRotation3D() + gGameLayer->player.sprite3d->getRotation3D();


			//		プレイヤーの座標にカメラのノードを置く
			//GameMasterS->SetCameraNodePos(gGameLayer->player.cameraAjust);
			GameMasterS->SetCameraNodePos(cameraPos);

			//		カメラを公転させる
			cameraRot.y -= 180.0f;//プレイヤーは180度回転させているので補正を行う
			GameMasterS->SetCameraNodeRot(cameraRot);
			break;
		case PSTATE_APPEAR:
			cameraPos = gGameLayer->player.wrapper->getPosition3D() + gGameLayer->player.sprite3d->getPosition3D() + gGameLayer->player.cameraAjust;
			cameraRot = gGameLayer->player.wrapper->getRotation3D() + gGameLayer->player.sprite3d->getRotation3D();


			//		プレイヤーの座標にカメラのノードを置く
			//GameMasterS->SetCameraNodePos(gGameLayer->player.cameraAjust);
			GameMasterS->SetCameraNodePos(cameraPos);

			//カメラを公転させる
			cameraRot.y -= 180.0f;//プレイヤーは180度回転させているので補正を行う
			GameMasterS->SetCameraNodeRot(cameraRot);
			break;

		case PSTATE_RUN:

			cameraPos = gGameLayer->player.wrapper->getPosition3D() + gGameLayer->player.sprite3d->getPosition3D();// +gGameLayer->player.cameraAjust;
			cameraRot = gGameLayer->player.wrapper->getRotation3D() + gGameLayer->player.sprite3d->getRotation3D();

			//プレイヤーの座標にカメラのノードを置く
			GameMasterS->SetCameraNodePos(cameraPos);

			//カメラを公転させる
			cameraRot.y -= 180.0f;//プレイヤーは180度回転させているので補正を行う
			GameMasterS->SetCameraNodeRot(cameraRot);
			break;

		default:

			cameraPos = gGameLayer->player.wrapper->getPosition3D() + gGameLayer->player.sprite3d->getPosition3D();// +gGameLayer->player.cameraAjust;
			cameraRot = gGameLayer->player.wrapper->getRotation3D() + gGameLayer->player.sprite3d->getRotation3D();
			//プレイヤーの座標にカメラのノードを置く
			GameMasterS->SetCameraNodePos(cameraPos);
			//カメラを公転させる
			cameraRot.y -= 180.0f;//プレイヤーは180度回転させているので補正を行う
			GameMasterS->SetCameraNodeRot(cameraRot);
			break;
		}
	}
	return TRUE;
}



bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	GameMasterS->SetTouchPos(pTouch);//タッチ座標を取得してセット
	GameMasterS->SetTouchFlag(TFLAG_ON);
	
	return true;
}


void GameScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	GameMasterS->SetTouchPos(pTouch);//タッチ座標を取得してセット
	GameMasterS->SetTouchFlag(TFLAG_MOVE);

	Director *pDirector;
	Point touchPoint;
	Rect spRect;

	static float rx;
	static float ry;
	static float rz;

	auto s = Director::getInstance()->getWinSize();//画面サイズ取得
	//タッチ座標を取得する
	pDirector = Director::getInstance();
	touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

}



void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	GameMasterS->SetTouchPos(pTouch);//タッチ座標を取得してセット
	GameMasterS->SetTouchFlag(TFLAG_RELEASE);
}

#include "GameScene.h"

//各レイヤーを管理するソースコードをインクルードしておく

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameModelsLayer.h"
#include "GameUILayer.h"
#include"GameMaster.h"

#else

#include "C++/Scene/GameModelsLayer.h"
#include "C++/Scene/GameUILayer.h"
#include "C++/Base/GameMaster.h"

#endif

USING_NS_CC;
using namespace TapGun;

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


//ゲームレイヤーの初期化関数
//GameLayer* GameScene::gameLayer()
//{
//	cocos2d::Node* layer = this->getChildByTag(GameLayerTag);
//	return (GameLayer *)layer;
//}


//UILayer* GameScene::uiLayer()
//{
//	cocos2d::Node* layer = GameScene::sharedLayer()->getChildByTag(UILayerTag);
//	return (UILayer *)layer;
//}


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
	if(!Layer::init())
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

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::moveTime), 0.016f);//1秒60Fでゲーム更新

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
	if(NULL != gUILayer)
	{
		GameMasterS->InitCamera2D();//カメラを初期化
		gUILayer->setCameraMask(CAMFLAG_DEFAULT);
		addChild(GameMasterS->Get2DCamInstance());
	}

	//3D用カメラの実装
	if(NULL != gGameLayer)
	{
		GameMasterS->InitCamera3D();//カメラを初期化（ノードにaddChildもする）
		gGameLayer->setCameraMask(CAMFLAG_3D);

		//プレイヤーの座標取得はとりあえずこのような形で記述しています
		Vec3 cameraPos = gGameLayer->unit[playerNum].sprite3d->getPosition3D();

		//ノードを意識しない座標
		/*
		GameMasterS->CamNode->setPosition3D(Vec3(0.0f,0.0f,0.0f));//ノードは常にプレイヤーの座標に一致

		Vec3 cameraPos2 = Vec3(cameraPos.x + 0.8f, cameraPos.y + 1.5f, cameraPos.z + 3.1f);
		GameMasterS->SetCamera3DPos(cameraPos2);
		*/



		//ノードを意識する座標

		GameMasterS->SetCameraNodePos(cameraPos);//ノードは常にプレイヤーの座標に一致
		GameMasterS->SetCameraNodeRot(gGameLayer->unit[playerNum].sprite3d->getRotation3D());//ノード回転もプレイヤーをもとに設定

		Vec3 cameraPos2 = Vec3(0.58f, 1.55f, 1.3f);//プレイヤー（親ノード）とカメラの位置関係をセット
		//Vec3 cameraPos2 = Vec3(0.8f, 1.5f, 10.1f);//プレイヤー（親ノード）とカメラの位置関係をセット

		GameMasterS->SetCamera3DPos(cameraPos2);
		GameMasterS->SetCamera3DRot(Vec3(-3.0f, 0.0f, 0.0f));

		GameMasterS->GetCameraNode();
		GameMasterS->Get3DCamInstance();
		addChild(GameMasterS->GetCamNodeInstance());

	}
	return TRUE;
}



//更新系


/**
*	指定フレームごとのゲームシーン更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameScene::moveTime(float delta)
{
	GameMasterS->UpdateTouchManager();//タッチ情報を更新

	//現在のゲームの状態でゲーム分岐
	switch(GameMasterS->GetGameState())
	{

	case GSTATE_INIT:
		if(NULL != gGameLayer)//現在は子レイヤーをクリエイトしたかを確認する
		{
			playerNum = gGameLayer->InitLayer();//
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

		if(NULL != gGameLayer)//現在は初期化チェック確認する
		{
			gGameLayer->UpdateWait();//レイヤーの更新
		}
		if(NULL != gUILayer)//現在は初期化チェック確認する
		{
			gUILayer->UpdateLayer();
		}
		UpdateCamera();//モデルの移動をもとにカメラ移動

		break;
	case GSTATE_PLAY_INIT://ウェイト終了後プレイ前の処理

		//敵の配置を行う
		GameMasterS->SetGameState(GSTATE_PLAY);
		GameMasterS->SetPlayerState(PSTATE_IDLE);

//		UpdateCamera();//モデルの移動をもとにカメラ移動

		break;
	case GSTATE_PLAY:

		if(NULL != gGameLayer)//現在は初期化チェック確認する
		{
			gGameLayer->UpdateLayer();//レイヤーの更新
		}
		if(NULL != gUILayer)//現在は初期化チェック確認する
		{
			gUILayer->UpdateLayer();
		}
		UpdateCamera();//モデルの移動をもとにカメラ移動

		break;

	case GSTATE_PAUSE:
		//ポーズ中は専用のレイヤーを描画する？
		//モデルの更新処理を制限する
		break;
	case GSTATE_CONTINUE:

		break;
	case GSTATE_GAMEOVER:

		break;
	}
}


/**
*	ゲームシーン更新（現在使用していません）
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameScene::update(float delta)
{

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

	}

	if(NULL != gGameLayer)
	{

		//プレイヤーの周りをカメラが回転するテスト

		//プレイヤーの座標取得はとりあえずこのような形で記述しています
		Vec3 cameraPos = gGameLayer->unit[playerNum].sprite3d->getPosition3D();
		Vec3 cameraRot = gGameLayer->unit[playerNum].sprite3d->getRotation3D();

		//①：公転
		//プレイヤーの座標にカメラのノードを置く
		GameMasterS->SetCameraNodePos(cameraPos);

		//カメラを公転させる
		cameraRot.y -= 180.0f;//プレイヤーは180度回転させているので補正を行う
		GameMasterS->SetCameraNodeRot(cameraRot);

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

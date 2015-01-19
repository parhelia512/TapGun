
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



GameMaster* GameParamObj2;//とりあえず名前を変えるか名前空間で区別する

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


    GameParamObj2 = GameMaster::GetInstance();//ゲームパラメータクラスのインスタンス生成
    GameParamObj2->InitScreenSize();//スクリーンサイズのセット
    GameParamObj2->InitParam();//ゲームパラメータの初期化


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
        GameParamObj2->InitCamera2D();//カメラを初期化
        gUILayer->setCameraMask(CAMFLAG_DEFAULT);
        int a = gUILayer->getCameraMask();
        addChild(GameParamObj2->Get2DCamInstance());
    }

    //3D用カメラの実装
    if(NULL != gGameLayer)
    {
        GameParamObj2->InitCamera3D();//カメラを初期化
        gGameLayer->setCameraMask(CAMFLAG_3D);

        //プレイヤーの座標取得はとりあえずこのような形で記述しています
        Vec3 cameraPos = gGameLayer->unit[playerNum].sprite3d->getPosition3D();

        cameraPos.x += 0.8;// += 0.5f;
        cameraPos.y += 1.5f;// += 1.5f;
        cameraPos.z += 4.0f;// += 3.1f;
		

		//cameraPos.x = 0.0f;// += 0.5f;
		//cameraPos.y = 0.0f;// += 1.5f;
		//cameraPos.z = 0.0f;// += 3.1f;
//		GameParamObj2->SetCameraLookAt();

        GameParamObj2->SetCamera3DPos(cameraPos);
        GameParamObj2->SetCamera3DRot(Vec3(0.0f, 0.0f, 0.0f));
       // gGameLayer->addChild(GameParamObj2->Get3DCamInstance());//add camera to the scene
		addChild(GameParamObj2->Get3DCamInstance());//add camera to the scene

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
	GameParamObj2->UpdateTouchManager();//タッチ情報を更新


	switch(GameParamObj2->GetGameState())
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
		GameParamObj2->SetGameState(GSTATE_PLAY);
		break;

	case GSTATE_WAIT:

		break;
	case GSTATE_PLAY:

		if(NULL != gGameLayer)//現在は初期化チェック確認する
		{
			gGameLayer->UpdateLayer();//レイヤーの更新(現在はタッチ座標とカメラ構造体を引数として渡しています)
		}
		if(NULL != gUILayer)//現在は初期化チェック確認する
		{

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
        static float rot;
        rot = -0.01f;
        //gGameLayer->setRotation3D(Vec3(0.0f, rot, 0.0f));
    }
    return TRUE;
}



bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	GameParamObj2->SetTouchPos(pTouch);//タッチ座標を取得してセット
	GameParamObj2->SetTouchFlag(TFLAG_ON);
    return true;
}


void GameScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	GameParamObj2->SetTouchPos(pTouch);//タッチ座標を取得してセット
	GameParamObj2->SetTouchFlag(TFLAG_MOVE);

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
	GameParamObj2->SetTouchPos(pTouch);//タッチ座標を取得してセット
	GameParamObj2->SetTouchFlag(TFLAG_RELEASE);
}

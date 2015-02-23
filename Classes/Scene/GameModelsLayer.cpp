
#include "GameModelsLayer.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
#include "Sprite3D.h"
#include "Sound.h"

#else

#include "Base/Sprite3D.h"
#include "Base/GameMaster.h"
#include "System/Sound.h"

#endif


USING_NS_CC;
using namespace TapGun;

GameMaster* GameMasterM;//変数名は今後考慮する

int rotationCount;
float rotationR;//
Vec3 changeCameraPos;
Vec3 changeCameraRot;

/**
*	ゲーム本編のモデルレイヤーの初期化
*
*	@author	sasebon
*	@param	なし
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
bool GameModelsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	GameMasterM = GameMaster::GetInstance();//ゲームパラメータクラスの初期化
	return true;
}



/**
*	ゲーム本編のUIレイヤーの各種数値初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::InitLayer(void)
{
	LoadModels();//スプライトの生成
//	player.createMuzzle(player.sprite3d);
//	player.muzzleFlagOff();
	InitAllModels();

	InitPlayer(0);//とりあえず引数0
	InitMap(0);//正規のマップデータが降りてくるまでいったん保留します

	enemyTable->InitAll();//エネミー出現テーブルを初期化（現在はすべて0）

	InitEnemy(0);
	InitBullet();

	//timeval構造体の初期化
	nowTV = new timeval();
	preTV = new timeval();
	memset(nowTV, 0, sizeof(timeval));
	memset(preTV, 0, sizeof(timeval));
}



/**
*	ゲーム本編のスプライトの生成
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	2/4 Ver 1.0
*/
void GameModelsLayer::LoadModels()
{
	//各ユニットのノードなど、createする必要があるものは同時に行う
	//addChildも同時に行う

	//プレイヤーのロード
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "player";
	std::string fileName2 = "Player.anime";
#else
	std::string fileName1 = "player/player";
	std::string fileName2 = "Player.anime";
#endif

	//スプライトとノードのcreate
	player.sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);
	player.wrapper = Node::create();//モデルの親ノード
	player.leftNode = Node::create();//プレイヤーの回転軸の基準ノード（左）
	player.rightNode = Node::create();//プレイヤーの回転軸の基準ノード（右）
	player.centerNode = Node::create();

	//スプライトとノードのaddChild
	player.wrapper->addChild(player.sprite3d);
	addChild(player.wrapper);
	player.wrapper->addChild(player.leftNode);
	player.wrapper->addChild(player.rightNode);
	player.wrapper->addChild(player.centerNode);

	//マップのロード
	//マップは0番に割り当て
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "map507";
	fileName1 = "stage";
#else
	fileName1 = "Stage/map507";
	fileName1 = "Stage/stage";
#endif
	unit[UNIT0_MAP].sprite3d = _Sprite3D::create(fileName1);//0番は現在マップに割り当て
	addChild(unit[UNIT0_MAP].sprite3d);


	//敵のロード
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "enemy";
	fileName2 = "Enemy.anime";
#else
	fileName1 = "enemy/enemy";
	fileName2 = "Enemy.anime";
#endif
	for (int i = UNIT1_ENEMY; i < UNIT2_BULLET; i++)
	{
		//スプライトとノードのcreate
		unit[i].sprite3d = _Sprite3D::create(fileName1, fileName2);//1番~20番を敵に割り当て
		unit[i].wrapper = Node::create();//親ノードも初期化
		unit[i].node1 = Node::create();//左手用ノード
		unit[i].node2 = Node::create();//右手用ノード
		unit[i].colisionNode = Node::create();//

		//スプライトとノードのaddChild
		unit[i].wrapper->addChild(unit[i].sprite3d);
		addChild(unit[i].wrapper);
		unit[i].sprite3d->addChild(unit[i].node2);
		unit[i].sprite3d->addChild(unit[i].node1);
		unit[i].sprite3d->addChild(unit[i].colisionNode);//当たり判定の基準ノードを3dスプライトに紐付け
	}
	//敵弾のロード
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "bullet";
#else
	fileName1 = "Bullet/tama";
#endif

	for (int i = UNIT2_BULLET; i < UNIT3_MAX; i++)
	{
		unit[i].sprite3d = _Sprite3D::create(fileName1);
		unit[i].wrapper = Node::create();
		unit[i].node1 = Node::create();//弾の先端用ノード
		//		unit[i].colisionNode = Node::create();

		unit[i].wrapper->addChild(unit[i].sprite3d);
		addChild(unit[i].wrapper);
		unit[i].wrapper->addChild(unit[i].node1);
		//		unit[i].sprite3d->addChild(unit[i].colisionNode);//当たり判定の基準ノードを3dスプライトに紐付け
	}


#ifdef DEBUG_CENTER
	center.sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);//プレイヤーの回転中心を表す仮ポイント
#endif

	//座標計算用ノード
	cNode.gNode = Node::create();
	cNode.lNode = Node::create();
	cNode.lNode2 = Node::create();

	//座標計算用のノードをaddChild
	addChild(cNode.gNode);
	cNode.gNode->addChild(cNode.lNode);
	cNode.lNode->addChild(cNode.lNode2);
}


/**
*	全モデル初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::InitAllModels()
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		unit[i].Init();//メンバ変数初期化
	}
}


/**
*	プレイヤー初期化
*
*	@author	sasebon
*	@param	ステージ番号
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::InitPlayer(int stage_num)
{
	player.Init();//プレイヤーの情報を初期化

	//プレイヤー固有の初期化（今後場所を変更する）
	GameMasterM->playerHitFlag = TRUE;//

	//回避座標の軸の定義
	player.leftNode->setPosition3D(Vec3(-0.6f, 0.0f, -0.6f));
	player.rightNode->setPosition3D(Vec3(0.6f, 0.0f, -0.6f));


	//ステージに応じた初期化
	player.sprite3d->setScale(1.0f);
	player.sprite3d->setRotation3D(GameMasterM->stagePoint[POINT_START].pRot);//プレイヤーは正面を向く
	player.wrapper->setPosition3D(GameMasterM->stagePoint[POINT_START].pPos);
	GameMasterM->sPoint = POINT_W1;//ステージ1に走る

	//当たり判定の定義（仮）
	player.collisionPos = Vec3(1.2, 3.0, 1.2);//範囲を指定して
	player.SetCollision();
	player.centerNode->setPosition3D(Vec3(0.0f, PLAYER_CENTER_Y, 0.0f));

	GameMasterM->SetPlayerBullets(STS_MAXBULLETS);//

#ifdef DEBUG_CENTER
	center.sprite3d->setScale(0.1f);
#endif

	//最初はアイドル状態から始まるので、時間を取得せずともよい
	player.motStartTime = 0.0f;
	player.motProcTime = 0.0f;
	player.motPreTime = 0.0f;
}



/**
*	エネミー初期化
*
*	@author	sasebon
*	@param	ステージ番号
*	@return	正常:1 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitEnemy(int stage_num)
{
	//全てのエネミーユニットを初期化
	//エネミーのセットはsetEnemyで行う

	for(int i = UNIT1_ENEMY; i < UNIT2_BULLET; i++)
	{
		unit[i].Init(i, UKIND_ENEMY);
		unit[i].visible = FALSE;
		unit[i].sprite3d->setVisible(FALSE);
		unit[i].collisionPos = Vec3(0.8f, 1.5f, 0.8f);//範囲を指定して
		unit[i].SetCollision();//
		unit[i].eState = ESTATE_NONE;

		unit[i].node2->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));//
		unit[i].node1->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));//
	}
	return TRUE;
}


/**
*	敵弾初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::InitBullet()
{
	//全てのエネミーユニットを初期化
	//エネミーのセットはsetEnemyで行う
	for (int i = UNIT2_BULLET; i < UNIT3_MAX; i++)
	{
		unit[i].Init(i, UKIND_EBULLET);
		unit[i].sprite3d->setVisible(FALSE);
//		unit[i].collisionPos = Vec3(0.8f, 1.5f, 0.8f);//範囲を指定して
//		unit[i].SetCollision();//
		unit[i].eState = ESTATE_NONE;
	}
}


/**
*	ステージごとのエネミーのセット
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::SetEnemy(void)
{
	//現在ウェーブで場合分け
	switch(GameMasterM->wave)
	{
	case 0://ウェーブ1

		enemyTable->InitAll();//エネミー出現テーブルを初期化（）
		enemyTable->finishNumber = 10;//9体の敵が出る

		//敵の初期化
		for(int i = UNIT1_ENEMY; i < UNIT2_BULLET; i++)
		{
			unit[i].sprite3d->setVisible(false);//敵モデル非表示
			unit[i].visible = FALSE;//敵モデル非表示
			unit[i].sprite3d->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));//敵モデル非表示
			unit[i].eState = ESTATE_SLEEP;
			unit[i].tableNum = -1;
			unit[i].hitpoint = 5;

			unit[i].AIIdle = -1;
			unit[i].AIAtk = -1;
			unit[i].AIAppear = -1;//

			unit[i].atkFrame = 0.0f;//
			unit[i].eWaitFrame = 0.0f;//出現までの待ちフレーム

		}


		//敵の出現ポイントをセット
		enemyTable->standbyPos[0] = (Vec3(17.539f, 0.0f, -16.435));
		enemyTable->standbyPos[1] = (Vec3(14.574f, 0.0f, 11.887f));
		enemyTable->standbyPos[2] = (Vec3(5.965f, 0.0f, -11.007f));
		enemyTable->standbyPos[3] = (Vec3(9.19f, 0.0f, -16.823f));
		enemyTable->standbyPos[4] = (Vec3(17.907f, 0.0f, -15.401f));
		enemyTable->standbyPos[5] = (Vec3(17.539f, 0.0f, -16.435f));
		enemyTable->standbyPos[6] = (Vec3(9.19f, 0.0f, -16.823f));
		enemyTable->standbyPos[7] = (Vec3(9.19f, 0.0f, -16.823f));
		enemyTable->standbyPos[8] = (Vec3(6.028f, 0.0f, -7.788f));
		enemyTable->standbyPos[9] = (Vec3(6.134f, 0.0f, -15.654f));

		//敵の目標地点をセット
		enemyTable->targetPos[0] = (Vec3(11.385f, 0.0f, -10.211f));
		enemyTable->targetPos[1] = (Vec3(10.673f, 0.0f, -13.275f));
		enemyTable->targetPos[2] = (Vec3(11.385f, 0.0f, -7.781f));
		enemyTable->targetPos[3] = (Vec3(9.705f, 0.0f, -8.381f));
		enemyTable->targetPos[4] = (Vec3(10.673f, 0.0f, -13.275f));
		enemyTable->targetPos[5] = (Vec3(11.385f, 0.0f, -10.211f));
		enemyTable->targetPos[6] = (Vec3(9.705f, 0.0f, -8.381f));
		enemyTable->targetPos[7] = (Vec3(11.385f, 0.0f, -10.211f));
		enemyTable->targetPos[8] = (Vec3(11.385f, 0.0f, -7.781f));
		enemyTable->targetPos[9] = (Vec3(10.673f, 0.0f, -10.211f));




		//エネミーの初期座標をセット
		//エネミーの最初のターゲット座標をセット
		//エネミーの行動パターンをセット
		enemyTable->enemyData[0].standbyPos = enemyTable->standbyPos[0];
		enemyTable->enemyData[0].targetPos = enemyTable->targetPos[0];
		enemyTable->enemyData[0].nextEnemyNum = 3;
		enemyTable->enemyData[0].alive = TRUE;
		enemyTable->enemyData[0].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[1].standbyPos = enemyTable->standbyPos[1];
		enemyTable->enemyData[1].targetPos = enemyTable->targetPos[1];
		enemyTable->enemyData[1].nextEnemyNum = 4;
		enemyTable->enemyData[1].alive = TRUE;
		enemyTable->enemyData[1].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[2].standbyPos = enemyTable->standbyPos[2];
		enemyTable->enemyData[2].targetPos = enemyTable->targetPos[2];
		enemyTable->enemyData[2].nextEnemyNum = 5;
		enemyTable->enemyData[2].alive = TRUE;
		enemyTable->enemyData[2].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[3].standbyPos = enemyTable->standbyPos[3];
		enemyTable->enemyData[3].targetPos = enemyTable->targetPos[3];
		enemyTable->enemyData[3].nextEnemyNum = 6;
		enemyTable->enemyData[3].alive = TRUE;
		enemyTable->enemyData[3].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[4].standbyPos = enemyTable->standbyPos[4];
		enemyTable->enemyData[4].targetPos = enemyTable->targetPos[4];
		enemyTable->enemyData[4].nextEnemyNum = 7;
		enemyTable->enemyData[4].alive = TRUE;
		enemyTable->enemyData[4].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[5].standbyPos = enemyTable->standbyPos[5];
		enemyTable->enemyData[5].targetPos = enemyTable->targetPos[5];
		enemyTable->enemyData[5].nextEnemyNum = 8;
		enemyTable->enemyData[5].alive = TRUE;
		enemyTable->enemyData[5].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[6].standbyPos = enemyTable->standbyPos[6];
		enemyTable->enemyData[6].targetPos = enemyTable->targetPos[6];
		enemyTable->enemyData[6].nextEnemyNum = -1;
		enemyTable->enemyData[6].alive = TRUE;
		enemyTable->enemyData[6].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);


		enemyTable->enemyData[7].standbyPos = enemyTable->standbyPos[7];
		enemyTable->enemyData[7].targetPos = enemyTable->targetPos[7];
		enemyTable->enemyData[7].nextEnemyNum = -1;
		enemyTable->enemyData[7].alive = TRUE;
		enemyTable->enemyData[7].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);

		enemyTable->enemyData[8].standbyPos = enemyTable->standbyPos[8];
		enemyTable->enemyData[8].targetPos = enemyTable->targetPos[8];
		enemyTable->enemyData[8].nextEnemyNum = 9;
		enemyTable->enemyData[8].finishFlag = TRUE;
		enemyTable->enemyData[8].alive = TRUE;
		enemyTable->enemyData[8].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);

		enemyTable->enemyData[9].standbyPos = enemyTable->standbyPos[9];
		enemyTable->enemyData[9].targetPos = enemyTable->targetPos[9];
		enemyTable->enemyData[9].nextEnemyNum = -1;
		enemyTable->enemyData[9].finishFlag = TRUE;
		enemyTable->enemyData[9].alive = TRUE;
		enemyTable->enemyData[9].SetAI(AI_ATK_NONE, AI_IDLE_SIDE, AI_ATK_NONE);



		//敵の出現定義が済んだら、最初に出現させる敵のセットを行う
		unit[1].eState = ESTATE_STANDBY;
		unit[1].sprite3d->setVisible(true);//敵モデル非表示
		unit[1].visible = TRUE;//敵モデル非表示
		unit[1].sprite3d->setPosition3D(enemyTable->enemyData[0].standbyPos);//敵モデル非表示
		unit[1].targetPos = enemyTable->enemyData[0].targetPos;
		unit[1].StandbyPos = enemyTable->enemyData[0].standbyPos;
		unit[1].tableNum = 0;

		unit[1].AIIdle = enemyTable->enemyData[0].AIIdle;
		unit[1].AIAtk = enemyTable->enemyData[0].AIAtk;
		unit[1].AIAppear = enemyTable->enemyData[0].AIappear;


		unit[2].eState = ESTATE_STANDBY;
		unit[2].sprite3d->setVisible(true);//敵モデル非表示
		unit[2].visible = TRUE;//敵モデル非表示
		unit[2].sprite3d->setPosition3D(enemyTable->enemyData[1].standbyPos);//敵モデル非表示
		unit[2].targetPos = enemyTable->enemyData[1].targetPos;
		unit[2].StandbyPos = enemyTable->enemyData[1].standbyPos;
		unit[2].tableNum = 1;

		unit[2].AIIdle = enemyTable->enemyData[2].AIIdle;
		unit[2].AIAtk = enemyTable->enemyData[2].AIAtk;
		unit[2].AIAppear = enemyTable->enemyData[2].AIappear;


		unit[3].eState = ESTATE_STANDBY;
		unit[3].sprite3d->setVisible(true);//敵モデル非表示
		unit[3].visible = TRUE;//敵モデル非表示
		unit[3].sprite3d->setPosition3D(enemyTable->enemyData[2].standbyPos);//敵モデル非表示
		unit[3].targetPos = enemyTable->enemyData[2].targetPos;
		unit[3].StandbyPos = enemyTable->enemyData[2].standbyPos;
		unit[3].tableNum = 2;

		unit[3].AIIdle = enemyTable->enemyData[2].AIIdle;
		unit[3].AIAtk = enemyTable->enemyData[2].AIAtk;
		unit[3].AIAppear = enemyTable->enemyData[2].AIappear;


		break;
	case 1://ステージ1

		break;
	case 3:

		break;
	default:
		break;
	}
}



/**
*	ステージオブジェクトの初期化
*
*	@author	sasebon
*	@param	ステージ番号
*	@return	正常:1 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitMap(int stage_num)
{
	unit[UNIT0_MAP].Init();//メンバ変数の初期化をしておく

	unit[UNIT0_MAP].sprite3d->setScale(1.0f);
	unit[UNIT0_MAP].sprite3d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[UNIT0_MAP].sprite3d->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
//	unit[UNIT0_MAP].sprite3d->setPosition3D(Vec3(-20.0f, 0.0f, 50.0f));
	unit[UNIT0_MAP].Init(0, UKIND_MAP);
	return TRUE;
}


/**
*	ウェイト状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/23 Ver 1.0
*/
void GameModelsLayer::UpdateWait()
{
	switch (GameMasterM->waitFlag)
	{
	case 0:
	{
		//目標地点を取得し、移動処理の準備を行う
		player.targetPos = GameMasterM->stagePoint[GameMasterM->sPoint].pPos;//
		player.speed = STS_RUNSPEED;//スピードは後で調整する

		player.speedVec = player.targetPos - player.wrapper->getPosition3D();//

		//ベクトルの正規化を行う
		player.speedVec.normalize();

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		player.speedVec.x *= player.speed;
		player.speedVec.z *= player.speed;

		//キャラクターの向きを調整
		double r = atan2f(player.speedVec.z, player.speedVec.x);
		r = CC_RADIANS_TO_DEGREES(r);

		player.speedVec.y = 0;//yは今のところ0で扱う
		player.sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//

		player.sprite3d->stopALLAnimation();
		player.sprite3d->startAnimationLoop("run");
		GameMasterM->waitFlag = 1;
		GameMasterM->SetPlayerState(PSTATE_RUN);
		//カメラの位置が滑らかに変化する処理を入れる
		GameMasterM->SetCamera3DPos(Vec3(W_SETX, W_SETY, W_SETZ));//プレイヤー（親ノード）とカメラの位置関係をセット
		GameMasterM->SetCamera3DRot(Vec3(W_ROTX, W_ROTY, W_ROTZ));
	}
		break;
	case 1:
		GameMasterM->waitFlag = 2;
		break;
	case 2:
	{
			  UpdatePlayer();//プレイヤーの更新
			  Vec3 tmpPos = player.wrapper->getPosition3D();
			  tmpPos = player.targetPos - tmpPos;
			  //一定以上目的地に近付いたら、カメラとプレイヤーを回転させる準備を行う


			  //平面の距離を求める
			  float d1 = sqrtf(tmpPos.x * tmpPos.x + tmpPos.y * tmpPos.y);
			  //計算した平面上の距離と高さの距離を求める
			  d1 = sqrtf((tmpPos.z * tmpPos.z) + (d1 * d1));

			  if(0.15f >= d1)
			  {
				  GameMasterM->waitFlag = 3;
				  Vec3 tmp = player.sprite3d->getRotation3D();//プレイヤーの今の角度をもとに
				  rotationR = GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y - tmp.y;//戦闘時の角度との差を計算する
				  rotationR *= 0.05;//1フレームごとに変化する角度を計算
				  rotationCount = 0;

				  if(POINT_CHANGE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)
				  {
					  changeCameraPos = Vec3(0.0f, 0.0f, 0.0f);
					  changeCameraRot = Vec3(0.0f, 0.0f, 0.0f);
				  }
				  else if(POINT_FINISH == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)
				  {
					  changeCameraPos = Vec3(0.0f, 0.0f, 0.0f);
					  changeCameraRot = Vec3(0.0f, 0.0f, 0.0f);
				  }
				  else if(POINT_BATTLE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)
				  {
					  //プレイヤーとカメラの位置関係を計算
					  Vec3 cP = GameMasterM->stagePoint[GameMasterM->sPoint].cPos - GameMasterM->stagePoint[GameMasterM->sPoint].pPos;
					  Vec3 cR = (GameMasterM->stagePoint[GameMasterM->sPoint].cRot) - GameMasterM->stagePoint[GameMasterM->sPoint].pRot;

					  if(PSIDE_LEFT == GameMasterM->stagePoint[GameMasterM->sPoint].playerSide)
					  {
						  changeCameraPos = Vec3(C_SETX_L - W_SETX, C_SETY_L - W_SETY, C_SETZ_L - W_SETZ) * 0.05;
						  changeCameraRot = Vec3(C_ROTX_L - W_ROTX, C_ROTY_L - W_ROTY, C_ROTZ_L - W_ROTZ)* 0.05;
					  }
					  else
					  {
						  changeCameraPos = Vec3(C_SETX_R - W_SETX, C_SETY_R - W_SETY, C_SETZ_R - W_SETZ) * 0.05;
						  changeCameraRot = Vec3(C_ROTX_R - W_ROTX, C_ROTY_R - W_ROTY, C_ROTZ_R - W_ROTZ)* 0.05;
					  }
				  }
				  player.speed = 0.0f;
				  player.speedVec = Vec3(0.0f, 0.0f, 0.0f);
			  }
	}
		break;
	case 3:
	{
		if (20 > rotationCount)//回転中の動作
		{
			Vec3 tmp = player.sprite3d->getRotation3D();
			player.sprite3d->setRotation3D(tmp + Vec3(0, rotationR, 0));//今の角度に回転角度を足す

			GameMasterM->AddCamera3DPos(changeCameraPos);//プレイヤー（親ノード）とカメラの位置関係をセット
			GameMasterM->AddCamera3DRot(changeCameraRot);

			rotationCount++;
		}
		else//回転終了後の動作
		{
			if (POINT_CHANGE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//進行方向切り替え
			{
				player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].pRot);
				player.wrapper->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pPos);

				GameMasterM->sPoint++;//座標と角度が設定できたらポイントを先に進める
				GameMasterM->waitFlag = 0;
			}
			else if (POINT_BATTLE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//次のウェーブに到達した
			{
				//座標と角度をセット
				player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].pRot);
				player.wrapper->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pPos);

				GameMasterM->playerSide = GameMasterM->stagePoint[GameMasterM->sPoint].playerSide;//現在が左右どちらに立っているかを確認

				//プレイヤーの回避用ノードをもとに、回避座標を取得する
				if (PSIDE_LEFT == GameMasterM->playerSide)
				{
					//目標角度をもとにノードの移動後座標を取得
					Vec2 pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					Vec3 newPos = player.wrapper->getPosition3D() + Vec3(pos.x, 0.0f, pos.y);
					player.wrapper->setPosition3D(newPos);//wrapper

					pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					newPos = player.sprite3d->getPosition3D() - Vec3(pos.x, 0.0f, pos.y);
					player.sprite3d->setPosition3D(newPos);//wrapper

					//目標角度をもとに、回避時のカメラ移動座標を計算
					//プレイヤーの親ノードに対する回避後カメラ座標の相対座標を計算
					Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, PSIDE_LEFT);
					camTarget = Vec3(tmp.x, 0.0f, tmp.y);

					//回避時のカメラ移動前の座標を確保
					camCenter = player.wrapper->getPosition3D();
				}
				else
				{
					//目標角度をもとにノードの移動後座標を取得
					Vec2 pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					Vec3 newPos = player.wrapper->getPosition3D() + Vec3(pos.x, 0.0f, pos.y);
					player.wrapper->setPosition3D(newPos);//wrapper

					pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					newPos = player.sprite3d->getPosition3D() - Vec3(pos.x, 0.0f, pos.y);
					player.sprite3d->setPosition3D(newPos);//wrapper


					//目標角度をもとに、回避時のカメラ移動座標を計算
					Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, PSIDE_RIGHT);
					camTarget = Vec3(tmp.x, 0.0f, tmp.y);
				}
				GameMasterM->SetGameState(GSTATE_PLAY_SET);//戦闘ポイントに到着したら、ウェイトからプレイに移行
				player.sprite3d->stopAllActions();
				GameMasterM->SetPlayerState(PSTATE_IDLE);

				//ゲームに関係する各種フラグの初期化
				GameMasterM->flgPlayerATK = FALSE;//プレイヤーの攻撃判定をOFFに
				GameMasterM->playerHitFlag = TRUE;//プレイヤーの食らい判定をONに
				GameMasterM->shotFlag = FALSE;//

			}
			else if (POINT_CLEAR == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//クリアしたら
			{

			}
			else
			{
				int a = 0;
			}
		}
	}
		break;
	case 4:

		break;
	}
}



/**
*	プレイヤーの更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::UpdatePlayer(void)
{
	//タッチ座標をもとに攻撃や回避の処理を行う
	//この関数内では、タッチ状態とタッチフラグの更新は行わないこと。

	//１：プレイヤーのフレーム・座標更新
	player.Update(GameMasterM->loopTime);
	//マズルの更新
	//	player.muzzleUpdate();

	//２：プレイヤーの状態を取得して場合分け
	switch(GameMasterM->GetPlayerState())
	{

	case PSTATE_IDLE://アイドル状態
		ActionIdle();
		break;
	case PSTATE_SHOT:
		ActionShot();
		break;
	case PSTATE_DODGE://隠れ中
		ActionDodge();
		break;
	case PSTATE_HIDE://隠れている
		ActionHide();
		break;
	case PSTATE_APPEAR://隠れた状態から出る
		ActionAppear();
		break;
	case PSTATE_DAMAGED:
		ActionDamaged();
		break;
	case PSTATE_RECOVER:
		ActionRecover();
		break;
	case PSTATE_RUN://ウェイト状態

		break;
	case PSTATE_DEAD://死亡状態
		ActionDead();
		break;
	case PSTATE_CONTINUE://

		break;
	}
	//プレイヤーが攻撃可能な場合、攻撃範囲の座標をタッチしたら攻撃を行う
}


/**
*	プレイヤーのアイドル状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionIdle()
{
	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string shot;
	std::string h_shot;
	std::string h_reload;

	auto director = Director::getInstance();


	if(PSIDE_LEFT == GameMasterM->playerSide)
	{
		shot = "shot_l";
		h_shot = "h_shot_l";
		h_reload = "h_reload_l";
	}
	else
	{
		shot = "shot_r";
		h_shot = "h_shot_r";
		h_reload = "h_reload_r";
	}

	if(TSTATE_ON == GameMasterM->GetTouchState())//タッチされたら
	{
		auto s = Director::getInstance()->getWinSize();//画面サイズ取得
		const Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得

		//		player.muzzleflagOn();

		int tmpFlag = 0;

		if(PSIDE_LEFT == GameMasterM->playerSide)//プレイヤーが左に立っている
		{
			//攻撃可能範囲をタッチしていれば
			if(tPos.x > s.width *(1.0f - BATTLE_FEILD_X))
			{
				tmpFlag = 1;//
			}
			//回避UI付近をタッチしたら
			else if(tPos.x >= s.width * HIDE_UI_X0 && tPos.x < s.width *HIDE_UI_X1
				&& tPos.y >= s.height*HIDE_UI_Y0 && tPos.y < s.height*HIDE_UI_Y1)
			{
				tmpFlag = 2;
			}
		}
		else//右に立っている
		{
			//攻撃可能範囲をタッチしていれば
			if(tPos.x < s.width * BATTLE_FEILD_X)
			{
				tmpFlag = 1;//
			}
			//回避UI付近をタッチしたら
			else if(tPos.x < s.width * (1.0f - HIDE_UI_X0) && tPos.x >= s.width *(1.0f - HIDE_UI_X1)
				&& tPos.y >= s.height*HIDE_UI_Y0 && tPos.y < s.height*HIDE_UI_Y1)
			{
				tmpFlag = 2;
			}
		}

		//タッチ状態に応じて分岐
		if(0 == tmpFlag)
		{
			//タッチしていない
		}
		else if(1 == tmpFlag)
		{
			//残弾に応じて処理を分ける
			if(0 >= GameMasterM->GetPlayerBullets())
			{

				//モーションは再生するが弾を出さない
			}
			else
			{
				//アニメーションを再生
				GameMasterM->SetPlayerState(PSTATE_SHOT);
				player.sprite3d->stopAllActions();
				player.sprite3d->startAnimation(shot);//射撃アニメーションを最後まで再生する

				GameMasterM->rapidFrame = -1.0f;//連射フレームを-1に初期化
				GameMasterM->flgPlayerATK = FALSE;//
				GameMasterM->shotFlag = FALSE;//

				//モーション管理用の時間を初期化
				player.motProcTime = 0;//モーションを再生してからの経過時間（秒）
				player.motPreTime = getNowTime();//PreTimeに現在時刻を代入
				player.motStartTime = getNowTime();
			}
		}
		else
		{
			//
			GameMasterM->SetPlayerState(PSTATE_DODGE);//回避に移行

			player.sprite3d->stopAllActions();
			player.sprite3d->startAnimationReverse(h_shot);//回避モーションを再生

			//モーション管理用の時間を初期化
			player.motProcTime = 0;//モーションを再生してからの経過時間（秒）
			player.motPreTime = getNowTime();//PreTimeに現在時刻を代入
			player.motStartTime = getNowTime();
			player.setAnimEndTime(MACRO_FtoS(STS_HIDEWAIT));//回避モーションにかかる時間をセット

		}
	}
}



/**
*	プレイヤーの攻撃状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionShot()
{
	//モーションを再生してからの経過時間をある程度正確に取得するため、関数内で時間計算を行っています
	player.motProcTime = getNowTime() - player.motStartTime;//モーションを再生してからの経過時間（秒）
	float lTime = getNowTime() - player.motPreTime;
	player.motPreTime = getNowTime();//PreTimeに現在時刻を代入

	GameMasterM->rapidFrame += MACRO_StoF(lTime);//

	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string shot;
	std::string h_shot;
	std::string h_reload;
	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		shot = "shot_l";
		h_shot = "h_shot_l";
		h_reload = "h_reload_l";
	}
	else
	{
		shot = "shot_r";
		h_shot = "h_shot_r";
		h_reload = "h_reload_r";
	}

	auto sound = Sound::getInstance();

	//5フレーム以上タッチしているかのチェック
	if (FALSE == GameMasterM->shotFlag && MACRO_StoF(player.motProcTime)>= 5.0f)
	{
		GameMasterM->shotFlag = TRUE;
		player.sprite3d->stopAllActions();
		player.sprite3d->startAnimationLoop(shot, 0, 7.0f);
//		player.sprite3d->startAnimationLoop(shot);
	}


	if (TSTATE_ON == GameMasterM->GetTouchState() || TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		if (0 >= GameMasterM->GetPlayerBullets())
		{
			//残弾がない場合
			GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする
			//アニメーションはそのまま行う
		}
		else
		{
			//残弾がある場合
			//一定フレームごとに攻撃判定をONにする
			if (STS_RAPIDSPEED < GameMasterM->rapidFrame)
			{
				GameMasterM->flgPlayerATK = TRUE;
				GameMasterM->AddPlayerBullets(-1);//弾数を減らす
				//音声はフラグ成立時に鳴らす
				//sound->playSE("Shot.wav");
				GameMasterM->rapidFrame = 0.0f;
			}
			else
			{
				GameMasterM->flgPlayerATK = FALSE;
			}
		}

		GameMasterM->SetPlayerState(PSTATE_SHOT);//ステート状態はそのまま
	}
	else if (TSTATE_RELEASE == GameMasterM->GetTouchState())//タッチを離したら
	{
		if (FALSE == GameMasterM->shotFlag)
		{
			//もしタッチ時間が5フレーム以内なら
			GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
			GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする

			//そのままアニメーションを終了する
		}
		else
		{
			GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
			GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする

			//それ以外の場合、ショットの最後の部分まで再生する
			player.sprite3d->stopAllActions();
			player.sprite3d->startAnimation(shot);
		}
	}
	else
	{
		if (FALSE == GameMasterM->shotFlag)
		{
			//もしタッチ時間が5フレーム以内なら
			GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
			GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする
			GameMasterM->shotFlag = FALSE;
			//そのままアニメーションを終了する
		}
		else
		{
			GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
			GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする
			GameMasterM->shotFlag = FALSE;

			//ショットの最後の部分を再生する
			player.sprite3d->stopAllActions();
			player.sprite3d->startAnimation(shot);
		}
	}
}



/**
*	プレイヤーの避け最中の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionDodge(void)
{
	//モーションを再生してからの経過時間をある程度正確に取得するため、関数内で時間計算を行っています
	player.motProcTime = getNowTime() - player.motStartTime;//モーションを再生してからの経過時間（秒）
	float lTime = getNowTime() - player.motPreTime;
	player.motPreTime = getNowTime();//PreTimeに現在時刻を代入

	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string shot;
	std::string h_shot;
	std::string h_reload;
	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		h_shot = "h_shot_l";
		h_reload = "h_reload_l";
	}
	else
	{
		h_shot = "h_shot_r";
		h_reload = "h_reload_r";
	}

	//１：ボタンホールド状態で回避フレームが終了するとActionHideに移行する
	//２：ボタンホールド状態が解除されればActionAppearに移行する
	//３：ボタンホールド継続状態であれば、モーションを継続する・・・（ボタンON,ボタンMOVE）

	int state = GameMasterM->GetTouchState();//現在のタッチ状態を取得

	//無敵時間の判定を行う
	if(STS_MUTEKISTART <= MACRO_StoF(player.motProcTime))//無敵開始フレームに達したら
	{
		GameMasterM->playerHitFlag = FALSE;//当たり判定を無効化する
	}

	//リロード判定を行う
	if(STS_RELOADSTART <= MACRO_StoF(player.motProcTime))//リロード開始フレームに達したら
	{
		GameMasterM->SetPlayerBullets(STS_MAXBULLETS);//弾数を回復する
	}

	//回避完了フレームに達したら
	//	if (STS_HIDEWAIT <= GameMasterM->hideFrame)
	//	if (0 == player.sprite3d->checkAnimationState())//アニメーションが終了したら
	if (player.getAnimEndTime() <= player.motProcTime)
	{
		GameMasterM->SetPlayerState(PSTATE_HIDE);//隠れている状態に移行

		//リロードモーションが終了した後は、リロードモーションを行う
		player.sprite3d->stopAllActions();
		player.sprite3d->startAnimation(h_reload);//リロードモーションを再生

		//モーション用カウンターを初期化
		player.motProcTime = 0.0f;//経過時間を0に初期化
		player.motPreTime = getNowTime();
		player.motStartTime = getNowTime();

		//座標と角度をセットしてキャラクターの座標を補正
		if (PSIDE_LEFT == GameMasterM->playerSide)
		{
			player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].pRot + Vec3(0.0f, 96.0f, 0.0f));
			player.wrapper->setRotation3D(Vec3(0.0f, -96.0f, 0.0f));
		}
		else
		{
			player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].pRot - Vec3(0.0f, 96.0f, 0.0f));
			player.wrapper->setRotation3D(Vec3(0.0f, 96.0f, 0.0f));
		}
	}
	else
	{
		//回避完了前にホールド解除した場合
		//とりあえずTFLAG_CANCELをif内に入れておく
		if (TSTATE_RELEASE == state)
		{
			GameMasterM->SetPlayerState(PSTATE_APPEAR);//隠れている状態に移行
			//突撃モーションを再生

			float startTime = MACRO_FtoS(STS_HIDEWAIT)- player.motProcTime;//回避モーションの残り時間をもとに、突撃モーションの開始時間を計算

			player.setAnimEndTime(MACRO_FtoS(STS_HIDEWAIT) - startTime);//アニメーション終了までの残り秒数をセット
			player.sprite3d->stopALLAnimation();//モーション終了
			player.sprite3d->startAnimation(h_shot, MACRO_StoF(startTime), STS_HIDEWAIT);//

			//
			player.motStartTime = getNowTime();//現在時刻
			player.motProcTime = startTime;//突撃の「秒」数をセット
		}
		else if (TSTATE_MOVE == state || TSTATE_ON == state)//ホールド状態
		{
			//回避動作中は指定座標を軸に座標移動を行う
			if (PSIDE_LEFT == GameMasterM->playerSide)
			{
				//プレイヤーの座標の更新
				float rot = lTime * 90.0f / (MACRO_FtoS(STS_HIDEWAIT));

				Vec3 tmp = player.wrapper->getRotation3D();
				tmp.y -= rot;// *loopTime;
				player.wrapper->setRotation3D(tmp);//毎フレームP親ノードの角度を更新する
				tmp = player.sprite3d->getRotation3D();
				tmp.y += rot;// *loopTime;
				player.sprite3d->setRotation3D(tmp);//プレイヤーの角度は逆に更新し、キャラクターの向きを正面に向かせる

				//回避に合わせてカメラの座標を補正する
				player.cameraAjust = Vec3(camTarget.x * MACRO_StoF(player.motProcTime), camTarget.y * MACRO_StoF(player.motProcTime), camTarget.z * MACRO_StoF(player.motProcTime));//ループごとの移動量を計算

			}
			else
			{
				//プレイヤーの座標の更新
				float rot = lTime * 90.0f / (MACRO_FtoS(STS_HIDEWAIT));

				Vec3 tmp = player.wrapper->getRotation3D();
				tmp.y += rot;// *loopTime;
				player.wrapper->setRotation3D(tmp);
				tmp = player.sprite3d->getRotation3D();
				tmp.y -= rot;// *loopTime;
				player.sprite3d->setRotation3D(tmp);

				//回避に合わせてカメラの座標を補正する
				player.cameraAjust = Vec3(camTarget.x * MACRO_StoF(player.motProcTime), camTarget.y * MACRO_StoF(player.motProcTime), camTarget.z * MACRO_StoF(player.motProcTime));//ループごとの移動量を計算
			}
		}
		else
		{
			int a = 0;
			a = 0;
		}
	}
}


/**
*	プレイヤーの隠れ状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionHide(void)
{
	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string shot;
	std::string h_shot;
	std::string h_reload;
	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		h_shot = "h_shot_l";
		h_reload = "h_reload_l";
	}
	else
	{
		h_shot = "h_shot_r";
		h_reload = "h_reload_r";
	}

	//ボタンが押しっぱなしであれば、回避状態を継続し、リロードアニメーションを再生
	//ボタンが離されれば、回避状態を終了して突撃状態へ移行

	if (TSTATE_ON == GameMasterM->GetTouchState() || TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		//タッチ中はリロードを再生、再生後はモーション停止
		player.cameraAjust = Vec3(camTarget.x * STS_HIDEWAIT, camTarget.y * STS_HIDEWAIT, camTarget.z * STS_HIDEWAIT);//カメラ位置
	}
	else if (TSTATE_RELEASE == GameMasterM->GetTouchState())//離されれば
	{
		GameMasterM->SetPlayerState(PSTATE_APPEAR);
		player.sprite3d->startAnimation(h_shot);
//		player.InitFrame();//フレームをリフレッシュ

		//モーション管理用時間の初期化
		player.motStartTime = getNowTime();//スタートは現在時刻 * 0.001f//現在時刻を取得
		player.motPreTime = getNowTime();//前フレームの時刻も現在時刻
		player.motProcTime = 0.0f;//経過時間は0
		player.setAnimEndTime(MACRO_FtoS(STS_HIDEWAIT));//モーション終了までの残り時間を計算
	}
}

/**
*	プレイヤーの飛び出し状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionAppear(void)
{
	//モーションを再生してからの経過時間をある程度正確に取得するため、関数内で時間計算を行っています
	player.motProcTime = getNowTime() - player.motStartTime;//モーションを再生してからの経過時間（秒）
	float lTime = getNowTime() - player.motPreTime;//1ループにかかった時間を計算
	player.motPreTime = getNowTime();//PreTimeに現在時刻を代入


	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string idle;
	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		idle = "idle_l";
	}
	else
	{
		idle = "idle_r";
	}

	//１：突撃終了フレームが終了するとActionIdleに移行する
	int flag = GameMasterM->GetTouchFlag();//現在のタッチ状態を取得

	//無敵時間の判定を行う
	if (STS_MUTEKISTART <= MACRO_StoF(player.motProcTime))//無敵終了フレームに達したら
	{
		GameMasterM->playerHitFlag = TRUE;//当たり判定を有効化する
	}

	//回避完了の判定
	//	if (STS_HIDEWAIT <= GameMasterM->hideFrame)//突撃フレームに達したら
	//	if(0 == player.sprite3d->checkAnimationState())//アニメーションが終了したら
	if(player.getAnimEndTime() <= player.motProcTime)
	{
		//必要ならばモーションの停止を行う
		GameMasterM->SetPlayerState(PSTATE_IDLE);//アイドル状態に移行
		player.sprite3d->stopAllActions();


		//座標と角度をセットしてキャラクターの座標を補正
		player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].pRot);
		player.wrapper->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));

		//座標と角度をセットしてカメラの座標を補正
		Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, GameMasterM->playerSide);
		camTarget = Vec3(tmp.x, 0.0f, tmp.y);


		player.sprite3d->startAnimationLoop(idle);
	}
	else
	{
		if (PSIDE_LEFT == GameMasterM->playerSide)
		{
			//回避フレームに比例してカメラの回転を変化させる
			float rot = lTime * 90.0f / (MACRO_FtoS(STS_HIDEWAIT));
			Vec3 tmp = player.wrapper->getRotation3D();
			tmp.y += rot;//
			player.wrapper->setRotation3D(tmp);//プレイヤーの親ノード（回避軸）の角度を更新する
			tmp = player.sprite3d->getRotation3D();
			tmp.y -= rot;//
			player.sprite3d->setRotation3D(tmp);//プレイヤー自身の角度を更新する

			//回避に合わせてカメラの座標を補正する
			player.cameraAjust = Vec3(camTarget.x * (MACRO_FtoS(STS_HIDEWAIT) - player.motProcTime), camTarget.y * (MACRO_FtoS(STS_HIDEWAIT) - player.motProcTime), camTarget.z * (MACRO_FtoS(STS_HIDEWAIT) - player.motProcTime));//ループごとの移動量を計算
		}
		else
		{
			//回避フレームに比例してカメラの回転を変化させる
			float rot = lTime * 90.0f / (MACRO_FtoS(STS_HIDEWAIT));
			Vec3 tmp = player.wrapper->getRotation3D();
			tmp.y -= rot;//
			player.wrapper->setRotation3D(tmp);//プレイヤーの親ノード（回避軸）の角度を更新する
			tmp = player.sprite3d->getRotation3D();
			tmp.y += rot;//
			player.sprite3d->setRotation3D(tmp);//プレイヤー自身の角度を更新する

			//回避に合わせてカメラの座標を補正する
			player.cameraAjust = Vec3(camTarget.x * (MACRO_FtoS(STS_HIDEWAIT) - player.motProcTime), camTarget.y * (MACRO_FtoS(STS_HIDEWAIT) - player.motProcTime), camTarget.z * (MACRO_FtoS(STS_HIDEWAIT) - player.motProcTime));//ループごとの移動量を計算
		}
	}
}

/**
*	プレイヤーの食らい状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionDamaged(void)
{
	//モーションを再生してからの経過時間をある程度正確に取得するため、関数内で時間計算を行っています
	player.motProcTime = getNowTime() - player.motStartTime;//モーションを再生してからの経過時間（秒）
	float lTime = getNowTime() - player.motPreTime;//1ループにかかった時間を計算
	player.motPreTime = getNowTime();//PreTimeに現在時刻を代入

	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string recov;
	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		recov = "recov_l";
	}
	else
	{
		recov = "recov_r";
	}

	//アニメーションの確認
	if (0 == player.sprite3d->checkAnimationState())
	{
		//食らいモーションが終了したら


		//必要ならばモーションの停止を行う
		GameMasterM->SetPlayerState(PSTATE_RECOVER);//起き上がり状態に移行
		player.sprite3d->stopAllActions();
		player.sprite3d->startAnimation(recov);//起き上がりモーションを再生

		//
		player.motProcTime = 0.0f;//モーションを再生してからの経過時間（秒）
		player.motPreTime = getNowTime();//PreTimeに現在時刻を代入
		player.motStartTime = getNowTime();//PreTimeに現在時刻を代入
	}
	else
	{
		//
	}
}


/**
*	プレイヤーの起き上がり状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionRecover(void)
{
	//モーションを再生してからの経過時間をある程度正確に取得するため、関数内で時間計算を行っています
	player.motProcTime = getNowTime() - player.motStartTime;//モーションを再生してからの経過時間（秒）
	float lTime = getNowTime() - player.motPreTime;//1ループにかかった時間を計算
	player.motPreTime = getNowTime();//PreTimeに現在時刻を代入


	//プレイヤーの向きに応じて呼び出すアニメーションを変更する
	//とりあえずここで文字列作成
	std::string idle;
	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		idle = "idel_l";
	}
	else
	{
		idle = "idel_r";
	}


	//アニメーションの確認
	if (0 == player.sprite3d->checkAnimationState())
	{
		//食らいモーションが終了したら
		GameMasterM->SetPlayerState(PSTATE_IDLE);//アイドル状態に移行
		player.sprite3d->stopAllActions();
		player.sprite3d->startAnimationLoop(idle);

		GameMasterM->playerHitFlag = TRUE;//当たり判定を戻す

		//モーション管理用の時間を初期化
		player.motProcTime = 0.0f;//モーションを再生してからの経過時間（秒）
		player.motPreTime = getNowTime();//PreTimeに現在時刻を代入
		player.motStartTime = getNowTime();//StartTimeに現在時刻を代入
	}
	else
	{
		//
	}
}

/**
*	プレイヤーのウェイト状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionRun(void)
{
}




/**
*	プレイヤーの死亡状態の更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void GameModelsLayer::ActionDead(void)
{
	//
	//モーションを再生してからの経過時間をある程度正確に取得するため、関数内で時間計算を行っています
	player.motProcTime = getNowTime() - player.motStartTime;//モーションを再生してからの経過時間（秒）
	float lTime = getNowTime() - player.motPreTime;//1ループにかかった時間を計算
	player.motPreTime = getNowTime();//PreTimeに現在時刻を代入


	//アニメーションの確認
	if(0 == player.sprite3d->checkAnimationState())
	{
		//食らいモーションが終了したら
		GameMasterM->SetPlayerState(PSTATE_CONTINUE);//アイドル状態に移行
	}
	else
	{
		//
	}
}



/**
*	敵に弾を発射させる
*
*	@author	sasebon
*	@param	弾を撃った敵の番号
*	@return	なし
*	@date	2/12 Ver 1.0
*/
void GameModelsLayer::ShootBullet(int enemy_num)
{
	//
	int num = -1;
	for (int i = UNIT2_BULLET; i < UNIT3_MAX; i++)
	{
		if (FALSE == unit[i].visible)
		{
			//表示されていない弾用構造体の配列番号を取得する
			num = i;
			break;
		}
	}
	if (num != -1)
	{
		//弾を一度初期化する
		unit[num].Init(num, UKIND_EBULLET);

		unit[num].sprite3d->setScale(0.5f);//

		//弾を撃ったエネミーの座標と、プレイヤーの座標を元に、弾の移動方向を求める
		Vec3 enemyPos = unit[enemy_num].sprite3d->getPosition3D();

		//プレイヤーに向けて弾を発射する
		unit[num].speedVec = GameMasterM->stagePoint[GameMasterM->sPoint].pPos - enemyPos;//

		//ベクトルの正規化を行う
		unit[num].speedVec.normalize();

		//キャラクターの向きを調整
		double r = atan2f(unit[num].speedVec.z, unit[num].speedVec.x);
		r = CC_RADIANS_TO_DEGREES(r);

		unit[num].sprite3d->setRotation3D(Vec3(-90.0f, 90.0f - r, 0.0f));//
		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		unit[num].speed = STS_EBULLET_SPEED;
		unit[num].speedVec.x *= unit[num].speed;
		unit[num].speedVec.z *= unit[num].speed;
		//unit[num].speedVec.y = 0;//yは今のところ0で扱う

		unit[num].sprite3d->setPosition3D(enemyPos);
		unit[num].sprite3d->setPositionY(1.2f);

		//弾を画面に描画する
		unit[num].visible = TRUE;
		unit[num].sprite3d->setVisible(true);
	}
}


/**
*	敵弾の更新処理
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	2/12 Ver 1.0
*/
void GameModelsLayer::UpdateBullets()
{
	//全ての敵弾ユニットを更新
	for (int num = UNIT2_BULLET; num <= UNIT3_MAX; num++)
	{
		//画面に出ている弾のみを更新
		if (TRUE == unit[num].visible && TRUE == unit[num].valid)
		{
			unit[num].Update(GameMasterM->loopTime);//座標と一緒に当たり判定を移動
		}
	}
}



/**
*	当たり判定の処理
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/19 Ver 1.0
*/
void  GameModelsLayer::CheckHit(void)
{
	//========================================================
	//プレイヤー攻撃処理の仮実装
	//タッチ座標（スクリーン座標）からワールド座標を求め、レイを飛ばす

	//レイと敵の当たり判定処理
	const int pstate = GameMasterM->GetPlayerState();

	//攻撃判定フラグがONのときのみ攻撃判定を処理
	if(TRUE == GameMasterM->flgPlayerATK)
	{
		//注意：敵が重なって存在する場合に備え、Ｚソートなどの並び替えを行う必要がありそうです
		auto s = Director::getInstance()->getWinSize();//ウィンドウサイズを取得

		Vec3 rayStart = Vec3(0, 0, 0);//レイの始点
		Vec3 rayEnd = Vec3(0, 0, 0);//レイの終点

		Camera* cam3d = GameMasterM->GetCamera3D();//カメラのインスタンスを取得
		const Node* camNode = GameMasterM->GetCameraNode();//ノードのインスタンスを取得

		Vec3 tmpPos = cam3d->getPosition3D();//カメラ座標を保存
		Vec3 tmpRot = cam3d->getRotation3D();//カメラ回転を保存

		const Point pos = Vec2(tmpPos.x, tmpPos.z);
		const Point absolutePoint = camNode->convertToWorldSpace(pos);//カメラのx,zの絶対座標を取得

		Vec3 cPos = Vec3(pos.x, tmpPos.y, pos.y);//yは
		//Vec3 cRot = cam3d->getRotation3D() + camNode->getRotation3D();

		Vec2 tPos = GameMasterM->GetTouchPosInView();//タッチ座標を取得
		//		Vec2 gliv = GameMasterM->GetTouchPos();

		tPos.y -= GameMasterM->reticleAjust * s.height;//レティクルの状態を
		if(tPos.y < 0.0f)
		{
			tPos.y = 0.0f;
		}

		Vec3 tmpPosNear = Vec3(tPos.x, tPos.y, -1.0f);//-1.0f == 視錘台の近面（near plane）
		Vec3 tmpPosFar = Vec3(tPos.x, tPos.y, 1.0f);//1.0f == 視錘台の遠面（far plane）

		cam3d->setPosition3D(cPos);
		//cam3d->setRotation3D(cRot);

		cam3d->unproject(s, &tmpPosNear, &rayStart);//near planeの3次元座標を取得
		cam3d->unproject(s, &tmpPosFar, &rayEnd);

		//rayStart = cam3d->getPosition3D();


		Ray touchRay(rayStart, rayEnd);//仮レイを設定

		//レイの当たり判定
		for(int i = 0; i < MAX_UNIT; i++)
		{
			if(-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind && unit[i].eState != ESTATE_DAMAGED && unit[i].eState != ESTATE_DEAD)
			{
				if(touchRay.intersects(unit[i].obbHead))//タッチ座標の法線と敵の当たり判定が接触したかをチェック
				{
					unit[i].hitpoint -= 1;
				}
			}
		}

		/*@*/
		cam3d->setPosition3D(tmpPos);//
		cam3d->setRotation3D(tmpRot);//
	}

	//========================================================
	//敵の攻撃処理（弾とプレイヤーの当たり判定）
	if (TRUE == GameMasterM->playerHitFlag)
	{
		//プレイヤーの当たり判定が存在する場合
		//全ての敵弾ユニットを更新
		for (int i = UNIT2_BULLET; i < UNIT3_MAX; i++)
		{
			if (TRUE == unit[i].visible)
			{
				//プレイヤーとの当たり判定を処理

				//プレイヤーのグローバル座標を取得
				Vec3 pPos = player.wrapper->getPosition3D() + player.sprite3d->getPosition3D() + player.centerNode->getPosition3D();
				Vec3 dir = pPos - unit[i].sprite3d->getPosition3D();//プレイヤーと敵弾の差のベクトル

				//平面の距離を求める
				float d1 = sqrtf(dir.x * dir.x + dir.y * dir.y);
				//計算した平面上の距離と高さの距離を求める
				d1 = sqrtf((dir.z * dir.z) + (d1 * d1));
				if (0.4f > d1)
				{
					//接触した場合は_sprite3Dの解放を行う
					unit[i].sprite3d->setVisible(false);
					unit[i].visible = FALSE;
					unit[i].speedVec = Vec3(0.0f, 0.0f, 0.0f);

					//プレイヤーの状態を食らい判定にする
					GameMasterM->AddPlayerHP(-1);//ダメージを計算

					player.sprite3d->stopALLAnimation();//すべてのアニメーションを中断して

					if(0 < GameMasterM->GetPlayerHP())
					{
						switch(GameMasterM->playerSide)
						{
						case PSIDE_LEFT:
							player.sprite3d->startAnimation("hit_l");//食らいモーションを再生
							break;
						case PSIDE_RIGHT:
							player.sprite3d->startAnimation("hit_r");//食らいモーションを再生
							break;
						}
						GameMasterM->SetPlayerState(PSTATE_DAMAGED);//
					}
					else
					{
						player.sprite3d->startAnimation("dei_l");//食らいモーションを再生
						GameMasterM->SetPlayerState(PSTATE_DEAD);//
					}


					GameMasterM->playerHitFlag = FALSE;
					//ダメージを処理


					//座標と角度をセットしてキャラクターの座標を補正
					player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].pRot);
					player.wrapper->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));

					//座標と角度をセットしてカメラの座標を補正
					Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].pRot.y, GameMasterM->playerSide);
					camTarget = Vec3(tmp.x, 0.0f, tmp.y);

					//タイムとフレームの初期化
//					player.InitFrame();//フレームをリフレッシュ
					//モーション管理用の時間を初期化
					player.motProcTime = 0.0f;//モーションを再生してからの経過時間（秒）
					player.motPreTime = getNowTime();//PreTimeに現在時刻を代入
					player.motStartTime = getNowTime();//StartTimeに現在時刻を代入

					//一度でも攻撃を受けるとブレーク
					break;
				}
			}
		}
	}

	if (FALSE == GameMasterM->playerHitFlag && (PSTATE_DAMAGED == GameMasterM->GetPlayerState() || PSTATE_RECOVER == GameMasterM->GetPlayerState())
		|| PSTATE_DEAD == GameMasterM->GetPlayerState())
	{
		//当たり判定がオフの時も、プレイヤーが食らいモーションを受けているときは弾とプレイヤーの当たり判定を処理する
		//（演出のための処理）
		//プレイヤーの当たり判定が存在する場合
		//全ての敵弾ユニットを更新
		for (int i = UNIT2_BULLET; i < UNIT3_MAX; i++)
		{
			if (TRUE == unit[i].visible)
			{
				//プレイヤーとの当たり判定を処理

				//プレイヤーのグローバル座標を取得
				Vec3 pPos = player.wrapper->getPosition3D() + player.sprite3d->getPosition3D() + player.centerNode->getPosition3D();

				Vec3 dir = pPos - unit[i].sprite3d->getPosition3D();//プレイヤーと敵弾の差のベクトル

				//平面の距離を求める
				float d1 = sqrtf(dir.x * dir.x + dir.y * dir.y);
				//計算した平面上の距離と高さの距離を求める
				d1 = sqrtf((dir.z * dir.z) + (d1 * d1));
				if (0.4f > d1)
				{
					//接触した場合は_sprite3Dの解放を行う
					unit[i].sprite3d->setVisible(false);
					unit[i].visible = FALSE;
					unit[i].speedVec = Vec3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}

	//========================================================
	//弾の消去処理
	//全ての敵弾ユニットを更新
	for (int i = UNIT2_BULLET; i < UNIT3_MAX; i++)
	{
		if (TRUE == unit[i].visible)
		{
			//
			if (180.0f < unit[i].GetFrame())
			{
				//
				unit[i].speed = 0.0f;
				unit[i].visible = FALSE;
				unit[i].sprite3d->setVisible(false);
			}
		}
	}


	//

}


int GameModelsLayer::SearchFreeUnit()
{
	for (int i = 1; i <= 20; i++)
	{
		if (FALSE == unit[i].visible)
		{
			return i;
		}
	}
	return -1;
}



/*
指定フレームごとに呼び出される
*/
void GameModelsLayer::moveTime(float delta)
{

}



void GameModelsLayer::update(float delta)
{

}




/**
*	プレイヤーの回避中心計算
*
*	@author	sasebon
*	@param	プレイヤーの角度
*	@return	移動後のノード
*	@date	2/4 Ver 1.0
*/
Vec2 GameModelsLayer::calcRot(float pRot, int pSide)
{
	//
	Vec2 ret = Vec2(0.0f, 0.0f);
	cNode.gNode->setRotation(0.0f);
	cNode.gNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode->setPosition(Vec2(0.0f, 0.0f));

	//プレイヤーの向きに応じて処理を変更する
	if (PSIDE_LEFT == pSide)
	{
		cNode.lNode->setPositionX(HIDEPOINT_X);//回避座標を代入
		cNode.lNode->setPositionY(HIDEPOINT_Y);//回避座標を代入

		cNode.gNode->setRotation(pRot);

		ret = cNode.gNode->convertToWorldSpace(cNode.lNode->getPosition());//回転後のlNodeの座標を取得
	}
	else
	{
		cNode.lNode->setPositionX(-HIDEPOINT_X);//回避座標を代入
		cNode.lNode->setPositionY(HIDEPOINT_Y);//回避座標を代

		cNode.gNode->setRotation(pRot);
		ret = cNode.gNode->convertToWorldSpace(cNode.lNode->getPosition());//回転後のlNodeの座標を取得
	}
	return ret;
}



/**
*	カメラの回避座標計算
*
*	@author	sasebon
*	@param	プレイヤー回転量（角度）、プレイヤーの左右の位置
*	@return	移動後の座標
*	@date	2/4 Ver 1.0
*/
Vec2 GameModelsLayer::calcCamPos(float pRot, int pSide)
{
	//
	Vec2 ret = Vec2(0.0f, 0.0f);
	cNode.gNode->setRotation(0.0f);
	cNode.gNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode2->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode2->setPosition(Vec2(0.0f, 0.0f));

	//プレイヤーの向きに応じて処理を変更する
	if (PSIDE_LEFT == pSide)
	{
		cNode.lNode->setPositionX(C_SETX_L);//
		cNode.lNode->setPositionY(C_SETZ_L);//
		cNode.lNode2->setPositionX(HIDECAMERA_X);
		cNode.lNode2->setPositionY(HIDECAMERA_Y);

		Vec2 test = cNode.lNode2->getPosition();

		cNode.gNode->setRotation(pRot);
		ret = cNode.lNode->convertToWorldSpace(cNode.lNode2->getPosition());//回転後のカメラの座標（プレイヤーとの相対位置）
		ret = cNode.gNode->convertToWorldSpace(ret);//回転後のカメラの座標（プレイヤーとの相対位置）
	}
	else
	{
		cNode.lNode->setPositionX(C_SETX_R);//
		cNode.lNode->setPositionY(C_SETZ_R);//
		cNode.lNode2->setPositionX(-HIDECAMERA_X);
		cNode.lNode2->setPositionY(HIDECAMERA_Y);

		cNode.gNode->setRotation(pRot);
		ret = cNode.lNode->convertToWorldSpace(cNode.lNode2->getPosition());//回転後のカメラの座標（プレイヤーとの相対位置）
		ret = cNode.gNode->convertToWorldSpace(ret);//回転後のカメラの座標（プレイヤーとの相対位置）
	}

	return ret;
}



/**
*	カメラの回避座標計算
*
*	@author	sasebon
*	@param	プレイヤー回転量（角度）、プレイヤーの左右の位置
*	@return	移動後の座標
*	@date	2/4 Ver 1.0
*/
Vec2 GameModelsLayer::calcCamPos2(float pRot, int pSide)
{
	/*
	行いたい処理
	・前提
	カメラの親ノードはプレイヤーの位置に一致させている
	ただし戦闘中はプレイヤーの親ノードとプレイヤーの座標がずれるので、親ノードとプレイヤーの座標を加算し、ずれた分の座標を戻している
	⇒つまり、プレイヤーの親ノードから見たプレイヤーの座標がカメラの親ノード座標と一致する

	この状態でP親ノードを回転させることで、プレイヤーの回避を行っている。
	そのためプレイヤーの座標と角度は更新されない

	P親ノードの回転からP座標の移動を計算し、移動後の座標（P親ノードから見た座標）を取得する
	その座標をC親ノードに当てはめれば、カメラの動きが正しくなる・・・はず
	*/


	//
	Vec2 ret = Vec2(0.0f, 0.0f);
	cNode.gNode->setRotation(0.0f);
	cNode.gNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode2->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode2->setPosition(Vec2(0.0f, 0.0f));

	//プレイヤーの向きに応じて処理を変更する
	if (PSIDE_LEFT == pSide)
	{
		cNode.lNode->setPositionX(HIDEPOINT_X);//カメラの親ノード
		cNode.lNode->setPositionY(HIDEPOINT_Y);//〃
		cNode.lNode2->setPositionX(-HIDECAMERA_X);//回避後の座標
		cNode.lNode2->setPositionY(HIDECAMERA_Y);

		cNode.gNode->setRotation(pRot);

		ret = cNode.gNode->convertToWorldSpace(cNode.lNode2->getPosition());//回転後のlNode2の座標を取得
	}
	else
	{
		cNode.lNode->setPositionX(HIDEPOINT_X);//カメラの親ノード
		cNode.lNode->setPositionY(HIDEPOINT_Y);//〃
		cNode.lNode2->setPositionX(HIDECAMERA_X);//回避後の座標
		cNode.lNode2->setPositionY(HIDECAMERA_Y);

		cNode.gNode->setRotation(pRot);

		ret = cNode.gNode->convertToWorldSpace(cNode.lNode2->getPosition());//回転後のlNode2の座標を取得
	}
	return ret;
}



/**
*	カメラの回避座標計算
*
*	@author	sasebon
*	@param	プレイヤー回転量（角度）、プレイヤーの左右の位置
*	@return	移動後の座標
*	@date	2/4 Ver 1.0
*/
Vec2 GameModelsLayer::calcCamPos3(float pRot, int pSide)
{
	//
	Vec2 ret = Vec2(0.0f, 0.0f);
	cNode.gNode->setRotation(0.0f);
	cNode.gNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode->setPosition(Vec2(0.0f, 0.0f));

	cNode.lNode2->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	cNode.lNode2->setPosition(Vec2(0.0f, 0.0f));

	//プレイヤーの向きに応じて処理を変更する
	if (PSIDE_LEFT == pSide)
	{
		cNode.lNode->setPositionX(HIDECAMERA_X);//カメラの親ノードの回避後の座標
		cNode.lNode->setPositionY(HIDECAMERA_Y);//カメラの親ノードの回避後の座標

		cNode.gNode->setRotation(pRot);//カメラの親ノードをプレイヤーの向きだけ回転させる

		ret = cNode.gNode->convertToWorldSpace(cNode.lNode->getPosition());//回転後のlNodeの座標を取得
		//1フレーム当たりの移動量が計算できた
		ret.x = ret.x / STS_HIDEWAIT;
		ret.y = ret.y / STS_HIDEWAIT;
	}
	else
	{
		cNode.lNode->setPositionX(-HIDECAMERA_X);//カメラの親ノードの回避後の座標
		cNode.lNode->setPositionY(HIDECAMERA_Y);//カメラの親ノードの回避後の座標

		cNode.gNode->setRotation(pRot);//カメラの親ノードをプレイヤーの向きだけ回転させる

		ret = cNode.gNode->convertToWorldSpace(cNode.lNode->getPosition());//回転後のlNodeの座標を取得
		//1フレーム当たりの移動量が計算できた
		ret.x = ret.x / STS_HIDEWAIT;
		ret.y = ret.y / STS_HIDEWAIT;
	}
	return ret;
}



/**
*	エネミーの更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::UpdateEnemy()
{
	auto sound = Sound::getInstance();
	auto random = rand() % 4;
	for(int num = UNIT1_ENEMY; num < UNIT2_BULLET; num++)
	{
		if(TRUE == unit[num].valid && TRUE == unit[num].visible)//エネミーが表示されていれば
		{

			unit[num].Update(GameMasterM->loopTime);//フレーム・座標・当たり判定の更新

			auto director = Director::getInstance();
			auto loopTime = director->getDeltaTime();


			//敵キャラクターのhpが0になったら
			if(unit[num].hitpoint <= 0 && ESTATE_DAMAGED != unit[num].eState && ESTATE_DEAD != unit[num].eState)
			{
				unit[num].eState = ESTATE_DAMAGED;//ダメージ状態に変更
			}


			switch(unit[num].eState)
			{
			case ESTATE_SLEEP://プレイヤーが休眠状態

				break;
			case ESTATE_STANDBY://目標地点への移動開始
				ActionEStandby(num);
				break;
			case ESTATE_IDLE://アイドル状態
				ActionEIdle(num);
				break;
			case ESTATE_MOVE://移動状態
				ActionEMove(num);
				break;
			case ESTATE_WAIT://ウェイト
				//ActionEMove(num);
				break;
			case ESTATE_ATTACK1://攻撃
				ActionEAttack(num);
				break;
			case ESTATE_DAMAGED://被弾
				ActionEDamaged(num);
				break;
			case ESTATE_DEAD://死亡
				ActionEDead(num);
				break;
			case ESTATE_END://死んだ敵の処分
				//敵が死んだら次の敵を確認する
				//
				break;
			}
		}
	}
}





/**
*	エネミー1の更新
*
*	@author	sasebon
*	@param	敵Unitの配列番号
*	@return	なし
*	@date	2/5 Ver 1.0
*/
//void GameModelsLayer::ActionEnemy1(int num)
//{
//	unit[num].Update(GameMasterM->loopTime);//フレーム・座標・当たり判定の更新
//
//	//敵キャラクターのhpが0になったら
//	if (unit[num].hitpoint <= 0 && ESTATE_DAMAGED != unit[num].eState && ESTATE_DEAD != unit[num].eState)
//	{
//		unit[num].eState = ESTATE_DAMAGED;//ダメージ状態に変更
//	}
//
//	switch (unit[num].eState)
//	{
//	case ESTATE_SLEEP://プレイヤーが休眠状態
//
//
//
//		break;
//	case ESTATE_STANDBY://キャラクターが目標地点へと走るモーション
//	{
//		unit[num].eState = ESTATE_MOVE;//待機が終わったら移動
//
//		unit[num].speed = STS_ENEMY_RUNSPEED;//スピードは後で調整する
//
//		//向きの設定
//		unit[num].speedVec = unit[num].targetPos - unit[num].sprite3d->getPosition3D();
//
//		unit[num].speedVec.normalize();//ベクトルの正規化を行う
//		double r = atan2(unit[num].speedVec.z, unit[num].speedVec.x);
//		r = CC_RADIANS_TO_DEGREES(r);
//
//		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
//		unit[num].speedVec.x *= unit[num].speed;
//		unit[num].speedVec.z *= unit[num].speed;
//
//		unit[num].speedVec.y = 0;//yは今のところ0で扱う
//		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//
//
//		unit[num].sprite3d->startAnimationLoop("run");
//
//	}
//		break;
//	case ESTATE_IDLE://アイドル状態
//
//
//		break;
//	case ESTATE_MOVE://移動状態
//	{
//		Vec3 tmpPos = unit[num].sprite3d->getPosition3D();
//
//		//一定以上目的地に近付いたら
//		if (0.1f >= sqrtf(unit[num].targetPos.x - tmpPos.x) * (unit[num].targetPos.x - tmpPos.x)
//			+ (unit[num].targetPos.y - tmpPos.y) *(unit[num].targetPos.y - tmpPos.y))
//		{
//			//プレイヤーの立っている座標を向く
//
//			Vec3 tmpPos = GameMasterM->stagePoint[GameMasterM->sPoint].pPos;//プレイヤーの立っている座標の取得
//			unit[num].sprite3d->setPosition3D(unit[num].targetPos);//敵をポジションにセット
//
//			tmpPos = tmpPos - unit[num].targetPos;//プレイヤーの位置へのベクトルを計算
//			tmpPos.normalize();//ベクトルの正規化を行う
//
//
//			double r = atan2(tmpPos.z, tmpPos.x);
//			r = CC_RADIANS_TO_DEGREES(r);
//			unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//
//
//			unit[num].speed = 0.0f;
//			unit[num].speedVec = Vec3(0.0f, 0.0f, 0.0f);//移動終了
//
//			unit[num].eState = ESTATE_IDLE;//アイドル状態を開始
//			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
//
//			unit[num].sprite3d->startAnimationLoop("dammy_shot");
//		}
//	}
//		break;
//
//	case ESTATE_WAIT://ウェイト
//
//		break;
//
//	case ESTATE_ATTACK1://攻撃
//
//
//		break;
//	case ESTATE_ATTACK2:
//		break;
//
//	case ESTATE_ATTACK3:
//		break;
//
//	case ESTATE_DAMAGED://被弾
//
//		//HPが0になったら
//
//		unit[num].sprite3d->stopALLAnimation();
//		unit[num].sprite3d->startAnimation("dei2");
//		unit[num].eState = ESTATE_DEAD;
//
//
//		//
//		//if( random == 0)
//		//{
//		//	sound -> playSE("Damage_01.wav");
//		//}
//		//else if( random == 1)
//		//{
//		//	sound -> playSE("Damage_02.wav");
//		//}
//		//else if( random == 2)
//		//{
//		//	sound -> playSE("Damage_03.wav");
//		//}
//		//else if( random == 3)
//		//{
//		//	sound -> playSE("Damage_04.wav");
//		//}
//
//		//共通
//
//		//		unit[num].eState = ESTATE_STANDBY;
//		//	unit[num].hitpoint = 5;
//		//個別
//
//		//ShootBullet(num);
//
//
//		//				unit[num].sprite3d->setVisible( false);
//		break;
//	case ESTATE_DEAD://死亡
//		if (0 == unit[num].sprite3d->checkAnimationState())//死亡アニメーションが終了したら
//		{
//			unit[num].sprite3d->setVisible(false);
//			unit[num].visible = FALSE;
//			//unit[num].eState = ESTATE_END;
//			setNextEnemy(num);//
//		}
//		break;
//	case ESTATE_END://死んだ敵の処分
//		//敵が死んだら次の敵を確認する
//		//
//		break;
//	}
//}


///**
//*	エネミー2の更新
//*
//*	@author	sasebon
//*	@param	敵Unitの配列番号
//*	@return	なし
//*	@date	2/5 Ver 1.0
//*/
//void GameModelsLayer::ActionEnemy2(int num)
//{
//	unit[num].Update(GameMasterM->loopTime);//フレーム・座標・当たり判定の更新
//
//	auto director = Director::getInstance();
//	auto loopTime = director->getDeltaTime();
//
//
//	//敵キャラクターのhpが0になったら
//	if (unit[num].hitpoint <= 0 && ESTATE_DAMAGED != unit[num].eState && ESTATE_DEAD != unit[num].eState)
//	{
//		unit[num].eState = ESTATE_DAMAGED;//ダメージ状態に変更
//	}
//
//	switch (unit[num].eState)
//	{
//	case ESTATE_SLEEP://プレイヤーが休眠状態
//
//
//
//		break;
//	case ESTATE_STANDBY://キャラクターが目標地点へと走るモーション
//	{
//		unit[num].eState = ESTATE_MOVE;//待機が終わったら移動
//
//		unit[num].speed = STS_ENEMY_RUNSPEED;//スピードは後で調整する
//
//		//向きの設定
//		unit[num].speedVec = unit[num].targetPos - unit[num].sprite3d->getPosition3D();
//
//		unit[num].speedVec.normalize();//ベクトルの正規化を行う
//		double r = atan2(unit[num].speedVec.z, unit[num].speedVec.x);
//		r = CC_RADIANS_TO_DEGREES(r);
//
//		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
//		unit[num].speedVec.x *= unit[num].speed;
//		unit[num].speedVec.z *= unit[num].speed;
//
//		unit[num].speedVec.y = 0;//yは今のところ0で扱う
//		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//
//
//		unit[num].sprite3d->startAnimationLoop("run");
//
//	}
//		break;
//	case ESTATE_IDLE://アイドル状態
//	{
//		unit[num].atkFrame--;
//		if (unit[num].atkFrame <= 0)
//		{
//			unit[num].eState = ESTATE_ATTACK1;//アタック状態に移る
//			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
//			unit[num].sprite3d->startAnimation("shot");
//			if (ESTATE_ATTACK1 == unit[num].eState)
//			{
//				unit[num].atkFrame = 60.0f;//弾を発射するまでの残りフレーム
//			}
//		}
//		else
//		{
//
//		}
//	}
//		break;
//	case ESTATE_MOVE://移動状態
//	{
//		Vec3 tmpPos = unit[num].sprite3d->getPosition3D();
//
//		//一定以上目的地に近付いたら
//		if (0.1f >= sqrtf(unit[num].targetPos.x - tmpPos.x) * (unit[num].targetPos.x - tmpPos.x)
//			+ (unit[num].targetPos.y - tmpPos.y) *(unit[num].targetPos.y - tmpPos.y))
//		{
//			//プレイヤーの立っている座標を向く
//
//			Vec3 tmpPos = GameMasterM->stagePoint[GameMasterM->sPoint].pPos;//プレイヤーの立っている座標の取得
//			unit[num].sprite3d->setPosition3D(unit[num].targetPos);//敵をポジションにセット
//
//			tmpPos = tmpPos - unit[num].targetPos;//プレイヤーの位置へのベクトルを計算
//			tmpPos.normalize();//ベクトルの正規化を行う
//
//
//			double r = atan2(tmpPos.z, tmpPos.x);
//			r = CC_RADIANS_TO_DEGREES(r);
//			unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//
//
//			unit[num].speed = 0.0f;
//			unit[num].speedVec = Vec3(0.0f, 0.0f, 0.0f);//移動終了
//
//			unit[num].eState = ESTATE_IDLE;//アイドル状態を開始
//			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
//
//			unit[num].sprite3d->startAnimationLoop("idle");
//			unit[num].atkFrame = 60;//攻撃動作に移るまでの「秒数」//@秒ではなくフレームで統一する
//		}
//	}
//		break;
//
//	case ESTATE_WAIT://ウェイト
//
//		break;
//
//	case ESTATE_ATTACK1://攻撃
//
//		//タイミングを合わせて射撃を行う
//		unit[num].atkFrame -= loopTime * 60.0f;//アタックフレームを減少させていく
//		if (0.0f >= unit[num].atkFrame)
//		{
//			//フレームが0になったら
//			ShootBullet(num);
//			unit[num].atkFrame = 20.0f;//次の攻撃までのフレームを設定
//		}
//
//		//アニメーションが終了したら
//		if (0 == unit[num].sprite3d->checkAnimationState())
//		{
//			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
//			unit[num].sprite3d->startAnimation("idle");//
//			unit[num].atkFrame = 200;
//
//			unit[num].eState = ESTATE_IDLE;
//		}
//
//		break;
//	case ESTATE_ATTACK2:
//		break;
//
//	case ESTATE_ATTACK3:
//		break;
//
//	case ESTATE_DAMAGED://被弾
//
//		//HPが0になったら
//
//		unit[num].sprite3d->stopALLAnimation();
//		unit[num].sprite3d->startAnimation("dei1");
//		unit[num].eState = ESTATE_DEAD;
//
//
//		//
//		//if( random == 0)
//		//{
//		//    sound -> playSE("Damage_01.wav");
//		//}
//		//else if( random == 1)
//		//{
//		//    sound -> playSE("Damage_02.wav");
//		//}
//		//else if( random == 2)
//		//{
//		//    sound -> playSE("Damage_03.wav");
//		//}
//		//else if( random == 3)
//		//{
//		//    sound -> playSE("Damage_04.wav");
//		//}
//
//		//共通
//
//		//        unit[num].eState = ESTATE_STANDBY;
//		//    unit[num].hitpoint = 5;
//		//個別
//		break;
//	case ESTATE_DEAD://死亡
//		if (0 == unit[num].sprite3d->checkAnimationState())//死亡アニメーションが終了したら
//		{
//			unit[num].sprite3d->setVisible(false);
//			unit[num].visible = FALSE;
//			//unit[num].eState = ESTATE_END;
//			setNextEnemy(num);//
//		}
//		break;
//	case ESTATE_END://死んだ敵の処分
//		//敵が死んだら次の敵を確認する
//		//
//		break;
//	}
//}
//


/**
*	次の敵を出現させる
*
*	@author	sasebon
*	@param	敵Unitの配列番号
*	@return	なし
*	@date	2/5 Ver 1.0
*/
void GameModelsLayer::setNextEnemy(int num)
{
	//現在のウェーブと、死亡した敵の番号をもとに、次のモデルを準備する
	const int nextNum = enemyTable->enemyData[unit[num].tableNum].nextEnemyNum;
	enemyTable->enemyData[unit[num].tableNum].alive = FALSE;
	if(-1 == nextNum)//次のモデルが設定されていなければ
	{

	}
	else
	{//次の敵をスタンバイ状態にする
		int n = SearchFreeUnit();

		unit[n].eState = ESTATE_STANDBY;
		unit[n].sprite3d->setVisible(true);//敵モデル表示
		unit[n].visible = TRUE;//敵モデル表示
		unit[n].sprite3d->setPosition3D(enemyTable->enemyData[nextNum].standbyPos);
		unit[n].targetPos = enemyTable->enemyData[nextNum].targetPos;
		unit[n].StandbyPos = enemyTable->enemyData[nextNum].standbyPos;
		unit[n].tableNum = nextNum;
		unit[n].hitpoint = 5;

		unit[n].AIIdle = enemyTable->enemyData[nextNum].AIIdle;
		unit[n].AIAtk = enemyTable->enemyData[nextNum].AIAtk;
		unit[n].AIAppear = enemyTable->enemyData[nextNum].AIappear;
	}
}


/**
*	ウェーブ終了のチェック
*
*	@author	sasebon
*	@param	なし
*	@return	ウェーブ中:1 ウェーブ終了:-1
*	@date	2/5 Ver 1.0
*/
int GameModelsLayer::CheckNextStage(void)
{
	if(GSTATE_PLAY == GameMasterM->GetGameState())
	{
		for(int i = 0; i <= 100; i++)//
		{
			if(TRUE == enemyTable->enemyData[i].alive)
			{
				//1体でも敵が生きていれば
				return FALSE;
			}
		}
		player.sprite3d->stopALLAnimation();//現在のモーションを終了し

		GameMasterM->SetGameState(GSTATE_WAIT);//次のウェイトへ進む
		GameMasterM->wave += 1;//次のステージへ進む
		GameMasterM->waitFlag = 0;//
		GameMasterM->sPoint += 1;
	}
	else
	{
		//戦闘中で無ければ常にfalse
		return FALSE;
	}

	return TRUE;
}



/**
*	現在時刻を取得（秒）
*
*	@author	sasebon
*	@param	なし
*	@return	ウェーブ中:1 ウェーブ終了:-1
*	@date	2/5 Ver 1.0
*/
float GameModelsLayer::getNowTime(void)
{
	//現在時刻を取得
	gettimeofday(nowTV, nullptr);//player.nowTimeTo = clock() * 0.001f;
	//時間差を計算
	nowTime = (nowTV->tv_sec * 1000.0f + nowTV->tv_usec * 0.001f) * 0.001f;

	return nowTime;
}


//
void GameModelsLayer::ActionEStandby(int num)
{
	unit[num].speed = STS_ENEMY_RUNSPEED;//スピードは後で調整する

	//向きの設定
	unit[num].speedVec = unit[num].targetPos - unit[num].sprite3d->getPosition3D();

	unit[num].speedVec.normalize();//ベクトルの正規化を行う
	double r = atan2(unit[num].speedVec.z, unit[num].speedVec.x);
	r = CC_RADIANS_TO_DEGREES(r);

	//正規化が終わったら、速度をかけて方向ベクトルの計算終了
	unit[num].speedVec.x *= unit[num].speed;
	unit[num].speedVec.z *= unit[num].speed;

	unit[num].speedVec.y = 0;//yは今のところ0で扱う
	unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//

	//モーションに応じて動き方を変える

	unit[num].sprite3d->startAnimationLoop("run");
	unit[num].eState = ESTATE_MOVE;//待機が終わったら移動
}


//移動
void GameModelsLayer::ActionEMove(int num)
{
	Vec3 tmpPos = unit[num].sprite3d->getPosition3D();
	tmpPos = unit[num].targetPos - tmpPos;

	//平面の距離を求める
	float d1 = sqrtf(tmpPos.x * tmpPos.x + tmpPos.y * tmpPos.y);
	//計算した平面上の距離と高さの距離を求める
	d1 = sqrtf((tmpPos.z * tmpPos.z) + (d1 * d1));


	//一定以上目的地に近付いたら
	if(0.1f >= d1)
	{
		Vec3 tmpPos = GameMasterM->stagePoint[GameMasterM->sPoint].pPos;//
		unit[num].sprite3d->setPosition3D(unit[num].targetPos);//敵をポジションにセット

		tmpPos = tmpPos - unit[num].targetPos;//プレイヤーの位置へのベクトルを計算
		tmpPos.normalize();//ベクトルの正規化を行う


		double r = atan2(tmpPos.z, tmpPos.x);
		r = CC_RADIANS_TO_DEGREES(r);
		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//

		unit[num].speed = 0.0f;
		unit[num].speedVec = Vec3(0.0f, 0.0f, 0.0f);//移動終了

		unit[num].eState = ESTATE_IDLE;//アイドル状態を開始
		unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し

		//敵のAIの種類でモーションと移動量を変更する
		switch(unit[num].AIIdle)
		{
		case AI_IDLE_FAKE:
			unit[num].sprite3d->startAnimationLoop("dammy_shot");

			break;
		case AI_IDLE_SIDE:
			unit[num].sprite3d->startAnimationLoop("idle");//とりあえずidle

			break;
		case AI_IDLE_STOP:
			unit[num].sprite3d->startAnimationLoop("idle");
			break;
		}
	}
}


void GameModelsLayer::ActionEIdle(int num)
{
	//
	unit[num].atkFrame -= GameMasterM->loopTime;
	if(unit[num].atkFrame <= 0)
	{
		//攻撃モーションに応じて動きを変化
		switch(unit[num].AIAtk)
		{
		case AI_ATK_NONE:

			break;
		default:
			unit[num].eState = ESTATE_ATTACK1;//アタック状態に移る
			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
			unit[num].sprite3d->startAnimation("shot");
			if(ESTATE_ATTACK1 == unit[num].eState)
			{
				unit[num].atkFrame = 1.0f;//弾を発射するまでの残りフレーム
			}
			break;
		}
	}
	else
	{

	}
}

void GameModelsLayer::ActionEDodge(int num)
{

}

void GameModelsLayer::ActionEDamaged(int num)
{
	//HPが0になったら

	unit[num].sprite3d->stopALLAnimation();
	unit[num].sprite3d->startAnimation("dei1");
	unit[num].eState = ESTATE_DEAD;


	//
	//if( random == 0)
	//{
	//    sound -> playSE("Damage_01.wav");
	//}
	//else if( random == 1)
	//{
	//    sound -> playSE("Damage_02.wav");
	//}
	//else if( random == 2)
	//{
	//    sound -> playSE("Damage_03.wav");
	//}
	//else if( random == 3)
	//{
	//    sound -> playSE("Damage_04.wav");
	//}

	//共通

	//        unit[num].eState = ESTATE_STANDBY;
	//    unit[num].hitpoint = 5;
	//個別

}

void GameModelsLayer::ActionERecover(int num)
{

}


void GameModelsLayer::ActionEDead(int num)
{
	if(0 == unit[num].sprite3d->checkAnimationState())//死亡アニメーションが終了したら
	{
		unit[num].sprite3d->setVisible(false);
		unit[num].visible = FALSE;
		//unit[num].eState = ESTATE_END;
		setNextEnemy(num);//
	}
}



//
void GameModelsLayer::ActionEAttack(int num)
{

	//タイミングを合わせて射撃を行う
	unit[num].atkFrame -= GameMasterM->loopTime;//アタックフレームを減少させていく
	if(0.0f >= unit[num].atkFrame)
	{
		//フレームが0になったら
//		ShootBullet(num);
		unit[num].atkFrame = 0.33f;//次の弾発射までの時間を設定
	}

	//アニメーションが終了したら
	if(0 == unit[num].sprite3d->checkAnimationState())
	{
		unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
		unit[num].eState = ESTATE_IDLE;

		//敵のAIの種類でモーションと移動量を変更する
		switch(unit[num].AIIdle)
		{
		case AI_IDLE_FAKE:
			unit[num].sprite3d->startAnimationLoop("dammy_shot");
			unit[num].atkFrame = 3.3f;

			break;
		case AI_IDLE_SIDE:
			unit[num].sprite3d->startAnimationLoop("idle");//とりあえずidle
			unit[num].atkFrame = 3.3f;

			break;
		case AI_IDLE_STOP:
			unit[num].sprite3d->startAnimationLoop("idle");
			unit[num].atkFrame = 3.3f;
			break;
		}
	}
}
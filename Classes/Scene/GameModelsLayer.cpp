
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
#define DAMMY 1
Unit dammyUnit[DAMMY];

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "player";
	std::string fileName2 = "Player.anime";
#else
	std::string fileName1 = "player/player";
	std::string fileName2 = "Player.anime";
#endif
	player.sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);
	center.sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);//プレイヤーの回転中心を表す仮ポイント


	//マップは0番に割り当て
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "map507";
#else
	fileName1 = "Stage/map507";
#endif
	unit[0].sprite3d = _Sprite3D::create(fileName1);//0番は現在マップに割り当て

	//敵は1番~20番に割り当て
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "enemy";
	fileName2 = "Enemy.anime";
#else
	fileName1 = "enemy/enemy";
	fileName2 = "Enemy.anime";
#endif
	for (int i = 1; i <= 20; i++)
	{
		unit[i].sprite3d = _Sprite3D::create(fileName1, fileName2);//1番~20番を敵に割り当て
		unit[i].wrapper = Node::create();//親ノードも初期化
	}

	//敵弾モデルは21番~40番に割り当て
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	fileName1 = "bullet";
#else
	fileName1 = "Bullet/tama";
#endif
	for (int i = 21; i <= 40; i++)
	{
		unit[i].sprite3d = _Sprite3D::create(fileName1);
		unit[i].wrapper = Node::create();
	}


	//処理落ちチェック用のダミーキャラ
	for (int i = 0; i < DAMMY; i++)
	{
		dammyUnit[i].sprite3d = _Sprite3D::create("enemy/enemy", "Enemy.anime");
		dammyUnit[i].sprite3d->startAnimationLoop("sroll2");
		dammyUnit[i].sprite3d->setPosition3D(Vec3(-0.3f, 0.0f, 26.5f + 0.1f * i));
		addChild(dammyUnit[i].sprite3d);
	}
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
	player.wrapper = Node::create();//モデルの親ノード
	player.wrapper->addChild(player.sprite3d);//親ノードにスプライトを紐付け
	addChild(player.wrapper);//親ノードをレイヤーに紐付け

	//回避座標の軸の定義
	player.leftNode = Node::create();
	player.leftNode->setPosition3D(Vec3(-0.6f, 0.0f, -0.6f));
	player.wrapper->addChild(player.leftNode);
	player.rightNode = Node::create();
	player.rightNode->setPosition3D(Vec3(0.6f, 0.0f, -0.6f));
	player.wrapper->addChild(player.rightNode);


	//ステージに応じた初期化
	player.sprite3d->setScale(1.0f);
	player.sprite3d->setRotation3D(GameMasterM->stagePoint[POINT_START].rot);//プレイヤーは正面を向く
	player.wrapper->setPosition3D(GameMasterM->stagePoint[POINT_START].pos);
	GameMasterM->sPoint = POINT_STAGE1;//ステージ1に走る

	//当たり判定の定義（仮）
	player.collisionPos = Vec3(1.2, 3.0, 1.2);//範囲を指定して
	player.SetCollision();

	GameMasterM->SetPlayerBullets(STS_MAXBULLETS);//


	center.sprite3d->setScale(0.1f);
	player.wrapper->addChild(center.sprite3d);


	cNode.gNode = Node::create();
	cNode.lNode = Node::create();
	cNode.lNode2 = Node::create();

	addChild(cNode.gNode);
	cNode.gNode->addChild(cNode.lNode);
	cNode.lNode->addChild(cNode.lNode2);

	player.animCount = 0.0f;
	player.nowTimeFrom = 0.0f;
	player.nowTimeTo = 0.0f;
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

	for (int i = 1; i <= 20; i++)
	{
		unit[i].Init(i, UKIND_ENEMY);
		unit[i].visible = FALSE;
		unit[i].sprite3d->setVisible(FALSE);
		unit[i].collisionPos = Vec3(0.8f, 1.5f, 0.8f);//範囲を指定して
		unit[i].SetCollision();//
		unit[i].eState = ESTATE_NONE;

		addChild(unit[i].wrapper);//親ノードをレイヤーに紐付け
		unit[i].wrapper->addChild(unit[i].sprite3d);//3dスプライトを親ノードに紐付け
		unit[i].sprite3d->addChild(unit[i].colisionNode);//当たり判定の基準ノードを3dスプライトに紐付け

		unit[i].nodeRightGun = Node::create();
		unit[i].nodeLeftGun = Node::create();

		unit[i].nodeRightGun->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));//
		unit[i].nodeLeftGun->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));//

		unit[i].nodeL = unit[i].sprite3d->getAttachNode("Bip001 L Hand");
		unit[i].nodeL->addChild(unit[i].nodeLeftGun);

		//		unit[i].nodeRightGun

		//		unit[i].sprite3d->addChild(unit[i].nodeRightGun);//3dスプライトを親ノードに紐付け
		//		unit[i].sprite3d->addChild(unit[i].nodeLeftGun);//3dスプライトを親ノードに紐付け
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
	for (int i = 21; i <= 40; i++)
	{
		unit[i].Init(i, UKIND_EBULLET);
		unit[i].sprite3d->setVisible(FALSE);
		unit[i].collisionPos = Vec3(0.8f, 1.5f, 0.8f);//範囲を指定して
		unit[i].SetCollision();//
		unit[i].eState = ESTATE_NONE;

		addChild(unit[i].wrapper);//親ノードをレイヤーに紐付け
		unit[i].wrapper->addChild(unit[i].sprite3d);//3dスプライトを親ノードに紐付け
		unit[i].sprite3d->addChild(unit[i].colisionNode);//当たり判定の基準ノードを3dスプライトに紐付け
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
	switch (GameMasterM->wave)
	{
	case 0://ステージ1

		enemyTable->finishNumber = 10;//9体の敵が出る
		for (int i = 1; i < 20; i++)
		{
			unit[i].sprite3d->setVisible(false);//敵モデル非表示
			unit[i].visible = FALSE;//敵モデル非表示
			unit[i].sprite3d->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));//敵モデル非表示
			unit[i].eState = ESTATE_SLEEP;
			unit[i].tableNum = -1;
			unit[i].hitpoint = 5;
		}


		//敵の出現ポイントをセット
		enemyTable->standbyPos[0] = (Vec3(-4.65f, 0.0f, 18.15f));
		enemyTable->standbyPos[1] = (Vec3(0.65f, 0.0f, 10.8f));
		enemyTable->standbyPos[2] = (Vec3(9.1f, 0.0f, 18.65f));
		enemyTable->standbyPos[3] = (Vec3(-5.7f, 0.0f, 28.4f));

		//エネミーの最初のターゲット座標をセット

		//敵の目標地点をセット
		enemyTable->targetPos[0] = (Vec3(-0.3f, 0.0f, 20.4f));
		enemyTable->targetPos[1] = (Vec3(-2.15f, 0.0f, 16.65f));
		enemyTable->targetPos[2] = (Vec3(3.7f, 0.0f, 20.35f));
		enemyTable->targetPos[3] = (Vec3(-0.3f, 0.0f, 26.5f));



		//エネミーの初期座標をセット
		//エネミーの最初のターゲット座標をセット
		//エネミーの行動パターンをセット
		enemyTable->enemyData[0].standbyPos = enemyTable->standbyPos[0];
		enemyTable->enemyData[0].targetPos = enemyTable->targetPos[0];
		enemyTable->enemyData[0].nextEnemyNum = 3;
		enemyTable->enemyData[0].alive = TRUE;
		enemyTable->enemyData[0].AIType = AI_TYPE_SINGLE;//

		enemyTable->enemyData[1].standbyPos = enemyTable->standbyPos[1];
		enemyTable->enemyData[1].targetPos = enemyTable->targetPos[1];
		enemyTable->enemyData[1].nextEnemyNum = 4;
		enemyTable->enemyData[1].alive = TRUE;
		enemyTable->enemyData[1].AIType = AI_TYPE_MATO;//


		enemyTable->enemyData[2].standbyPos = enemyTable->standbyPos[2];
		enemyTable->enemyData[2].targetPos = enemyTable->targetPos[2];
		enemyTable->enemyData[2].nextEnemyNum = 5;
		enemyTable->enemyData[2].alive = TRUE;
		enemyTable->enemyData[2].AIType = AI_TYPE_MATO;//


		enemyTable->enemyData[3].standbyPos = enemyTable->standbyPos[0];
		enemyTable->enemyData[3].targetPos = enemyTable->targetPos[0];
		enemyTable->enemyData[3].nextEnemyNum = 6;
		enemyTable->enemyData[3].alive = TRUE;
		enemyTable->enemyData[3].AIType = AI_TYPE_MATO;//


		enemyTable->enemyData[4].standbyPos = enemyTable->standbyPos[1];
		enemyTable->enemyData[4].targetPos = enemyTable->targetPos[1];
		enemyTable->enemyData[4].nextEnemyNum = 7;
		enemyTable->enemyData[4].alive = TRUE;
		enemyTable->enemyData[4].AIType = AI_TYPE_MATO;//


		enemyTable->enemyData[5].standbyPos = enemyTable->standbyPos[2];
		enemyTable->enemyData[5].targetPos = enemyTable->targetPos[2];
		enemyTable->enemyData[5].nextEnemyNum = 8;
		enemyTable->enemyData[5].alive = TRUE;
		enemyTable->enemyData[5].AIType = AI_TYPE_SINGLE;//


		enemyTable->enemyData[6].standbyPos = enemyTable->standbyPos[0];
		enemyTable->enemyData[6].targetPos = enemyTable->targetPos[0];
		enemyTable->enemyData[6].nextEnemyNum = -1;
		enemyTable->enemyData[6].alive = TRUE;
		enemyTable->enemyData[6].AIType = AI_TYPE_SINGLE;//


		enemyTable->enemyData[7].standbyPos = enemyTable->standbyPos[1];
		enemyTable->enemyData[7].targetPos = enemyTable->targetPos[1];
		enemyTable->enemyData[7].nextEnemyNum = -1;
		enemyTable->enemyData[7].alive = TRUE;
		enemyTable->enemyData[7].AIType = AI_TYPE_MATO;//

		enemyTable->enemyData[8].standbyPos = enemyTable->standbyPos[3];
		enemyTable->enemyData[8].targetPos = enemyTable->targetPos[3];
		enemyTable->enemyData[8].nextEnemyNum = 9;
		enemyTable->enemyData[8].finishFlag = TRUE;
		enemyTable->enemyData[8].alive = TRUE;
		enemyTable->enemyData[8].AIType = AI_TYPE_SINGLE;//

		enemyTable->enemyData[9].standbyPos = enemyTable->standbyPos[3];
		enemyTable->enemyData[9].targetPos = enemyTable->targetPos[3];
		enemyTable->enemyData[9].nextEnemyNum = -1;
		enemyTable->enemyData[9].finishFlag = TRUE;
		enemyTable->enemyData[9].alive = TRUE;
		enemyTable->enemyData[9].AIType = AI_TYPE_SINGLE;//

		//敵の出現定義が済んだら、最初に出現させる敵のセットを行う


		unit[1].eState = ESTATE_STANDBY;
		unit[1].sprite3d->setVisible(true);//敵モデル非表示
		unit[1].visible = TRUE;//敵モデル非表示
		unit[1].sprite3d->setPosition3D(enemyTable->enemyData[0].standbyPos);//敵モデル非表示
		unit[1].targetPos = enemyTable->enemyData[0].targetPos;
		unit[1].StandbyPos = enemyTable->enemyData[0].standbyPos;
		unit[1].tableNum = 0;
		unit[1].AIType = enemyTable->enemyData[0].AIType;

		unit[2].eState = ESTATE_STANDBY;
		unit[2].sprite3d->setVisible(true);//敵モデル非表示
		unit[2].visible = TRUE;//敵モデル非表示
		unit[2].sprite3d->setPosition3D(enemyTable->enemyData[1].standbyPos);//敵モデル非表示
		unit[2].targetPos = enemyTable->enemyData[1].targetPos;
		unit[2].StandbyPos = enemyTable->enemyData[1].standbyPos;
		unit[2].tableNum = 1;
		unit[2].AIType = enemyTable->enemyData[1].AIType;


		unit[3].eState = ESTATE_STANDBY;
		unit[3].sprite3d->setVisible(true);//敵モデル非表示
		unit[3].visible = TRUE;//敵モデル非表示
		unit[3].sprite3d->setPosition3D(enemyTable->enemyData[2].standbyPos);//敵モデル非表示
		unit[3].targetPos = enemyTable->enemyData[2].targetPos;
		unit[3].StandbyPos = enemyTable->enemyData[2].standbyPos;
		unit[3].tableNum = 2;
		unit[3].AIType = enemyTable->enemyData[2].AIType;


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
	unit[0].Init();//メンバ変数の初期化をしておく
	addChild(unit[0].sprite3d);

	unit[0].sprite3d->setScale(1.0f);
	unit[0].sprite3d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[0].sprite3d->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[0].Init(0, UKIND_MAP);
	return TRUE;
}



/**
*	レイヤーの更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::UpdateLayer()
{
	UpdatePlayer();//プレイヤーの更新
	UpdateEnemy();//エネミーの更新
	UpdateBullets();//敵弾の更新
	CheckHit();//当たり判定のチェック

	CheckNextStage();//
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
	if (0 == GameMasterM->waitFlag)	//次の目的地を検索
	{
		player.targetPos = GameMasterM->stagePoint[GameMasterM->sPoint].pos;//
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
	else if (1 == GameMasterM->waitFlag)
	{
		GameMasterM->waitFlag = 2;
	}
	else if (2 == GameMasterM->waitFlag)//次の目的地まで走る処理
	{
		UpdatePlayer();//プレイヤーの更新
		Vec3 tmpPos = player.wrapper->getPosition3D();

		//一定以上目的地に近付いたら、カメラとプレイヤーを回転させる準備を行う
		if (0.15f * 0.15f >= (player.targetPos.x - tmpPos.x) * (player.targetPos.x - tmpPos.x)
			+ (player.targetPos.z - tmpPos.z) *(player.targetPos.z - tmpPos.z))
		{
			GameMasterM->waitFlag = 3;
			Vec3 tmp = player.sprite3d->getRotation3D();//プレイヤーの今の角度をもとに
			rotationR = GameMasterM->stagePoint[GameMasterM->sPoint].rot.y - tmp.y;//戦闘時の角度との差を計算する
			rotationR *= 0.05;//1フレームごとに変化する角度を計算
			rotationCount = 0;

			if (POINT_CHANGE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)
			{
				changeCameraPos = Vec3(0.0f, 0.0f, 0.0f);
				changeCameraRot = Vec3(0.0f, 0.0f, 0.0f);
			}
			else if (POINT_FINISH == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)
			{
				changeCameraPos = Vec3(0.0f, 0.0f, 0.0f);
				changeCameraRot = Vec3(0.0f, 0.0f, 0.0f);
			}
			else if (POINT_BATTLE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)
			{
				if (PSIDE_LEFT == GameMasterM->stagePoint[GameMasterM->sPoint].playerSide)
				{
					//カメラとプレイヤーの位置も滑らかに変化させる
					changeCameraPos = Vec3(C_SETX_L - W_SETX, C_SETY_L - W_SETY, C_SETZ_L - W_SETZ) * 0.05;
					changeCameraRot = Vec3(C_ROTX_L - W_ROTX, C_ROTY_L - W_ROTY, C_ROTZ_L - W_ROTZ)* 0.05;
				}
				else
				{
					//カメラとプレイヤーの位置も滑らかに変化させる
					changeCameraPos = Vec3(C_SETX_R - W_SETX, C_SETY_R - W_SETY, C_SETZ_R - W_SETZ) * 0.05;
					changeCameraRot = Vec3(C_ROTX_R - W_ROTX, C_ROTY_R - W_ROTY, C_ROTZ_R - W_ROTZ)* 0.05;
				}
			}
			player.speed = 0.0f;
			player.speedVec = Vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else if (3 == GameMasterM->waitFlag)	//目的地に到着したら、カメラを回転させる
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
				player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot);
				player.wrapper->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pos);

				GameMasterM->sPoint++;//座標と角度が設定できたらポイントを先に進める
				GameMasterM->waitFlag = 0;
			}
			else if (POINT_BATTLE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//次のウェーブに到達した
			{
				//座標と角度をセット
				player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot);
				player.wrapper->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pos);

				GameMasterM->playerSide = GameMasterM->stagePoint[GameMasterM->sPoint].playerSide;//現在が左右どちらに立っているかを確認

				//プレイヤーの回避用ノードをもとに、回避座標を取得する
				if (PSIDE_LEFT == GameMasterM->playerSide)
				{
					//目標角度をもとにノードの移動後座標を取得
					Vec2 pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					Vec3 newPos = player.wrapper->getPosition3D() + Vec3(pos.x, 0.0f, pos.y);
					player.wrapper->setPosition3D(newPos);//wrapper

					pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					newPos = player.sprite3d->getPosition3D() - Vec3(pos.x, 0.0f, pos.y);
					player.sprite3d->setPosition3D(newPos);//wrapper

					//目標角度をもとに、回避時のカメラ移動座標を計算
					Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, PSIDE_LEFT);
					//tmpがプレイヤーの親ノードに対する回避後カメラ座標の位置（相対）

					//回避時のカメラ移動前の座標を確保
					camTarget = Vec3(tmp.x, 0.0f, tmp.y);// +player.wrapper->getPosition3D();
					camCenter = player.wrapper->getPosition3D();
				}
				else
				{
					//目標角度をもとにノードの移動後座標を取得
					Vec2 pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					Vec3 newPos = player.wrapper->getPosition3D() + Vec3(pos.x, 0.0f, pos.y);
					player.wrapper->setPosition3D(newPos);//wrapper

					pos = calcRot(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, GameMasterM->stagePoint[GameMasterM->sPoint].playerSide);
					newPos = player.sprite3d->getPosition3D() - Vec3(pos.x, 0.0f, pos.y);
					player.sprite3d->setPosition3D(newPos);//wrapper


					//目標角度をもとに、回避時のカメラ移動座標を計算
					Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, PSIDE_RIGHT);
					camTarget = Vec3(tmp.x, 0.0f, tmp.y);
					//回避時のカメラ移動前の座標を確保
					//					camTarget = Vec3(tmp.x, 0.0f, tmp.y) + player.wrapper->getPosition3D();
					//					camCenter = player.wrapper->getPosition3D();
				}
				GameMasterM->SetGameState(GSTATE_PLAY_INIT);//戦闘ポイントに到着したら、ウェイトからプレイに移行

				//左右に応じたアイドルモーションを開始する
				player.sprite3d->stopAllActions();

				//player.sprite3d->startAnimationLoop(idle);
			}
			else if (POINT_CLEAR == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//クリアしたら
			{
				//if (POINT_CHANGE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//進行方向切り替え
				//{
				//	player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot);
				//	player.wrapper->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pos);

				//	GameMasterM->sPoint++;//座標と角度が設定できたらポイントを先に進める
				//	GameMasterM->waitFlag = 0;
				//}

				player.sprite3d->setScale(1.0f);
				player.sprite3d->setRotation3D(GameMasterM->stagePoint[POINT_START].rot);//プレイヤーは正面を向く
				player.wrapper->setPosition3D(GameMasterM->stagePoint[POINT_START].pos);
				GameMasterM->sPoint = POINT_STAGE1;//ステージ1に走る
				GameMasterM->waitFlag = 0;
				GameMasterM->wave = 0;
			}
			else
			{
				int a = 0;
			}
		}
	}
	else if (4 == GameMasterM->waitFlag)	//次の戦闘ポイントに到着したら、ウェイトからプレイに移行
	{

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
	player.Update();
	//マズルの更新
	//	player.muzzleUpdate();

	//２：プレイヤーの状態を取得して場合分け
	switch (GameMasterM->GetPlayerState())
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

		break;
	case PSTATE_RUN://ウェイト状態

		break;
	case PSTATE_DEAD:
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

	if (TSTATE_ON == GameMasterM->GetTouchState())//タッチされたら
	{
		auto s = Director::getInstance()->getWinSize();//画面サイズ取得
		const Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得

		//		player.muzzleflagOn();

		int tmpFlag = 0;

		if (PSIDE_LEFT == GameMasterM->playerSide)//プレイヤーが左に立っている
		{
			//攻撃可能範囲をタッチしていれば
			if (tPos.x > s.width *(1.0f - BATTLE_FEILD_X))
			{
				tmpFlag = 1;//
			}
			//回避UI付近をタッチしたら
			else if (tPos.x >= s.width * HIDE_UI_X0 && tPos.x < s.width *HIDE_UI_X1
				&& tPos.y >= s.height*HIDE_UI_Y0 && tPos.y < s.height*HIDE_UI_Y1)
			{
				tmpFlag = 2;
			}
		}
		else//右に立っている
		{
			//攻撃可能範囲をタッチしていれば
			if (tPos.x < s.width * BATTLE_FEILD_X)
			{
				tmpFlag = 1;//
			}
			//回避UI付近をタッチしたら
			else if (tPos.x < s.width * (1.0f - HIDE_UI_X0) && tPos.x >= s.width *(1.0f - HIDE_UI_X1)
				&& tPos.y >= s.height*HIDE_UI_Y0 && tPos.y < s.height*HIDE_UI_Y1)
			{
				tmpFlag = 2;
			}
		}


		//タッチ状態に応じて分岐
		if (0 == tmpFlag)
		{
			//タッチしていない
		}
		else if (1 == tmpFlag)
		{
			//残弾に応じて処理を分ける
			if (0 >= GameMasterM->GetPlayerBullets())
			{

			}
			else
			{
				//アニメーションを再生
				GameMasterM->SetPlayerState(PSTATE_SHOT);
				player.sprite3d->stopAllActions();
				player.sprite3d->startAnimationLoop(shot, 0, 8 / 60);
				GameMasterM->rapidFrame = -1;//連射フレームを-1に初期化
				GameMasterM->flgPlayerATK = FALSE;//
				GameMasterM->hideFrame = 0;
				player.animCount = 0.0f;//
			}
		}
		else
		{
			GameMasterM->SetPlayerState(PSTATE_DODGE);//回避に移行
			player.InitFrame();//フレームをリフレッシュ
			GameMasterM->hideFrame = 0;

			player.sprite3d->stopAllActions();
			player.sprite3d->startAnimationReverse(h_shot);//回避モーションを再生
			player.nowTimeFrom = clock() * 0.001f;//現在時刻を取得
			player.nowTimeBefore = clock() * 0.001f;

			player.setAnimEndTime(STS_HIDEWAIT * 0.01666f);//回避モーションにかかる時間をセット
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
	//ループ時間を取得
	auto director = Director::getInstance();
	auto loopTime = director->getDeltaTime();

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

	GameMasterM->rapidFrame += 1 * loopTime;//連射フレームを加算する
	if (0 >= GameMasterM->GetPlayerBullets())
	{
		//残弾がない場合
		GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
		player.InitFrame();//フレームをリフレッシュ
		GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする
		player.sprite3d->stopAllActions();
	}
	else if (TSTATE_ON == GameMasterM->GetTouchState() || TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		//残弾がある場合
		//一定フレームごとに攻撃判定をONにする
		if (0 == ((int)GameMasterM->rapidFrame % STS_RAPIDSPEED))
		{
			GameMasterM->flgPlayerATK = TRUE;
			GameMasterM->AddPlayerBullets(-1);//弾数を減らす
			//音声はフラグ成立時に鳴らす
			//sound->playSE("Shot.wav");
		}
		else
		{
			GameMasterM->flgPlayerATK = FALSE;
		}

		GameMasterM->SetPlayerState(PSTATE_SHOT);//ステート状態はそのまま

	}
	else if (TSTATE_RELEASE == GameMasterM->GetTouchState())//タッチを離したら
	{
		GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
		player.InitFrame();//フレームをリフレッシュ
		GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする
		player.sprite3d->stopAllActions();
		player.sprite3d->startAnimation(shot);
	}
	else
	{
		GameMasterM->SetPlayerState(PSTATE_IDLE);
		player.InitFrame();//フレームをリフレッシュ
		GameMasterM->flgPlayerATK = FALSE;//攻撃判定をオフにする
		player.sprite3d->stopAllActions();

		//アニメーションを再生
		player.sprite3d->startAnimation(shot);
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
	auto director = Director::getInstance();
	auto loopTime = director->getDeltaTime();

	player.animCount += loopTime;
	player.nowTimeTo = clock() * 0.001f;
	float time = player.nowTimeTo - player.nowTimeFrom;//
	float lTime = player.nowTimeTo - player.nowTimeBefore;
	player.nowTimeBefore = clock() * 0.001f;

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
	GameMasterM->hideFrame += loopTime;//回避フレームを加算する

	int state = GameMasterM->GetTouchState();//現在のタッチ状態を取得

	//無敵時間の判定を行う
	if (STS_MUTEKISTART <= GameMasterM->hideFrame)//無敵開始フレームに達したら
	{
		GameMasterM->playerHitFlag = FALSE;//当たり判定を無効化する
	}

	//リロード判定を行う
	if (STS_RELOADSTART <= GameMasterM->hideFrame)//リロード開始フレームに達したら
	{
		GameMasterM->SetPlayerBullets(STS_MAXBULLETS);//弾数を回復する
	}

	//回避完了フレームに達したら
	//	if (STS_HIDEWAIT <= GameMasterM->hideFrame)
	if (player.getAnimEndTime() <= time)
		//	if (0 == player.sprite3d->checkAnimationState())//アニメーションが終了したら
	{
		GameMasterM->SetPlayerState(PSTATE_HIDE);//隠れている状態に移行
		//リロードモーションが終了した後は、リロードモーションを行う
		player.sprite3d->stopAllActions();
		//player.sprite3d->startAnimation(h_reload);//リロードモーションを再生

		player.animCount = 0.0f;
		time = 0.0f;
		//座標と角度をセットしてキャラクターの座標を補正
		if (PSIDE_LEFT == GameMasterM->playerSide)
		{
			player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot + Vec3(0.0f, 96.0f, 0.0f));
			player.wrapper->setRotation3D(Vec3(0.0f, -96.0f, 0.0f));
		}
		else
		{
			player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot - Vec3(0.0f, 96.0f, 0.0f));
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
			GameMasterM->hideFrame = STS_HIDEWAIT - GameMasterM->hideFrame;//突撃のフレーム数をセットする

			float startTime = STS_HIDEWAIT * 0.01666f - time;//

			player.setAnimEndTime(STS_HIDEWAIT * 0.01666f - startTime);//アニメーション終了までの残りフレームをセット
			player.sprite3d->stopALLAnimation();//モーション終了
			player.sprite3d->startAnimation(h_shot, startTime, STS_HIDEWAIT * 0.01666f);//モーション終了

			player.nowTimeTo = clock() * 0.001f;
			player.nowTimeBefore = clock() * 0.001f;
		}
		else if(TSTATE_MOVE == state || TSTATE_ON == state)//ホールド状態
		{
			//回避動作中は指定座標を軸に座標移動を行う

			{
				//プレイヤーの座標の更新
				//float rot = 96.0f / STS_HIDEWAIT;
				float rot = lTime * 90.0f / (STS_HIDEWAIT / 60.0f);

				Vec3 tmp = player.wrapper->getRotation3D();
				tmp.y -= rot * loopTime;
				player.wrapper->setRotation3D(tmp);//毎フレームP親ノードの角度を更新する
				tmp = player.sprite3d->getRotation3D();
				tmp.y += rot * loopTime;
				player.sprite3d->setRotation3D(tmp);//プレイヤーの角度は逆に更新し、キャラクターの向きを正面に向かせる

				//回避に合わせてカメラの座標を補正する
				player.cameraAjust = Vec3(camTarget.x * GameMasterM->hideFrame, camTarget.y * GameMasterM->hideFrame, camTarget.z * GameMasterM->hideFrame);//ループごとの移動量を計算
			}
			else
			{
				//プレイヤーの座標の更新
				float rot = 96.0f / STS_HIDEWAIT;
				Vec3 tmp = player.wrapper->getRotation3D();
				tmp.y += rot * loopTime;
				player.wrapper->setRotation3D(tmp);
				tmp = player.sprite3d->getRotation3D();
				tmp.y -= rot * loopTime;
				player.sprite3d->setRotation3D(tmp);

				//回避に合わせてカメラの座標を補正する
				player.cameraAjust = Vec3(camTarget.x * GameMasterM->hideFrame, camTarget.y * GameMasterM->hideFrame, camTarget.z * GameMasterM->hideFrame);//ループごとの移動量を計算
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
	if(PSIDE_LEFT == GameMasterM->playerSide)
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

	if(TSTATE_ON == GameMasterM->GetTouchState() || TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		//タッチ中はリロードを再生、再生後はモーション停止
		player.cameraAjust = Vec3(camTarget.x * STS_HIDEWAIT, camTarget.y * STS_HIDEWAIT, camTarget.z * STS_HIDEWAIT);//カメラ位置
	}
	else if(TSTATE_RELEASE == GameMasterM->GetTouchState())//離されれば
	{
		GameMasterM->SetPlayerState(PSTATE_APPEAR);
		player.sprite3d->startAnimation(h_shot);
		GameMasterM->hideFrame = 0;
		player.InitFrame();//フレームをリフレッシュ

		player.nowTimeFrom = clock() * 0.001f;//現在時刻を取得
		player.nowTimeBefore = clock() * 0.001f;
		player.setAnimEndTime(STS_HIDEWAIT * 0.01666f);
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
	//
	auto director = Director::getInstance();
	auto loopTime = director->getDeltaTime();

	player.animCount += loopTime;

	player.nowTimeTo = clock() * 0.001f;//現在時刻を取得
	float time = player.nowTimeTo - player.nowTimeFrom;//アニメーション再生時刻と現在時刻の差を取得
	float lTime = player.nowTimeTo - player.nowTimeBefore;//アニメーション再生1ループにかかった時間を取得
	player.nowTimeBefore = clock() * 0.001f;



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

	//１：突撃終了フレームが終了するとActionIdleに移行する

	int flag = GameMasterM->GetTouchFlag();//現在のタッチ状態を取得

	GameMasterM->hideFrame += loopTime;//回避フレームを加算する

	//無敵時間の判定を行う
	if (STS_MUTEKISTART <= GameMasterM->hideFrame)//無敵終了フレームに達したら
	{
		GameMasterM->playerHitFlag = TRUE;//当たり判定を有効化する
	}

	//回避完了の判定
	if (player.getAnimEndTime() <= time)
	//	if (STS_HIDEWAIT <= GameMasterM->hideFrame)//突撃フレームに達したら
	//	if(0 == player.sprite3d->checkAnimationState())//アニメーションが終了したら
	{
		//必要ならばモーションの停止を行う
		GameMasterM->SetPlayerState(PSTATE_IDLE);//アイドル状態に移行
		player.sprite3d->stopAllActions();

		//座標と角度をセットしてキャラクターの座標を補正
		player.sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot);
		player.wrapper->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));

		//座標と角度をセットしてカメラの座標を補正
		Vec2 tmp = calcCamPos3(GameMasterM->stagePoint[GameMasterM->sPoint].rot.y, GameMasterM->playerSide);
		camTarget = Vec3(tmp.x, 0.0f, tmp.y);
		player.sprite3d->startAnimation(idle);
	}
	else
	{
		if (PSIDE_LEFT == GameMasterM->playerSide)
		{
			//回避フレームに比例してカメラの回転を変化させる
			//float rot = 96.0f / STS_HIDEWAIT;
			float rot = lTime * 90.0f / (STS_HIDEWAIT / 60.0f);
			Vec3 tmp = player.wrapper->getRotation3D();
			tmp.y += rot * loopTime;
			player.wrapper->setRotation3D(tmp);//プレイヤーの親ノード（回避軸）の角度を更新する
			tmp = player.sprite3d->getRotation3D();
			tmp.y -= rot * loopTime;
			player.sprite3d->setRotation3D(tmp);//プレイヤー自身の角度を更新する

			//回避に合わせてカメラの座標を補正する
			Vec3 moveVec = -camTarget + camCenter;//必要な移動量
			player.cameraAjust = Vec3(camTarget.x * (STS_HIDEWAIT - GameMasterM->hideFrame), camTarget.y * (STS_HIDEWAIT - GameMasterM->hideFrame), camTarget.z * (STS_HIDEWAIT - GameMasterM->hideFrame));//ループごとの移動量を計算

		}
		else
		{
			//回避フレームに比例してカメラの回転を変化させる
			float rot = 96.0f / STS_HIDEWAIT;//
			Vec3 tmp = player.wrapper->getRotation3D();
			tmp.y -= rot * loopTime;
			player.wrapper->setRotation3D(tmp);//プレイヤーの親ノード（回避軸）の角度を更新する
			tmp = player.sprite3d->getRotation3D();
			tmp.y += rot * loopTime;
			player.sprite3d->setRotation3D(tmp);//プレイヤー自身の角度を更新する

			//回避に合わせてカメラの座標を補正する
			player.cameraAjust = Vec3(camTarget.x * (STS_HIDEWAIT - GameMasterM->hideFrame), camTarget.y * (STS_HIDEWAIT - GameMasterM->hideFrame), camTarget.z * (STS_HIDEWAIT - GameMasterM->hideFrame));//ループごとの移動量を計算
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
	for (int i = 21; i <= 40; i++)
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

		unit[num].sprite3d->setScale(1.0f);

		////当たり判定の定義（仮）
		unit[num].collisionPos = Vec3(0.3, 0.4, 0.3);//当たり判定矩形の大きさを設定
		unit[num].SetCollision();//当たり判定をセット
		//		unit[num].sprite3d->setScale(1.0f);//当たり判定をセット
//		unit[num].sprite3d->setScale(1.0f);//
		unit[num].sprite3d->setScale(0.5f);//

		//弾を撃ったエネミーの座標と、プレイヤーの座標を元に、弾の移動方向を求める
		Vec3 enemyPos = unit[enemy_num].sprite3d->getPosition3D();

		//プレイヤーに向けて弾を発射する
		unit[num].speedVec = GameMasterM->stagePoint[GameMasterM->sPoint].pos - enemyPos;//

		//ベクトルの正規化を行う
		unit[num].speedVec.normalize();

		//キャラクターの向きを調整
		double r = atan2f(unit[num].speedVec.z, unit[num].speedVec.x);
		r = CC_RADIANS_TO_DEGREES(r);

		unit[num].sprite3d->setRotation3D(Vec3(-90.0f, 90.0f - r, 0.0f));//
		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 90.0f - r, 0.0f));//


		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
//		unit[num].speed = 1.0f;
		unit[num].speed = 12.0f;
		unit[num].speedVec.x *= unit[num].speed;
		unit[num].speedVec.z *= unit[num].speed;
		//		unit[num].speedVec.y = 0;//yは今のところ0で扱う

		unit[num].sprite3d->setPosition3D(enemyPos);
		unit[num].sprite3d->setPositionY(1.2f);

		//弾を画面に描画する
		unit[num].visible = TRUE;
		unit[num].sprite3d->setVisible(true);
	}
}


/*

*/
void GameModelsLayer::UpdateBullets()
{
	//全ての敵弾ユニットを更新
	for (int num = 21; num <= 40; num++)
	{
		if (TRUE == unit[num].visible && TRUE == unit[num].valid)
		{
			unit[num].Update();//座標と一緒に当たり判定を移動
		}

		//@テストの消去処理
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
	const int count = player.GetFrame();

	//攻撃判定フラグがONのときのみ攻撃判定を処理
	if (TRUE == GameMasterM->flgPlayerATK)
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

		Vec3 tmpPosNear = Vec3(tPos.x, tPos.y, -1.0f);//-1.0f == 視錘台の近面（near plane）
		Vec3 tmpPosFar = Vec3(tPos.x, tPos.y, 1.0f);//1.0f == 視錘台の遠面（far plane）

		cam3d->setPosition3D(cPos);
		//cam3d->setRotation3D(cRot);

		cam3d->unproject(s, &tmpPosNear, &rayStart);//near planeの3次元座標を取得
		cam3d->unproject(s, &tmpPosFar, &rayEnd);

		//rayStart = cam3d->getPosition3D();


		Ray touchRay(rayStart, rayEnd);//仮レイを設定

		//レイの当たり判定
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind && unit[i].eState != ESTATE_DAMAGED && unit[i].eState != ESTATE_DEAD)
			{
				if (touchRay.intersects(unit[i].obbHead))//タッチ座標の法線と敵の当たり判定が接触したかをチェック
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
		for (int i = 21; i <= 40; i++)
		{
			if (TRUE == unit[i].valid && TRUE == unit[i].visible)
			{
				//プレイヤーとの当たり判定を処理
				Vec3 d = player.sprite3d->getPosition3D() - unit[i].sprite3d->getPosition3D();
				if (0.1f >= sqrtf(((sqrtf(d.x * d.x + d.y * d.y)) * (sqrtf(d.x * d.x + d.y * d.y))) + (d.z * d.z)))
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
	//弾の画面外処理

	//全ての敵弾ユニットを更新
	for (int i = 21; i <= 40; i++)
	{
		if (FALSE != unit[i].valid && UKIND_EBULLET == unit[i].kind)
		{

		}
	}
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
	for (int i = 1; i <= 20; i++)//1番~20番を敵に割り当て
	{
		if (TRUE == unit[i].valid && TRUE == unit[i].visible)//エネミーが表示されていれば
		{
			switch (unit[i].AIType)
			{
			case AI_TYPE_MATO:
				ActionEnemy1(i);//
				break;
			case AI_TYPE_SINGLE:
				ActionEnemy2(i);//
				break;

			case AI_TYPE_SINGLE_J:

				break;
			default:
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
void GameModelsLayer::ActionEnemy1(int num)
{
	unit[num].Update();//フレーム・座標・当たり判定の更新

	//敵キャラクターのhpが0になったら
	if (unit[num].hitpoint <= 0 && ESTATE_DAMAGED != unit[num].eState && ESTATE_DEAD != unit[num].eState)
	{
		unit[num].eState = ESTATE_DAMAGED;//ダメージ状態に変更
	}

	switch (unit[num].eState)
	{
	case ESTATE_SLEEP://プレイヤーが休眠状態



		break;
	case ESTATE_STANDBY://キャラクターが目標地点へと走るモーション
	{
		unit[num].eState = ESTATE_MOVE;//待機が終わったら移動

		unit[num].speed = 5.0f;//スピードは後で調整する

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

		unit[num].sprite3d->startAnimationLoop("run");

	}
		break;
	case ESTATE_IDLE://アイドル状態


		break;
	case ESTATE_MOVE://移動状態
	{
		Vec3 tmpPos = unit[num].sprite3d->getPosition3D();

		//一定以上目的地に近付いたら
		if (0.1f >= sqrtf(unit[num].targetPos.x - tmpPos.x) * (unit[num].targetPos.x - tmpPos.x)
			+ (unit[num].targetPos.y - tmpPos.y) *(unit[num].targetPos.y - tmpPos.y))
		{
			//プレイヤーの立っている座標を向く

			Vec3 tmpPos = GameMasterM->stagePoint[GameMasterM->sPoint].pos;//プレイヤーの立っている座標の取得
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

			unit[num].sprite3d->startAnimationLoop("dammy_shot");
		}
	}
		break;

	case ESTATE_WAIT://ウェイト

		break;

	case ESTATE_ATTACK1://攻撃


		break;
	case ESTATE_ATTACK2:
		break;

	case ESTATE_ATTACK3:
		break;

	case ESTATE_DAMAGED://被弾

		//HPが0になったら

		unit[num].sprite3d->stopALLAnimation();
		unit[num].sprite3d->startAnimation("dei2");
		unit[num].eState = ESTATE_DEAD;


		//
		//if( random == 0)
		//{
		//	sound -> playSE("Damage_01.wav");
		//}
		//else if( random == 1)
		//{
		//	sound -> playSE("Damage_02.wav");
		//}
		//else if( random == 2)
		//{
		//	sound -> playSE("Damage_03.wav");
		//}
		//else if( random == 3)
		//{
		//	sound -> playSE("Damage_04.wav");
		//}

		//共通

		//		unit[num].eState = ESTATE_STANDBY;
		//	unit[num].hitpoint = 5;
		//個別

		//		ShootBullet(num);


		//				unit[num].sprite3d->setVisible( false);
		break;
	case ESTATE_DEAD://死亡
		if (0 == unit[num].sprite3d->checkAnimationState())//死亡アニメーションが終了したら
		{
			unit[num].sprite3d->setVisible(false);
			unit[num].visible = FALSE;
			//unit[num].eState = ESTATE_END;
			setNextEnemy(num);//
		}
		break;
	case ESTATE_END://死んだ敵の処分
		//敵が死んだら次の敵を確認する
		//
		break;
	}
}
/**
*	エネミー2の更新
*
*	@author	sasebon
*	@param	敵Unitの配列番号
*	@return	なし
*	@date	2/5 Ver 1.0
*/
void GameModelsLayer::ActionEnemy2(int num)
{
	unit[num].Update();//フレーム・座標・当たり判定の更新

	auto director = Director::getInstance();
	auto loopTime = director->getDeltaTime();


	//敵キャラクターのhpが0になったら
	if (unit[num].hitpoint <= 0 && ESTATE_DAMAGED != unit[num].eState && ESTATE_DEAD != unit[num].eState)
	{
		unit[num].eState = ESTATE_DAMAGED;//ダメージ状態に変更
	}

	switch (unit[num].eState)
	{
	case ESTATE_SLEEP://プレイヤーが休眠状態



		break;
	case ESTATE_STANDBY://キャラクターが目標地点へと走るモーション
	{
		unit[num].eState = ESTATE_MOVE;//待機が終わったら移動

		unit[num].speed = 5.0f;//スピードは後で調整する

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

		unit[num].sprite3d->startAnimationLoop("run");

	}
		break;
	case ESTATE_IDLE://アイドル状態
	{
		unit[num].atkFrame--;
		if (unit[num].atkFrame <= 0)
		{
			unit[num].eState = ESTATE_ATTACK1;//アタック状態に移る
			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
			unit[num].sprite3d->startAnimation("shot");
			if (ESTATE_ATTACK1 == unit[num].eState)
			{
				unit[num].atkFrame = 60.0f;//弾を発射するまでの残りフレーム
			}

		}
		else
		{

		}
	}
		break;
	case ESTATE_MOVE://移動状態
	{
		Vec3 tmpPos = unit[num].sprite3d->getPosition3D();

		//一定以上目的地に近付いたら
		if (0.1f >= sqrtf(unit[num].targetPos.x - tmpPos.x) * (unit[num].targetPos.x - tmpPos.x)
			+ (unit[num].targetPos.y - tmpPos.y) *(unit[num].targetPos.y - tmpPos.y))
		{
			//プレイヤーの立っている座標を向く

			Vec3 tmpPos = GameMasterM->stagePoint[GameMasterM->sPoint].pos;//プレイヤーの立っている座標の取得
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

			unit[num].sprite3d->startAnimationLoop("idle");
			unit[num].atkFrame = 60;//攻撃動作に移るまでの「秒数」//@秒ではなくフレームで統一する
		}
	}
		break;

	case ESTATE_WAIT://ウェイト

		break;

	case ESTATE_ATTACK1://攻撃

		//タイミングを合わせて射撃を行う
		unit[num].atkFrame -= loopTime * 60.0f;//アタックフレームを減少させていく
		if (0.0f >= unit[num].atkFrame)
		{
			//フレームが0になったら
			//ShootBullet(num);
			unit[num].atkFrame = 20.0f;//次の攻撃までのフレームを設定
		}
		

		//アニメーションが終了したら
		if (0 == unit[num].sprite3d->checkAnimationState())
		{
			unit[num].sprite3d->stopALLAnimation();//現在のモーションを終了し
			unit[num].sprite3d->startAnimation("idle");//
			unit[num].atkFrame = 200;

			unit[num].eState = ESTATE_IDLE;
		}

		break;
	case ESTATE_ATTACK2:
		break;

	case ESTATE_ATTACK3:
		break;

	case ESTATE_DAMAGED://被弾

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
		break;
	case ESTATE_DEAD://死亡
		if (0 == unit[num].sprite3d->checkAnimationState())//死亡アニメーションが終了したら
		{
			unit[num].sprite3d->setVisible(false);
			unit[num].visible = FALSE;
			//unit[num].eState = ESTATE_END;
			setNextEnemy(num);//
		}
		break;
	case ESTATE_END://死んだ敵の処分
		//敵が死んだら次の敵を確認する
		//
		break;
	}
}



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
	if (-1 == nextNum)//次のモデルが設定されていなければ
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
		unit[n].AIType = enemyTable->enemyData[nextNum].AIType;
		unit[n].hitpoint = 5;

	}
}


int GameModelsLayer::CheckNextStage(void)
{
	if (GSTATE_PLAY == GameMasterM->GetGameState())
	{
		for (int i = 0; i <= 100; i++)//1番~20番を敵に割り当て
		{
			if (TRUE == enemyTable->enemyData[i].alive)
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
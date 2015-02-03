
#include "GameModelsLayer.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
#include "Sprite3D.h"
#include "Sound.h"

#else

#include "C++/Base/Sprite3D.h"
#include "C++/Base/GameMaster.h"
#include "C++/System/Sound.h"

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
	if(!Layer::init())
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
	InitAllModels();

	InitPlayer(0);//とりあえず引数0
	InitMap(0);//正規のマップデータが降りてくるまでいったん保留します
	InitEnemy(0);
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
	for(int i = 0; i < MAX_UNIT; i++)
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "player";
	std::string fileName2 = "Player.anime";
#else
	std::string fileName1 = "player/player";
	std::string fileName2 = "Player.anime";
#endif
	player.sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);
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

	GameMasterM->nowBullets = STS_MAXBULLETS;//
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
	//※ステージスクリプトの内容を読み込んで初期化を行います


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "enemy";
	std::string fileName2 = "Enemy.anime";
#else
	std::string fileName1 = "enemy/enemy";
	std::string fileName2 = "Enemy.anime";
#endif

	int num = -1;
	switch(GameMasterM->wave)
	{
	case 0://ステージ1

		for (int i = 0; i < 20; i++)
		{
			num = SearchFreeUnit();
			if (-1 == num)
			{
				return false;
			}
			//共通
			unit[num].Init();//メンバ変数の初期化をしておく
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);
#else
			unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);
#endif
			unit[num].Init(num, UKIND_ENEMY);
			unit[num].wrapper = Node::create();//モデルの親ノード
			unit[num].wrapper->addChild(unit[num].sprite3d);
			addChild(unit[num].wrapper);

			//当たり判定の定義（仮）
			unit[num].collisionPos = Vec3(0.8f, 1.0f, 0.8f);
			unit[num].SetCollision();
			unit[num].sprite3d->setScale(1.0f);

			unit[num].eState = ESTATE_STANDBY;
			unit[num].hitpoint = 5;
			//個別
			unit[num].sprite3d->setPosition3D(Vec3(14.4f, 0.0f, 16.8f));
			unit[num].targetPos = Vec3(2.0f + i * 0.7f, 0.0f, 6.5f + i * 0.6f);
			unit[num].eWaitFrame = 20;


			//共通
			//unit[num].Init();//メンバ変数の初期化をしておく
			//unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2, fileName3);
			//unit[num].Init(num, UKIND_ENEMY);
			//unit[num].wrapper = Node::create();//モデルの親ノード
			//unit[num].wrapper->addChild(unit[num].sprite3d);
			//addChild(unit[num].wrapper);

			////当たり判定の定義（仮）
			//unit[num].collisionPos = Vec3(0.8f, 1.0f, 0.8f);
			//unit[num].SetCollision();
			//unit[num].sprite3d->setScale(1.0f);

			//unit[num].eState = ESTATE_STANDBY;
			////個別
			//unit[num].sprite3d->setPosition3D(Vec3(i * 0.2f, 0.0f, i * 0.1));
			//unit[num].targetPos = Vec3(14.5f, 0.0f, 4.5f);
			//unit[num].eWaitFrame = 20;
		}
	case 1:

		break;
	defalut:
		break;
	}
	return TRUE;
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
	switch(GameMasterM->wave)
	{
	case 0://ステージ1

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
	int num = SearchFreeUnit();
	if(-1 == num)
	{
		return false;
	}
	unit[num].Init();//メンバ変数の初期化をしておく

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "StageVer5";
	//std::string fileName2 = "stage_tex.png";
#else
//	std::string fileName1 = "Stage/StageVer5";
	std::string fileName1 = "Stage/stage4";
#endif
	unit[num].sprite3d = _Sprite3D::create(fileName1);

	addChild(unit[num].sprite3d);

	unit[num].sprite3d->setScale(1.0f);
	unit[num].sprite3d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[num].sprite3d->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[num].Init(num, UKIND_MAP);
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

	static float rot;
	//rot -= 0.5f;
	//player.sprite3d->setRotation3D(Vec3(0.0f, rot, 0.0f));
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

	if(0 == GameMasterM->waitFlag)	//次の目的地を検索
	{
		player.targetPos = GameMasterM->stagePoint[GameMasterM->sPoint].pos;//
		player.speed = 0.05f;//スピードは後で調整する

		player.speedVec = player.targetPos - player.wrapper->getPosition3D();//この方法が正しければ使用する

		//ベクトルの正規化を行う
		player.speedVec.normalize();

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		player.speedVec.x *= player.speed;
		player.speedVec.z *= player.speed;

		player.speedVec.y = 0;//yは今のところ0で扱う
		player.sprite3d->startAnimationLoop("run");
		GameMasterM->waitFlag = 1;


		//カメラの位置が滑らかに変化する処理を入れる
		GameMasterM->SetCamera3DPos(Vec3(W_SETX, W_SETY, W_SETZ));//プレイヤー（親ノード）とカメラの位置関係をセット
		GameMasterM->SetCamera3DRot(Vec3(W_ROTX, W_ROTY, W_ROTZ));

	}
	else if(1 == GameMasterM->waitFlag)	//次の目的地まで走る処理
	{
		UpdatePlayer();//プレイヤーの更新
		Vec3 tmpPos = player.wrapper->getPosition3D();

		//一定以上目的地に近付いたら、カメラとプレイヤーを開店させる準備を行う
		if(0.2f * 0.2f >= (player.targetPos.x - tmpPos.x) * (player.targetPos.x - tmpPos.x)
			+ (player.targetPos.y - tmpPos.y) *(player.targetPos.y - tmpPos.y))
		{
			GameMasterM->waitFlag = 2;
			Vec3 tmp = player.sprite3d->getRotation3D();//プレイヤーの今の角度をもとに
			rotationR = GameMasterM->stagePoint[GameMasterM->sPoint].rot.y - tmp.y;//戦闘時の角度との差を計算する
			rotationR *= 0.05;//1フレームごとに変化する角度を計算
			rotationCount = 0;

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
			player.speed = 0.0f;
			player.speedVec = Vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else if (2 == GameMasterM->waitFlag)	//目的地に到着したら、カメラを回転させる
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
					//
					Vec3 tmp1 = Vec3(HIDEPOINT_X, 0.0f, HIDEPOINT_Y);//原点に対する回避座標
					Vec2 tmp2;
					Vec3 rot = player.sprite3d->getRotation3D();
					tmp2.x = tmp1.x * cosf(rot.y) - tmp1.z * sinf(rot.y);
					tmp2.y = tmp1.x * sinf(rot.y) + tmp1.z * cosf(rot.y);
					//原点に対する回転後の座標が計算できたので、wrapperとsprite3dを移動させる
					tmp1.x = tmp2.x;
					tmp1.z = tmp2.y;
					player.wrapper->setPosition3D(player.wrapper->getPosition3D() + tmp1);
					player.sprite3d->setPosition3D(player.sprite3d->getPosition3D() - tmp1);
					player.cameraAjust = Vec3(0.0f, 0.0f, 0.0f);

				}
				else
				{
					Vec3 tmp1 = Vec3(-HIDEPOINT_X, 0.0f, HIDEPOINT_Y);//原点に対する回避座標
					Vec2 tmp2;
					Vec3 rot = player.sprite3d->getRotation3D();
					tmp2.x = tmp1.x * cosf(rot.y) - tmp1.z * sinf(rot.y);
					tmp2.y = tmp1.x * sinf(rot.y) + tmp1.z * cosf(rot.y);
					//原点に対する回転後の座標が計算できたので、wrapperとsprite3dを移動させる
					tmp1.x = tmp2.x;
					tmp1.z = tmp2.y;
					player.wrapper->setPosition3D(player.wrapper->getPosition3D() + tmp1);
					player.sprite3d->setPosition3D(player.sprite3d->getPosition3D() - tmp1);
					player.cameraAjust = Vec3(0.0f, 0.0f, 0.0f);
				}

				GameMasterM->SetGameState(GSTATE_PLAY_INIT);//戦闘ポイントに到着したら、ウェイトからプレイに移行

				//左右に応じたアイドルモーションを開始する
				player.sprite3d->stopAllActions();
				player.sprite3d->startAnimationLoop(idle);
			}
		}
	}
	else if(3 == GameMasterM->waitFlag)	//次の戦闘ポイントに到着したら、ウェイトからプレイに移行
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
		//タッチしていない
		if (0 == tmpFlag)
		{

		}
		else if (1 == tmpFlag)
		{
			//残弾に応じて処理を分ける
			if (0 >= GameMasterM->nowBullets)
			{
				//弾きれ
			}
			else
			{
				//アニメーションを再生
				GameMasterM->SetPlayerState(PSTATE_SHOT);
				player.sprite3d->stopAllActions();
				player.sprite3d->startAnimationLoop(shot);
				GameMasterM->rapidFrame = -1;//連射フレームを-1に初期化
				GameMasterM->flgPlayerATK = FALSE;
				GameMasterM->hideFrame = 0;
			}
		}
		else
		{
			GameMasterM->SetPlayerState(PSTATE_DODGE);//回避に移行
			player.InitFrame();//フレームをリフレッシュ
			GameMasterM->hideFrame = 0;

			player.sprite3d->stopAllActions();
			player.sprite3d->startAnimationReverse(h_shot);//回避モーションを再生
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

	GameMasterM->rapidFrame += 1;//連射フレームを加算する

	if(TSTATE_ON == GameMasterM->GetTouchState() || TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		//一定フレームごとに攻撃判定をONにする
		if(0 == (GameMasterM->rapidFrame % STS_RAPIDSPEED))
		{
			GameMasterM->flgPlayerATK = TRUE;
			//音声はフラグ成立時に鳴らす
			//sound->playSE("Shot.wav");
		}
		else
		{
			GameMasterM->flgPlayerATK = FALSE;
		}

		//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
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

	GameMasterM->hideFrame += 1;//回避フレームを加算する

	int flag = GameMasterM->GetTouchFlag();//現在のタッチ状態を取得

	//無敵時間の判定を行う
	if (STS_MUTEKISTART <= GameMasterM->hideFrame)//無敵開始フレームに達したら
	{
		GameMasterM->playerHitFlag = FALSE;//当たり判定を無効化する
	}

	//リロード判定を行う
	if (STS_RELOADSTART <= GameMasterM->hideFrame)//リロード開始フレームに達したら
	{
		GameMasterM->nowBullets = STS_MAXBULLETS;//弾数を回復する
	}

	if (STS_HIDEWAIT <= GameMasterM->hideFrame)//回避完了フレームに達したら
	{
		GameMasterM->SetPlayerState(PSTATE_HIDE);//隠れている状態に移行
		//リロードモーションの残りを再生するために、モーション終了は行わない
		player.sprite3d->stopAllActions();
//		player.sprite3d->startAnimation(idle);
	}

	//とりあえずTFLAG_CANCELをif内に入れておく
	if (TFLAG_RELEASE == flag || TFLAG_CANCEL == flag)//回避完了前にホールド解除した場合
	{
		player.sprite3d->stopALLAnimation();//モーション終了
		GameMasterM->SetPlayerState(PSTATE_APPEAR);//隠れている状態に移行
		//突撃モーションを再生
		GameMasterM->hideFrame = STS_HIDEWAIT - GameMasterM->hideFrame;//突撃のフレーム数をセットする
	}
	else if (TFLAG_ON == flag || TFLAG_MOVE == flag)//ホールド状態
	{
		//回避動作中は指定座標を軸に座標移動を行う
		//回避フレーム（12フレーム）を12分割し、90度程度回転する
		if (PSIDE_LEFT == GameMasterM->playerSide)
		{
			//
			float rot = 96.0f / STS_HIDEWAIT;
			Vec3 tmp = player.wrapper->getRotation3D();
			tmp.y -= rot;
			player.wrapper->setRotation3D(tmp);
			tmp = player.sprite3d->getRotation3D();
			tmp.y += rot;
			player.sprite3d->setRotation3D(tmp);
			//回避に合わせてカメラの座標を補正する
			player.cameraAjust = Vec3((HIDEPOINT_X * 2.5f) * GameMasterM->hideFrame / STS_HIDEWAIT, 0.0f, -(HIDEPOINT_Y * 1) * GameMasterM->hideFrame / STS_HIDEWAIT);
			Vec3 cameraRot = player.wrapper->getRotation3D() + player.sprite3d->getRotation3D() + Vec3(0.0f, 0.0f, 0.0f);//進行方向の角度
			Vec2 tmp2;
			tmp2.x = player.cameraAjust.x * cosf(-cameraRot.y) - player.cameraAjust.z * sinf(-cameraRot.y);
			tmp2.y = player.cameraAjust.x * sinf(-cameraRot.y) + player.cameraAjust.z * cosf(-cameraRot.y);
			player.cameraAjust.x = tmp2.x;
			player.cameraAjust.z = tmp2.y;
		}
		else
		{
			float rot = 96.0f / STS_HIDEWAIT;
			Vec3 tmp = player.wrapper->getRotation3D();
			tmp.y += rot;
			player.wrapper->setRotation3D(tmp);
			tmp = player.sprite3d->getRotation3D();
			tmp.y -= rot;
			player.sprite3d->setRotation3D(tmp);
			//回避に合わせてカメラの座標を補正する
			player.cameraAjust = Vec3(-HIDEPOINT_X, 0.0f, 0.0f);
		}
	}
	else
	{

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

	if(TSTATE_ON == GameMasterM->GetTouchState() || TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		//タッチ中はリロードを再生、再生後はモーション停止


	}
	else if(TSTATE_RELEASE == GameMasterM->GetTouchState())//離されれば
	{
		GameMasterM->SetPlayerState(PSTATE_APPEAR);
		player.sprite3d->startAnimation(h_shot);
		GameMasterM->hideFrame = 0;
		player.InitFrame();//フレームをリフレッシュ
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

	GameMasterM->hideFrame += 1;//回避フレームを加算する

	//無敵時間の判定を行う
	if (STS_MUTEKISTART <= GameMasterM->hideFrame)//無敵終了フレームに達したら
	{
		GameMasterM->playerHitFlag = TRUE;//当たり判定を有効化する
	}

	//回避完了の判定
	if (STS_HIDEWAIT <= GameMasterM->hideFrame)//回避完了フレームに達したら
	{
		//必要ならばモーションの停止を行う
		GameMasterM->SetPlayerState(PSTATE_IDLE);//アイドル状態に移行
		player.sprite3d->stopAllActions();
//		player.sprite3d->startAnimation(idle);
	}

	if (PSIDE_LEFT == GameMasterM->playerSide)
	{
		//
		float rot = 96.0f / STS_HIDEWAIT;
		Vec3 tmp = player.wrapper->getRotation3D();
		tmp.y += rot;
		player.wrapper->setRotation3D(tmp);
		tmp = player.sprite3d->getRotation3D();
		tmp.y -= rot;
		player.sprite3d->setRotation3D(tmp);

		//回避に合わせてカメラの座標を補正する
		player.cameraAjust = Vec3((HIDEPOINT_X * 2.5f) * (STS_HIDEWAIT - GameMasterM->hideFrame) / STS_HIDEWAIT, 0.0f, -(HIDEPOINT_Y * 1) * (STS_HIDEWAIT - GameMasterM->hideFrame) / STS_HIDEWAIT);
		Vec3 cameraRot = player.wrapper->getRotation3D() + player.sprite3d->getRotation3D() + Vec3(0.0f, 0.0f, 0.0f);//進行方向の角度
		Vec2 tmp2;
		tmp2.x = player.cameraAjust.x * cosf(-cameraRot.y) - player.cameraAjust.z * sinf(-cameraRot.y);
		tmp2.y = player.cameraAjust.x * sinf(-cameraRot.y) + player.cameraAjust.z * cosf(-cameraRot.y);
		player.cameraAjust.x = tmp2.x;
		player.cameraAjust.z = tmp2.y;
	}
	else
	{
		float rot = 96.0f / STS_HIDEWAIT;
		Vec3 tmp = player.wrapper->getRotation3D();
		tmp.y -= rot;
		player.wrapper->setRotation3D(tmp);
		tmp = player.sprite3d->getRotation3D();
		tmp.y += rot;
		player.sprite3d->setRotation3D(tmp);
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
void GameModelsLayer:: ActionDamaged(void)
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
void GameModelsLayer:: ActionRun(void)
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
void GameModelsLayer:: ActionDead(void)
{
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
	for(int i = 0; i < MAX_UNIT; i++)
	{
		if(-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind)
		{

			unit[i].Update();//フレーム・座標・当たり判定の更新
			if(unit[i].hitpoint <= 0)
			{
				unit[i].eState = ESTATE_DAMAGED;
			}

			switch(unit[i].eState)
			{
			case ESTATE_STANDBY:

				unit[i].eWaitFrame--;//待機時間を減らしていく
				if(unit[i].eWaitFrame <= 0)
				{
					unit[i].eState = ESTATE_MOVE;//待機が終わったら移動

					unit[i].speed = 0.03f;//スピードは後で調整する

					unit[i].speedVec = unit[i].targetPos - unit[i].sprite3d->getPosition3D();//この方法が正しければ使用する
					
					

					//ベクトルの正規化を行う
					unit[i].speedVec.normalize();

					double r = atan2(unit[i].speedVec.y, unit[i].speedVec.y);
					r = CC_DEGREES_TO_RADIANS(r);

					//正規化が終わったら、速度をかけて方向ベクトルの計算終了
					unit[i].speedVec.x *= unit[i].speed;
					unit[i].speedVec.z *= unit[i].speed;


					unit[i].speedVec.y = 0;//yは今のところ0で扱う
					unit[i].sprite3d->startAnimationLoop("stop");
					unit[i].atkFrame = 50;
					unit[i].sprite3d->setRotation3D(Vec3(0.0f, r + 180.0f, 0.0f));
				}

				break;
			case ESTATE_IDLE://アイドル状態

				unit[i].atkFrame--;
				unit[i].sprite3d->stopALLAnimation();
				if(unit[i].atkFrame <= 0)
				{
//					unit[i].eState = ESTATE_ATTACK1;
//					unit[i].sprite3d->startAnimationLoop("rshot");
				
				unit[i].eState = ESTATE_ATTACK1;
				unit[i].sprite3d->startAnimationLoop("rshot");
				}
				break;
			case ESTATE_MOVE://移動状態
			{
								 Vec3 tmpPos = unit[i].sprite3d->getPosition3D();

								 //一定以上目的地に近付いたら
								 if(0.01f >= sqrtf(unit[i].targetPos.x - tmpPos.x) * (unit[i].targetPos.x - tmpPos.x)
									 + (unit[i].targetPos.y - tmpPos.y) *(unit[i].targetPos.y - tmpPos.y))
								 {
									 //プレイヤーと反対方向を向く
									 Vec3 rot = player.sprite3d->getRotation3D();
									 rot.y -= 180.0f;

									 unit[i].sprite3d->setPosition3D(unit[i].targetPos);
									 unit[i].sprite3d->setRotation3D(rot);

									 unit[i].sprite3d->stopALLAnimation();

									 unit[i].speed = 0.0f;
									 unit[i].speedVec = Vec3(0.0f, 0.0f, 0.0f);


									 unit[i].eState = ESTATE_IDLE;
									 unit[i].atkFrame = 5;
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

//				unit[i].sprite3d->stopALLAnimation();
//				unit[i].sprite3d->startAnimation("dei2");
//				unit[i].eState = ESTATE_DEAD;
//				unit[i].eWaitFrame = 180;
					
					
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
	
				unit[i].eState = ESTATE_STANDBY;
				unit[i].hitpoint = 5;
				//個別
				unit[i].sprite3d->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
				unit[i].targetPos = Vec3(15.0f, 0.0f, 5.5f);
				unit[i].eWaitFrame = 0;
				unit[i].atkFrame = 20;
				
				ShootBullet(i);

				unit[i].eState = ESTATE_STANDBY;
				
//				unit[i].sprite3d->setVisible( false);
				break;
			case ESTATE_DEAD://死亡
				unit[i].eState = ESTATE_DEAD;
				if(unit[i].sprite3d->checkAnimationState() == 0)
				{
					unit[i].eWaitFrame--;
					if(unit[i].eWaitFrame <= 0)
					{
						//リスポーンさせる

					}
				}
				break;
			}
		}
	}
}





/*

*/
void GameModelsLayer::ShootBullet(int enemy_num)
{
	int num = SearchFreeUnit();
	if(FALSE != num)
	{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string fileName1 = "tama";
#else
		std::string fileName1 = "Bullet/bullet";
#endif
		unit[num].sprite3d = _Sprite3D::create(fileName1);

		unit[num].Init(num, UKIND_EBULLET);

		unit[num].wrapper = Node::create();//モデルの親ノード
		addChild(unit[num].sprite3d);
//		unit[num].wrapper->addChild(unit[num].sprite3d);
//		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(1.0f);

		////当たり判定の定義（仮）
		unit[num].collisionPos = Vec3(0.3, 0.4, 0.3);//当たり判定矩形の大きさを設定
		unit[num].SetCollision();//当たり判定をセット

		//弾を撃ったエネミーの座標と、プレイヤーの座標を元に、弾の移動方向を求める
		Vec3 enemyPos = unit[enemy_num].sprite3d->getPosition3D();
		Vec3 playerPos = player.sprite3d->getPosition3D();

		unit[num].speedVec = playerPos - enemyPos;//この方法が正しければ使用する

		//ベクトルの正規化を行う
		unit[num].speedVec.normalize();

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		unit[num].speed = 0.0f;
		unit[num].speedVec.x *= unit[num].speed;
		unit[num].speedVec.z *= unit[num].speed;
		unit[num].speedVec.y = 0;//yは今のところ0で扱う

		unit[num].sprite3d->setPosition3D(enemyPos);
		unit[num].sprite3d->setPositionY(1.2f);
	}
}


/*

*/
void GameModelsLayer::UpdateBullets()
{
	//全ての敵弾ユニットを更新
	for(int num = 0; num < MAX_UNIT; num++)
	{
		if(FALSE != unit[num].valid && UKIND_EBULLET == unit[num].kind)
		{
			unit[num].Update();//座標と一緒に当たり判定を移動

			//unit[num].Init();//メンバ変数の初期化をしておく
			unit[num].Init(num, UKIND_ENEMY);

			unit[num].eState = ESTATE_STANDBY;
			unit[num].hitpoint = 5;
			//個別
			unit[num].sprite3d->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
			unit[num].targetPos = Vec3(15.0f, 0.0f, 5.5f);
			unit[num].eWaitFrame = 20;
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
	const int count = player.GetFrame();

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

		Vec3 cPos = Vec3(pos.x, tmpPos.y,pos.y);//yは
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
		for(int i = 0; i < MAX_UNIT; i++)
		{
			if(-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind && unit[i].eState != ESTATE_DAMAGED && unit[i].eState != ESTATE_DEAD)
			{
				if(touchRay.intersects(unit[i].obbHead))//タッチ座標の法線と敵の当たり判定が接触したかをチェック
				{
					Vec3 rot = Vec3(0, 0, 0);
					rot = unit[i].sprite3d->getRotation3D();
					rot.y += 20.0f;
					//unit[i].sprite3d->setRotation3D(rot);
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

	//全ての敵弾ユニットを更新
	for(int i = 0; i < MAX_UNIT; i++)
	{
		if(FALSE != unit[i].valid && UKIND_EBULLET == unit[i].kind)
		{
			//プレイヤーとの当たり判定を処理
			if(player.obbHead.intersects(unit[i].obbHead))
			{
				//接触した場合は_sprite3Dの解放を行う
				unit[i].sprite3d->setVisible(false);
			}
		}
	}
}


int GameModelsLayer::SearchFreeUnit()
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (FALSE == unit[i].valid)
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


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
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitLayer(void)
{
	InitAllModels();

	InitPlayer(0);//とりあえず引数0
	InitMap(0);//正規のマップデータが降りてくるまでいったん保留します
	InitEnemy(0);

	return 0;
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
*	@return	正常:Unit配列のプレイヤー番号 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitPlayer(int stage_num)
{
	int num = SearchFreeUnit();
	if(FALSE == num)
	{
		return FALSE;
	}
	unit[num].Init();//メンバ変数の初期化をしておく

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fileName1 = "player";
	std::string fileName2 = "Player.anime";
	unit[num].sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);
#else
	std::string fileName1 = "Player/player";
	std::string fileName2 = "Player.anime";
	unit[num].sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2);
#endif

	unit[num].Init(num, UKIND_PLAYER1);//プレイヤーの情報を初期化

	//プレイヤー固有の初期化（今後場所を変更する）
	GameMasterM->playerHitFlag = TRUE;//
	playerNum = num;
	unit[num].wrapper = Node::create();//モデルの親ノード
	unit[num].wrapper->addChild(unit[num].sprite3d);//親ノードにスプライトを紐付け
	addChild(unit[num].wrapper);//親ノードをレイヤーに紐付け

	//ステージに応じた初期化

	unit[num].sprite3d->setScale(1.0f);
	unit[num].sprite3d->setRotation3D(GameMasterM->stagePoint[POINT_START].rot);//プレイヤーは正面を向く
	unit[num].sprite3d->setPosition3D(GameMasterM->stagePoint[POINT_START].pos);
	GameMasterM->sPoint = POINT_STAGE1;//ステージ1に走る

	//当たり判定の定義（仮）
	unit[num].collisionPos = Vec3(1.2, 3.0, 1.2);//範囲を指定して
	unit[num].SetCollision();

	return num;
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

		//一時的な配列
		for (int i = 0; i < 80; i++)
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
			unit[num].sprite3d->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
			unit[num].targetPos = Vec3(15.0f + i * 0.28f, 0.0f, 5.5f + +i * 0.1f);
			unit[num].eWaitFrame = 20;


		}
		for(int i = 3; i < 50; i++)
		{
			num = SearchFreeUnit();
			if(-1 == num)
			{
				continue;
			}

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
#else
	std::string fileName1 = "Stage/StageVer5";
#endif
	unit[num].sprite3d = _Sprite3D::create(fileName1);

	addChild(unit[num].sprite3d);

	unit[num].sprite3d->setScale(1.0f);
	unit[num].sprite3d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[num].sprite3d->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[num].Init(num, UKIND_MAP);
	return TRUE;
}



void GameModelsLayer::UpdateModels()
{
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
	//unit[playerNum].sprite3d->setRotation3D(Vec3(0.0f, rot, 0.0f));
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
	if(0 == GameMasterM->waitFlag)	//次の目的地を検索
	{
		unit[playerNum].targetPos = GameMasterM->stagePoint[GameMasterM->sPoint].pos;//
		unit[playerNum].speed = 0.05f;//スピードは後で調整する

		unit[playerNum].speedVec = unit[playerNum].targetPos - unit[playerNum].sprite3d->getPosition3D();//この方法が正しければ使用する

		//ベクトルの正規化を行う
		unit[playerNum].speedVec.normalize();

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		unit[playerNum].speedVec.x *= unit[playerNum].speed;
		unit[playerNum].speedVec.z *= unit[playerNum].speed;

		unit[playerNum].speedVec.y = 0;//yは今のところ0で扱う
		unit[playerNum].sprite3d->startAnimationLoop("run");
		GameMasterM->waitFlag = 1;
	}
	else if(1 == GameMasterM->waitFlag)	//次の目的地まで走る処理
	{
		UpdatePlayer();//プレイヤーの更新
		Vec3 tmpPos = unit[playerNum].sprite3d->getPosition3D();

		//一定以上目的地に近付いたら
		if(0.2f * 0.2f >= (unit[playerNum].targetPos.x - tmpPos.x) * (unit[playerNum].targetPos.x - tmpPos.x)
			+ (unit[playerNum].targetPos.y - tmpPos.y) *(unit[playerNum].targetPos.y - tmpPos.y))
		{
			GameMasterM->waitFlag = 2;
			Vec3 tmp = unit[playerNum].sprite3d->getRotation3D();
			rotationR = GameMasterM->stagePoint[GameMasterM->sPoint].rot.y - tmp.y;
			rotationR *= 0.05;
			rotationCount = 0;

			unit[playerNum].speed = 0.0f;
			unit[playerNum].speedVec = Vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else if(2 == GameMasterM->waitFlag)	//目的地に到着したら、カメラを回転させる
	{
		if(rotationCount >= 20)
		{

			if(POINT_CHANGE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//進行方向切り替え
			{
				unit[playerNum].sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot);
				unit[playerNum].sprite3d->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pos);

				GameMasterM->sPoint++;//座標と角度が設定できたらポイントを先に進める
				GameMasterM->waitFlag = 0;

			}
			else if(POINT_BATTLE == GameMasterM->stagePoint[GameMasterM->sPoint].pointType)//次のウェーブに到達した
			{
				//ステージポイントを進める
				unit[playerNum].sprite3d->setRotation3D(GameMasterM->stagePoint[GameMasterM->sPoint].rot);
				unit[playerNum].sprite3d->setPosition3D(GameMasterM->stagePoint[GameMasterM->sPoint].pos);

//				InitEnemy(0);//ここで敵の配置をすると座標で不具合が発生します

				GameMasterM->SetGameState(GSTATE_PLAY_INIT);//次の戦闘ポイントに到着したら、ウェイトからプレイに移行

				unit[playerNum].sprite3d->stopAllActions();
			}
		}
		else
		{
			Vec3 tmp = unit[playerNum].sprite3d->getRotation3D();
			unit[playerNum].sprite3d->setRotation3D(tmp + Vec3(0, rotationR, 0));
			rotationCount++;
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
	unit[playerNum].Update();

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
		else
		{
			//攻撃可能範囲をタッチしていれば
			if (tPos.x < s.width * BATTLE_FEILD_X)
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
		//タッチしていない
		if (0 == tmpFlag)
		{

		}
		else if (1 == tmpFlag)
		{
			//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
			GameMasterM->SetPlayerState(PSTATE_SHOT);

			//アニメーションを再生
			unit[playerNum].sprite3d->startAnimationLoop("shot_new");

			//回避フレームを初期化する
			GameMasterM->hideFrame = 0;
		}
		else
		{
			GameMasterM->SetPlayerState(PSTATE_DODGE);//回避に移行
			unit[playerNum].InitFrame();//フレームをリフレッシュ
			unit[playerNum].sprite3d->startAnimationReverse("hideshot_ln");
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
	auto sound = Sound::getInstance();
	if (TSTATE_ON == GameMasterM->GetTouchState())
	{
		auto s = Director::getInstance()->getWinSize();//画面サイズ取得
		Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得

		//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
		GameMasterM->SetPlayerState(PSTATE_SHOT);//ステート状態はそのまま

		//アニメーションは継続して再生
		sound->playSE("Shot.wav");
	}
	else if (TSTATE_MOVE == GameMasterM->GetTouchState())
	{
		auto s = Director::getInstance()->getWinSize();//画面サイズ取得
		Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得

		//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
		GameMasterM->SetPlayerState(PSTATE_SHOT);//ステート状態はそのまま

		//アニメーションは継続して再生
	}
	else if (TSTATE_RELEASE == GameMasterM->GetTouchState())//タッチを離したら
	{
		GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
		unit[playerNum].InitFrame();//フレームをリフレッシュ
		unit[playerNum].sprite3d->stopAllActions();

		unit[playerNum].sprite3d->startAnimation("shot");
	}
	else
	{
		GameMasterM->SetPlayerState(PSTATE_IDLE);
		unit[playerNum].InitFrame();//フレームをリフレッシュ
		unit[playerNum].sprite3d->stopAllActions();

		//アニメーションを再生
		unit[playerNum].sprite3d->startAnimation("shot");
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
	//１：ボタンホールド状態でモーションが終了するとActionHideに移行する
	//２：ボタンホールド状態が解除されればActionAppearに移行する
	//３：ボタンホールド継続状態であれば、モーションを継続する・・・（ボタンON,ボタンMOVE）

	GameMasterM->hideFrame += 1;//回避フレームを加算する

	int flag = GameMasterM->GetTouchFlag();//現在のタッチ状態を取得

	//無敵時間の判定を行う
	if (STS_MUTEKISTART == GameMasterM->hideFrame)//無敵開始フレームに達したら
	{
		GameMasterM->playerHitFlag = FALSE;//当たり判定を無効化する
	}

	//リロード判定を行う
	if (STS_RELOADSTART == GameMasterM->hideFrame)//リロード開始フレームに達したら
	{
		GameMasterM->nowBullets = STS_MAXBULLETS;//弾数を回復する
	}

	if (STS_HIDEWAIT == GameMasterM->hideFrame)//回避完了フレームに達したら
	{
		GameMasterM->SetPlayerState(PSTATE_HIDE);//隠れている状態に移行
		//リロードモーションの残りを再生するために、モーション終了は行わない
	}

	//とりあえずTFLAG_CANCELをif内に入れておく
	if (TFLAG_RELEASE == flag || TFLAG_CANCEL == flag)//回避完了前にホールド解除した場合
	{
		unit[playerNum].sprite3d->stopALLAnimation();//モーション終了
		GameMasterM->SetPlayerState(PSTATE_APPEAR);//隠れている状態に移行
		//突撃モーションを再生
		GameMasterM->hideFrame = STS_HIDEWAIT - GameMasterM->hideFrame;//突撃のフレーム数をセットする
	}
	else if (TFLAG_ON == flag || TFLAG_MOVE == flag)//ホールド状態
	{
		//
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
	if (TSTATE_ON == GameMasterM->GetTouchState())//タッチされたら
	{
		{
			auto s = Director::getInstance()->getWinSize();//画面サイズ取得
			Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得
			if (tPos.x > s.width * 0.5f)//攻撃可能範囲をタッチしていれば
			{
				//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
				GameMasterM->SetPlayerState(PSTATE_APPEAR);
				unit[playerNum].sprite3d->startAnimation("hideshot_ln");
				unit[playerNum].InitFrame();//フレームをリフレッシュ
			}
			else//それ以外は今のところ同じ
			{
				//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
				GameMasterM->SetPlayerState(PSTATE_APPEAR);
				unit[playerNum].sprite3d->startAnimation("hideshot_ln");
				unit[playerNum].InitFrame();//フレームをリフレッシュ
			}
		}
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
	//１：突撃終了フレームが終了するとActionIdleに移行する

	int flag = GameMasterM->GetTouchFlag();//現在のタッチ状態を取得

	GameMasterM->hideFrame += 1;//回避フレームを加算する

	//無敵時間の判定を行う
	if (STS_MUTEKISTART >= GameMasterM->hideFrame)//無敵終了フレームに達したら
	{
		GameMasterM->playerHitFlag = TRUE;//当たり判定を有効化する
	}

	//回避完了の判定
	if (STS_HIDEWAIT >= GameMasterM->hideFrame)//回避完了フレームに達したら
	{
		//必要ならばモーションの停止を行う
		GameMasterM->SetPlayerState(PSTATE_IDLE);//アイドル状態に移行
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
	//
	//if ()
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
									 Vec3 rot = unit[playerNum].sprite3d->getRotation3D();
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
					
					
				
				if( random == 0)
				{
					sound -> playSE("Damage_01.wav");
				}
				else if( random == 1)
				{
					sound -> playSE("Damage_02.wav");
				}
				else if( random == 2)
				{
					sound -> playSE("Damage_03.wav");
				}
				else if( random == 3)
				{
					sound -> playSE("Damage_04.wav");
				}
					
				//共通
	
				unit[i].eState = ESTATE_STANDBY;
				unit[i].hitpoint = 5;
				//個別
				unit[i].sprite3d->setPosition3D(Vec3(14.4f, 0.0f, 7.8f));
				unit[i].targetPos = Vec3(15.0f, 0.0f, 5.5f);
				unit[i].eWaitFrame = 0;
				unit[i].atkFrame = 20;
				
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
		std::string fileName2 = "tama.png";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);
#else
		std::string fileName1 = "enemy/enemy";
		std::string fileName2 = "tama_new.png";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);
#endif
		unit[num].Init(num, UKIND_EBULLET);

		unit[num].wrapper = Node::create();//モデルの親ノード
		addChild(unit[num].sprite3d);
//		unit[num].wrapper->addChild(unit[num].sprite3d);
//		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setScale(1.3f);

		////当たり判定の定義（仮）
		unit[num].collisionPos = Vec3(0.3, 0.4, 0.3);//当たり判定矩形の大きさを設定
		unit[num].SetCollision();//当たり判定をセット

		//弾を撃ったエネミーの座標と、プレイヤーの座標を元に、弾の移動方向を求める
		Vec3 enemyPos = unit[enemy_num].sprite3d->getPosition3D();
		Vec3 playerPos = unit[playerNum].sprite3d->getPosition3D();

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
	if(pstate == PSTATE_SHOT)
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
			if(unit[playerNum].obbHead.intersects(unit[i].obbHead))
			{
				//接触した場合は_sprite3Dの解放を行う
				unit[i].sprite3d->setVisible(false);
			}
		}
	}
}


int GameModelsLayer::GetPlayerNum()
{
	return playerNum;
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

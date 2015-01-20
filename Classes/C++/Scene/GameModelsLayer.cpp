
#include "GameModelsLayer.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameMaster.h"
#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"
#include "C++/Base/GameMaster.h"

#endif


USING_NS_CC;
using namespace TapGun;

GameMaster* GameMasterM;//変数名は今後考慮する


/*-*/
//Animate3D* animateShot;
//Animation3D* animationShot;
//Animate3D* animateHiding;
//Animation3D* animationHiding;

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

	playerNum = -1;
	playerNum = InitPlayer(0);//とりあえず引数0
//	InitMap(0);//正規のマップデータが降りてくるまでいったん保留します
	InitEnemy(0);

	return playerNum;
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
	std::string fileName3 = "enemy/tex_boy.png";
	unit[num].sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2, fileName3);
#else
	std::string fileName1 = "player/player";
	std::string fileName2 = "Player.anime";
	std::string fileName3 = "enemy/tex_boy.png";
	unit[num].sprite3d = TapGun::_Sprite3D::create(fileName1, fileName2, fileName3);
#endif


	unit[num].Init(num, UKIND_PLAYER1);
	playerNum = num;
	unit[num].wrapper = Node::create();//モデルの親ノード
	unit[num].wrapper->addChild(unit[num].sprite3d);//親ノードにスプライトを紐付け
	addChild(unit[num].wrapper);//親ノードをレイヤーに紐付け

	//ステージに応じた初期化
	switch(stage_num)
	{
	case 0:

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 180.0f, 0.0f));//プレイヤーは反対を向く
		unit[num].sprite3d->setPosition3D(Vec3(2.0f, 0.0f, -8.5f));

		break;

	default:
		return FALSE;
		break;
	}

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

	int num = -1;
	switch(stage_num)
	{
	case 0:
		//テストエネミーの読み込み：１
		num = SearchFreeUnit();
		if(-1 == num)
		{
			return false;
		}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string fileName1 = "enemy";
		std::string fileName2 = "Enemy.anime";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);

#else
		std::string fileName1 = "enemy/enemy";
		std::string fileName2 = "Enemy.anime";
		std::string fileName3 = "enemy/tex_boy.png";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2, fileName3);
#endif

		unit[num].Init(num, UKIND_ENEMY);

		unit[num].wrapper = Node::create();//モデルの親ノード
		unit[num].wrapper->addChild(unit[num].sprite3d);
		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setPosition3D(Vec3(4.0f, 0.0f, -18.5f));


		//当たり判定の定義（仮）
		unit[num].collisionPos = Vec3(0.8, 1.4, 0.8);
		unit[num].SetCollision();


		/*-*/
		unit[num].InitFrame();//フレームをクリア
		int r = rand() % 40 - 40;//とりあえず
		unit[num].SetFrame(r);//フレームをクリア


		//テストエネミーの読み込み：２

		num = SearchFreeUnit();
		if(-1 == num)
		{
			return false;
		}
		unit[num].Init();//メンバ変数の初期化をしておく

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		fileName1 = "enemy";
		fileName2 = "Enemy.anime";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);

#else
		fileName1 = "enemy/enemy";
		fileName2 = "Enemy.anime";
		fileName3 = "enemy/tex_boy.png";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2, fileName3);
#endif
		unit[num].Init(num, UKIND_ENEMY);

		unit[num].wrapper = Node::create();//モデルの親ノード
		unit[num].wrapper->addChild(unit[num].sprite3d);
		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setPosition3D(Vec3(3.0f, 0.0f, -60.5f));


		//当たり判定の定義（仮）
		unit[num].collisionPos = Vec3(0.8, 1.4, 0.8);
		unit[num].SetCollision();


		/*-*/
		unit[num].InitFrame();//フレームをクリア
		r = rand() % 40 - 40;//とりあえず
		unit[num].SetFrame(r);//フレームをクリア


		break;
	defalut:
		break;
	}

	return TRUE;
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
	std::string fileName1 = "map";
	std::string fileName2 = "stage_tex.png";
#else
	std::string fileName1 = "map";
	std::string fileName2 = "stage_tex.png";
#endif

	unit[num].sprite3d = _Sprite3D::create(fileName1,fileName2);

	unit[num].Init(num, UKIND_MAP);

	unit[num].wrapper = Node::create();//モデルの親ノード
	unit[num].wrapper->addChild(unit[num].sprite3d);
	addChild(unit[num].wrapper);


	unit[num].sprite3d->setScale(1.0f);
	unit[num].sprite3d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[num].sprite3d->setPosition3D(Vec3(0.0f, -5.5f, 0.0f));

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

		if (TSTATE_ON == GameMasterM->GetTouchState())//タッチされたら
		{
			{
				auto s = Director::getInstance()->getWinSize();//画面サイズ取得
				Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得
				if (tPos.x > s.width * 0.4f)//攻撃可能範囲をタッチしていれば
				{
					//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
					GameMasterM->SetPlayerState(PSTATE_SHOT);

					//アニメーションを再生
					unit[playerNum].sprite3d->startAnimationLoop("shot");//攻撃アニメーションを開始
				}
				else//それ以外は今のところ回避
				{
					GameMasterM->SetPlayerState(PSTATE_HIDING);//回避に移行
					unit[playerNum].InitFrame();//フレームをリフレッシュ

					//アニメーション読み込み
					unit[playerNum].sprite3d->startAnimationReverse("hideshot_l");
				}
			}
		}
		break;
	case PSTATE_SHOT:

		//
		if (TSTATE_ON == GameMasterM->GetTouchState())
		{
			{
				auto s = Director::getInstance()->getWinSize();//画面サイズ取得
				Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得

				//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
				GameMasterM->SetPlayerState(PSTATE_SHOT);//ステート状態はそのまま

				//アニメーションは継続して再生
			}
		}
		else if (TSTATE_MOVE == GameMasterM->GetTouchState())
		{
			{
				auto s = Director::getInstance()->getWinSize();//画面サイズ取得
				Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得

				//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
				GameMasterM->SetPlayerState(PSTATE_SHOT);//ステート状態はそのまま

				//アニメーションは継続して再生

			}
		}
		else if (TSTATE_RELEASE == GameMasterM->GetTouchState())//タッチを離したら
		{
			GameMasterM->SetPlayerState(PSTATE_IDLE);//通常状態に戻す
			unit[playerNum].InitFrame();//フレームをリフレッシュ
			unit[playerNum].sprite3d->stopAllActions();

			//アニメーションを再生
//			unit[playerNum].sprite3d->runAction(animateShot);

		}
		else
		{
			GameMasterM->SetPlayerState(PSTATE_IDLE);
			unit[playerNum].InitFrame();//フレームをリフレッシュ
			unit[playerNum].sprite3d->stopAllActions();

			//アニメーションを再生
//			std::string fileName1 = "Graph/Models/mot_player_shot.c3t";
		}

		break;
	case PSTATE_HIDING://隠れ中
		//キャラクター固有フレームが一定以上になったら状態遷移
		if (10 <= unit[playerNum].GetFrame())
		{
			GameMasterM->SetPlayerState(PSTATE_HIDE);//隠れている状態に移行
			unit[playerNum].InitFrame();//フレームをリフレッシュ

		}

		break;
	case PSTATE_HIDE://隠れている

		if (TSTATE_ON == GameMasterM->GetTouchState())//タッチされたら
		{
			{
				auto s = Director::getInstance()->getWinSize();//画面サイズ取得
				Vec2 tPos = GameMasterM->GetTouchPos();//タッチしたスクリーン座標を取得
				if (tPos.x > s.width * 0.5f)//攻撃可能範囲をタッチしていれば
				{
					//座標とフレーム数をさらに取得して、その数値に応じて攻撃処理
					GameMasterM->SetPlayerState(PSTATE_SHOT);
					unit[playerNum].InitFrame();//フレームをリフレッシュ

					//アニメーション読み込み
//					unit[playerNum].sprite3d->runAction(animateAppearShot);

				}
				else//それ以外は今のところなし
				{
					//GameMasterM->SetPlayerState(PSTATE_APPEAR);//回避に移行
					//unit[playerNum].InitFrame();//フレームをリフレッシュ
				}
			}
		}


		break;
	case PSTATE_APPEAR://隠れた状態から出る

		//キャラクター固有フレームが一定以上になったら状態遷移
		if (10 <= unit[playerNum].GetFrame())
		{
			GameMasterM->SetPlayerState(PSTATE_IDLE);//とりあえずアイドル状態に移行
			unit[playerNum].InitFrame();//フレームをリフレッシュ

		}
		break;

	case PSTATE_APPEARSHOT://隠れた状態から攻撃

		//キャラクター固有フレームが一定以上になったら状態遷移
		if (10 <= unit[playerNum].GetFrame())
		{
			GameMasterM->SetPlayerState(PSTATE_SHOT);//とりあえずアイドル状態に移行
			unit[playerNum].InitFrame();//フレームをリフレッシュ

			//アニメーションを再生
//			animateShot->setSpeed(1);
		}
		break;//隠れた状態から出る
	case PSTATE_DAMAGED:
		break;
	case PSTATE_RUN:
		break;
	case PSTATE_DEAD:
		break;
	}
	//プレイヤーが攻撃可能な場合、攻撃範囲の座標をタッチしたら攻撃を行う
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
	for(int i = 0; i < MAX_UNIT; i++)
	{
		if(-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind)
		{
			unit[i].Update();//フレーム・座標・当たり判定の更新
			if(300 <= unit[i].GetFrame())
			{

				//アニメーション読み込み
				unit[i].sprite3d->startAnimation("dei1");

				ShootBullet(i);//i番のエネミーが弾を発射する
				unit[i].InitFrame();//フレームをクリア
				int r = rand() % 40 - 40;//とりあえず
				unit[i].SetFrame(r);

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
		std::string fileName1 = "tama_new";
		std::string fileName2 = "tama_new.png";
		unit[num].sprite3d = _Sprite3D::create(fileName1, fileName2);
#endif
		unit[num].Init(num, UKIND_EBULLET);

		unit[num].wrapper = Node::create();//モデルの親ノード
		unit[num].wrapper->addChild(unit[num].sprite3d);
		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(0.5f);

		////当たり判定の定義（仮）
		unit[num].collisionPos = Vec3(0.3, 0.4, 0.3);//当たり判定矩形の大きさを設定
		unit[num].SetCollision();//当たり判定をセット

		//弾を撃ったエネミーの座標と、プレイヤーの座標を元に、弾の移動方向を求める
		Vec3 enemy_pos = unit[enemy_num].sprite3d->getPosition3D();
		Vec3 player_pos = unit[playerNum].sprite3d->getPosition3D();

		//unit[num].speed_vec = Vec3(enemy_pos.x, 0, 0);
		unit[num].speedVec = player_pos - enemy_pos;//この方法が正しければ使用する

		//ベクトルの正規化を行う
		float vx = unit[num].speedVec.x;
		float vz = unit[num].speedVec.z;

		float dist = sqrtf(vx * vx + vz * vz);//二次元的な距離
		vx = vx / dist;
		vz = vz / dist;

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		unit[num].speed = 0.8f;
		unit[num].speedVec.x = vx * unit[num].speed;
		unit[num].speedVec.z = vz * unit[num].speed;
		unit[num].speedVec.y = 0;//yは今のところ0で扱う

		unit[num].sprite3d->setPosition3D(enemy_pos);
		unit[num].sprite3d->setPositionY(1.2f);
	}
}


/*

*/
void GameModelsLayer::UpdateBullets()
{
	//全ての敵弾ユニットを更新
	for(int i = 0; i < MAX_UNIT; i++)
	{
		if(FALSE != unit[i].valid && UKIND_EBULLET == unit[i].kind)
		{
			unit[i].Update();//座標と一緒に当たり判定を移動
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
		//Vec2 gliv = pTouch->getLocationInView();
		Vec2 tPos = GameMasterM->GetTouchPosInView();//タッチ座標を取得

		Vec3 rayStart = Vec3(0, 0, 0);//レイの始点
		Vec3 rayEnd = Vec3(0, 0, 0);//レイの終点

		Vec3 tmpPosNear = Vec3(tPos.x, tPos.y, -1.0f);//-1.0f == 視錘台の近面（near plane）
		Vec3 tmpPosFar = Vec3(tPos.x, tPos.y, 1.0f);//1.0f == 視錘台の遠面（far plane）

		Camera* cam3d = GameMasterM->GetCamera3D();
		cam3d->unproject(s, &tmpPosNear, &rayStart);//near planeの3次元座標を取得
		cam3d->unproject(s, &tmpPosFar, &rayEnd);

		rayStart = cam3d->getPosition3D();

		Ray touchRay(rayStart, rayEnd);//仮レイを設定

		//レイの当たり判定
		for(int i = 0; i < MAX_UNIT; i++)
		{
			if(-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind)
			{
				if(touchRay.intersects(unit[i].obbHead))//タッチ座標の法線と敵の当たり判定が接触したかをチェック
				{
					Vec3 rot = Vec3(0, 0, 0);
					rot = unit[i].sprite3d->getRotation3D();
					rot.y += 20.0f;
					unit[i].sprite3d->setRotation3D(rot);
				}
			}
		}
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
	for(int i = 0; i < MAX_UNIT; i++)
	{
		if(FALSE == unit[i].valid)
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

﻿#include"Unit.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#else


#endif

USING_NS_CC;
using namespace TapGun;

/**
*	Unitクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Unit::Init( void)
{
	//初期化内容は随時更新します

	//管理フラグ
	visible = FALSE;
	kind = UKIND_NONE;//Unit種別をNONEに
	eState = ESTATE_IDLE;//とりあえずIDLEで初期化

	//変数
	pos = Vec3(0, 0, 0);//モデル座標
	speed = 0.0f;//移動速度
	speedVec = Vec3(0, 0, 0);//移動ベクトル
	targetPos = Vec3(0, 0, 0);//移動目標
	collisionPos = Vec3(0, 0, 0);//当たり判定（OBB）の各辺
	tableNum = -1;

//	colisionNode = Node::create();
	time = 0.0f;//管理フレーム
}



/**
*	Unitクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	Unit配列の番号,Unit種別
*	@return	正常終了:1 初期化エラー:-1
*	@date	1/8 Ver 1.0
*/
int Unit::Init(int num, int utype)
{
	//初期化内容は随時更新します

	//num番のUnit構造体が使用されているか初期化されていない、またはUnit種別が不正、または配列外の場合はエラー
	if(0 > utype || UKIND_NUM <= utype || 0 > num || MAX_UNIT <= num)
	{
		return FALSE;
	}

	//フラグの初期化
	kind = utype;//

	tableNum = -1;//敵用　敵が出現する順番を指定する

	//変数
	pos = Vec3(0, 0, 0);
	speed = 0.0f;
	speedVec = Vec3(0, 0, 0);
	targetPos = Vec3(0, 0, 0);

	time = 0.0f;//管理時間を初期化

	eWaitFrame = 0;//出現までの待ちフレーム
	StandbyPos = Vec3(0, 0, 0);//待機座標


	//モデルの種別によって当たり判定の設定を行う
	//敵や弾の種類（副種別）によってさらに条件分けする
	switch (utype)
	{
	case UKIND_ENEMY://エネミー

		visible = FALSE;//キャラクターの描画は最初OFF

		break;
	case UKIND_EBULLET://敵弾

		visible = FALSE;//キャラクターの描画は最初OFF

		break;
	default:
		//マップ
		visible = TRUE;//マップの描画は最初からON
		break;
	}
	//必要ならばモデルやアニメーション関連のデータを初期化する
}




/**
*	当たり判定の初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Unit::SetCollision(void)
{
	//当たり判定の定義（仮）
	aabbBody = sprite3d->getAABB();

	colisionNode->setPosition3D(Vec3(0.0f, 1.0f, 0.0f));

	//当たり判定の移動
	Vec3 collision_center = colisionNode->getPosition3D() + sprite3d->getPosition3D();

	Vec3 collision_min = collision_center - collisionPos * 0.5f;
	Vec3 collision_max = collision_center + collisionPos * 0.5f;

	aabbBody.set(collision_min, collision_max);
	obbHead = OBB(aabbBody);//
}




/**
*	Unitの各種変数更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Unit::Update(void)
{
	auto director = Director::getInstance();
	auto loopTime = director->getDeltaTime();//ループに要した時間を取得

	//フレームを加算
	time += loopTime;

	//座標を移動
	pos = sprite3d->getPosition3D();
	pos += speedVec * loopTime;
	sprite3d->setPosition3D(pos);


	switch(kind)
	{
	case UKIND_ENEMY:
		//敵のみ当たり判定を更新する
		//当たり判定を移動
	{
						Vec3 collision_center = colisionNode->getPosition3D() + sprite3d->getPosition3D();

						Vec3 collision_min = collision_center - collisionPos * 0.5f;
						Vec3 collision_max = collision_center + collisionPos * 0.5f;

						aabbBody.set(collision_min, collision_max);
						obbHead = OBB(aabbBody);//
	}
		break;
	default:

		break;
	}
}



/**
*	Unitの各種変数更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Unit::Update(float loopTime)
{
	//時間を加算
	time += loopTime;

	//座標を移動
	pos = sprite3d->getPosition3D();
	pos += speedVec * loopTime;
	sprite3d->setPosition3D(pos);


	switch (kind)
	{
	case UKIND_ENEMY:
		//敵のみ当たり判定を更新する
		//当たり判定を移動
	{
		Vec3 collision_center = colisionNode->getPosition3D() + sprite3d->getPosition3D();

		Vec3 collision_min = collision_center - collisionPos * 0.5f;
		Vec3 collision_max = collision_center + collisionPos * 0.5f;

		aabbBody.set(collision_min, collision_max);
		obbHead = OBB(aabbBody);//
	}
		break;
	default:

		break;
	}
}



/**
*	キャラクター固有時間の初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
void Unit::InitTime(void)
{
	time = 0;
}


/**
*	キャラクター固有時間のセット
*
*	@author	sasebon
*	@param	任意の時間
*	@return	なし
*	@date	1/20 Ver 1.0
*/
void Unit::SetTime(float f)
{
	time = f;
}



/**
*	再生するアニメーションをセットする
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
void Unit::SetAnimation(const std::string& animeName, const int speed)
{
	sprite3d->stopALLAnimation();//現在行っているアニメーションを停止する

	//アニメーションの再生方向の設定
	if(0 < speed)//順再生
	{
		sprite3d->startAnimation(animeName);
	}
	else if(0 == speed)//ループ再生
	{
		sprite3d->startAnimationLoop(animeName);
	}
	else if(0 > speed)//逆再生
	{
		sprite3d->startAnimationReverse(animeName);
	}
}



/**
*	キャラクター固有タイムを返す
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
int Unit::GetTime(void)
{
	return time;
}

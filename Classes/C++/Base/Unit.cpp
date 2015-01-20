#include"Unit.h"

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
	valid = FALSE;
	kind = UKIND_NONE;//Unit種別をNONEに

	//変数
	pos = Vec3(0, 0, 0);//モデル座標
	speed = 0.0f;//移動速度
	speedVec = Vec3(0, 0, 0);//移動ベクトル
	targetPos = Vec3(0, 0, 0);//移動目標
	collisionPos = Vec3(0, 0, 0);//当たり判定（OBB）の各辺

	frame = 0;//管理フレーム
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
	if(FALSE != valid || 0 > utype || UKIND_NUM <= utype || 0 > num || MAX_UNIT <= num)
	{
		return FALSE;
	}

	//フラグの初期化
	valid = TRUE;
	kind = utype;

	//変数
	pos = Vec3(0, 0, 0);
	speed = 0.0f;
	speedVec = Vec3(0, 0, 0);
	targetPos = Vec3(0, 0, 0);

	frame = 0;//管理フレーム

	//モデルの種別によって当たり判定の設定を行う
	//敵や弾の種類（副種別）によってさらに条件分けする
	switch(utype)
	{
	case UKIND_ENEMY://エネミー

		break;
	case UKIND_EBULLET://敵弾


		break;
	default:

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

	//当たり判定の移動
	Vec3 collision_center = sprite3d->getPosition3D();

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
	//フレームを加算
	frame += 1;

	//座標を移動
	pos = sprite3d->getPosition3D();
	pos += speedVec;
	sprite3d->setPosition3D(pos);

	//当たり判定を移動
	Vec3 collision_min = pos - collisionPos / 2;
	Vec3 collision_max = pos + collisionPos / 2;

	aabbBody.set(collision_min, collision_max);
	obbHead = OBB(aabbBody);//
}



/**
*	キャラクター固有フレームの初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
void Unit::InitFrame(void)
{
	frame = 0;
}


/**
*	キャラクター固有フレームのセット
*
*	@author	sasebon
*	@param	任意のフレーム
*	@return	なし
*	@date	1/20 Ver 1.0
*/
void Unit::SetFrame(int f)
{
	frame = f;
}

/**
*	キャラクター固有フレームを返す
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
int Unit::GetFrame(void)
{
	return frame;
}

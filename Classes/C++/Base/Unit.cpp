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
	animFrame = -2;//

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

//	Unit::UpdateAnimation();//アニメーションを更新
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
*	再生範囲を指定してアニメーションをセットする
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
//void Unit::SetAnimation(const std::string& animeName, const int speed, const int frame ,const int startF, const int endF)
//{
//	/*@*/
//	//現在はアニメーションフレームの範囲の整合性を取っていないので、今後処理を追加する
//
//	sprite3d->stopALLAnimation();//現在行っているアニメーションを停止する
//	//アニメーション再生時間の設定
//	int f = abs(endF - startF);
//
//	//ループ再生
//	if(0 == frame)
//	{
//		animFrame = -1;//
//		//この場合の処理は後で実装する
//		sprite3d->startAnimationLoop(animeName, startF, endF);//とりあえず
//		return;
//	}
//
//	//それ以外
//	if(0 < f)//アニメーションが正数ならば
//	{
//		animFrame = frame;//フレームが0になるとアニメーション停止
//	}
//	else if(0 == frame)//フレームに0を設定すると、停止しない
//	{
//		animFrame = -1;//
//		//この場合の処理は後で実装する
//		sprite3d->startAnimationLoop(animeName, startF, endF);//とりあえず
//		return;
//	}
//	else
//	{
//		animFrame = 0;//負の数の場合は本来エラー/*@*/
//	}
//
//	//アニメーションの再生方向の設定
//	if(0 <= speed)//順再生
//	{
//		sprite3d->startAnimation(animeName, startF, endF);
//	}
//	else if(0 > speed)//逆再生
//	{
//		sprite3d->startAnimationReverse(animeName);
//	}
//}


/**
*	アニメーションを更新する
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/21 Ver 1.0
*/
//void Unit::UpdateAnimation(void)
//{
	/*-*/
	//不要になったので削除予定

	//if(-2 == animFrame)
	//{

	//}
	//if(-1 == animFrame)//手動停止するまでループを続ける
	//{

	//}
	//else
	//{
	//	animFrame--;//アニメーション管理フレームを減らす
	//	if(0 >= animFrame)
	//	{
	//		sprite3d->stopALLAnimation();
	//		animFrame = -2;
	//	}
	//}
//}



/**
*	アニメーション中かを確認する
*
*	@author	sasebon
*	@param	なし
*	@return	再生中: TRUE | 再生していない : FALSE
*	@date	1/21 Ver 1.0
*/
//BOOL Unit::CheckAnimation(void)
//{
//	/*-*/
//	//不要になったので削除予定
//
//
//	if(0 < animFrame | -1 == animFrame)//再生中
//	{
//		return TRUE;
//	}
//	else if(0 == animFrame | -2 == animFrame)//再生終了または再生していない
//	{
//		return FALSE;
//	}
//}



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

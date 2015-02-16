#include"Player.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#else


#endif

USING_NS_CC;
using namespace TapGun;

/**
*	Playerクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Player::Init( void)
{
	//変数
	speed = 0.0f;//移動速度
	speedVec = Vec3(0, 0, 0);//移動ベクトル
	targetPos = Vec3(0, 0, 0);//移動目標
	collisionPos = Vec3(0, 0, 0);//当たり判定（OBB）の各辺

	colisionNode = Node::create();
	frame = 0;//管理フレーム
}


/**
*	当たり判定の初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Player::SetCollision(void)
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

	sprite3d->addChild(colisionNode);
}




/**
*	Playerの各種変数更新
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void Player::Update(void)
{
	auto director = Director::getInstance();
	auto loopTime = director->getDeltaTime();

	//フレームを加算
	frame += 1;

	//座標を移動
	Vec3 pos = wrapper->getPosition3D();
	pos += speedVec * loopTime;
	wrapper->setPosition3D(pos);

	//当たり判定を移動
	Vec3 collision_center = colisionNode->getPosition3D() + sprite3d->getPosition3D();

	Vec3 collision_min = collision_center - collisionPos * 0.5f;
	Vec3 collision_max = collision_center + collisionPos * 0.5f;


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
void Player::InitFrame(void)
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
void Player::SetFrame(int f)
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
void Player::SetAnimation(const std::string& animeName, const int speed)
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
*	キャラクター固有フレームを返す
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
int Player::GetFrame(void)
{
	return frame;
}


/**
*	アニメーション終了までの時間をセット
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
void Player::setAnimEndTime(float time)
{
	animEndTime = time;
}


/**
*	キャラクター固有フレームを返す
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/20 Ver 1.0
*/
float Player::getAnimEndTime(void)
{
	return animEndTime;
}

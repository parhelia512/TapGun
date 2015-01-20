#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"

#endif

#define MAX_UNIT 100

//using namespace cocos2d;

namespace TapGun
{

	//この定義は今後異なるヘッダファイルに移し替えます
#define FALSE -1
#define TRUE 1


	enum _UNIT_KIND_
	{
		UKIND_NONE,//未使用
		UKIND_PLAYER1,//プレイヤー1
		UKIND_PLAYER2,//プレイヤー2
		UKIND_ENEMY,//エネミー
		UKIND_EBULLET,//敵弾
		UKIND_MAP,//マップモデルも現在はUnitに含めています
		UKIND_NUM
	};



	//Unitクラス
	//プレイヤー・エネミー・弾・マップデータに用います
	class Unit
	{
	public:

		//メンバ変数

		//==フラグ系==
		int valid;//Unit使用フラグ（TRUE/FALSE）
		int kind;//Unit種別（_UNIT_KIND_）

		//==変数==
		cocos2d::Vec3 pos;//モデル座標・・・削除予定（sprite3dの座標を使用）
		float speed;//移動速度（移動量）
		cocos2d::Vec3 speedVec;//移動ベクトル（speedをもとに計算する）
		cocos2d::Vec3 targetPos;//移動時の目標座標（現在は自キャラや弾の移動に用いていますが、無駄と判断すれば今後削除します）
		cocos2d::Vec3 collisionPos;//OBBの辺の長さ（現在は１つのみ定義）

		//==当たり判定関連クラス(仮)==
		cocos2d::AABB aabbHead;//
		cocos2d::AABB aabbBody;//
		cocos2d::OBB obbHead;

		//==モデル・アニメーション関連クラス==
		TapGun::_Sprite3D* sprite3d;
		cocos2d::Node* wrapper;//モデルの親ノード（モデル基準座標として使用する。通常は(0,0,0)座標）
		cocos2d::Animation3D* animation;
		cocos2d::Animate3D* animate;

		//メンバ関数
		void Init(void);//数値の初期化（今後はコンストラクタに置き換える？）
		int Init(int num, int utype);//数値の初期化

		void SetCollision(void);//当たり判定を初期化

		void Update(void);//速度をもとに座標移動と当たり判定移動
		void SetPos(cocos2d::Vec3 pos);//引数の座標に移動
		void InitFrame(void);//フレームを初期化
		int GetFrame(void);//フレームの取得
		void SetFrame(int f);//フレームのセット
		//Character();
		//~Character();
	private:

		int frame;//Unit固有フレーム
	};
}
#endif //__UNIT_H__

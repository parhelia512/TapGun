#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

#include <stdio.h>
#include <fstream>


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"

#endif

namespace TapGun
{

	//この定義は今後異なるヘッダファイルに移し替えます
#define FALSE -1
#define TRUE 1


	//プレイヤークラス
	class Player
	{
	public:

		//メンバ変数


		//==フラグ系==
		int hitpoint;

		cocos2d::Vec3 cameraAjust;//回避モーション時のカメラ位置補正

		//==変数==
		float speed;//移動速度（移動量）
		cocos2d::Vec3 speedVec;//移動ベクトル（speedをもとに計算する）
		cocos2d::Vec3 targetPos;//移動時の目標座標（現在は自キャラや弾の移動に用いていますが、無駄と判断すれば今後削除します）
		cocos2d::Vec3 collisionPos;//OBBの辺の長さ（現在は１つのみ定義）

		//==当たり判定関連クラス(仮)==
		cocos2d::Node* colisionNode;//当たり判定基準用ノード

		cocos2d::AABB aabbHead;//
		cocos2d::AABB aabbBody;//
		cocos2d::OBB obbHead;

		//==モデル・アニメーション関連クラス==

		TapGun::_Sprite3D* sprite3d;
		cocos2d::Node* wrapper;//モデルの親ノード
		cocos2d::Node* leftNode;//回転軸の基準ノード
		cocos2d::Node* rightNode;//回転軸の基準ノード

		cocos2d::Animation3D* animation;
		cocos2d::Animate3D* animate;
		/*
		・座標移動はwrappar
		・回転はsprite3d;
		・Action時はwrapperを回転軸に移動し、移動した分sprite3dを逆に移動させる
		・回避時はwrapperを回転させて座標移動、回転した分sprite3dを逆に回転させる
		*/



		//メンバ関数
		void Init(void);//数値の初期化（今後はコンストラクタに置き換える？）

		void SetCollision(void);//当たり判定を初期化

		void Update(void);//速度をもとに座標移動と当たり判定移動
		void SetPos(cocos2d::Vec3 pos);//引数の座標に移動

		void SetAnimation(const std::string& animeName, const int speed);//

		void InitFrame(void);//フレームを初期化
		int GetFrame(void);//フレームの取得
		void SetFrame(int f);//フレームのセット
		//Character();
		//~Character();
	private:

		int frame;//Unit固有フレーム
		int animFrame;//アニメーション管理フレーム(animFrame >= 0 : 再生中 | animFrame == -1 : ループ再生 | animFrame == -2 : 無再生)
	};
}
#endif //__UNIT_H__

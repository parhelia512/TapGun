#ifndef __UI_H__
#define __UI_H__

#include "cocos2d.h"

#define MAX_UI 20

namespace TapGun
{

//この定義は今後異なるヘッダファイルに移し替えます
#define FALSE -1
#define TRUE 1


	enum _UI_KIND_
	{
		UIKIND_NONE,//未使用
		UIKIND_LIFEBAR,//HPのバー部分
		UIKIND_LIFE,//HPの弾部分
		UIKIND_RETICLE,//レティクル
		UIKIND_ARROW,//回避アイコン
		UKIND_BULLET_A,//残弾（アイコン）
		UKIND_BULLET_B,//残弾（数字）
		UIKIND_NUM//
	};


	//UIクラス
	class UI : public cocos2d::Sprite//
	{
	public:

		//UI();
		//~UI();

		//メンバ変数

		//==フラグ系==
		int valid;//UI使用フラグ（TRUE/FALSE）
		int kind;//UI種別（_UI_KIND_）

		//==変数==
		//速度関連は今後の状況で削除します
		float speed;//移動速度（移動量）
		cocos2d::Vec2 speedVec;//移動ベクトル（speedをもとに計算する）
		cocos2d::Vec2 targetPos;//移動時の目標座標（現在は自キャラや弾の移動に用いていますが、無駄と判断すれば今後削除します）
		int frame;//UI固有フレーム

		//==当たり判定関連クラス(仮)==
		cocos2d::Rect touchRect;//タッチ座標を任意指定する

		//メンバ関数
		void Init(void);//数値の初期化（今後はコンストラクタに置き換える？）
		int Init(int num, int utype);//数値の初期化

		//UI* Create( void);

		void SetCollision(void);//当たり判定を初期化

		void UpdatePos(void);//速度をもとに座標移動と当たり判定移動
		void UpdatePos(cocos2d::Vec2 pos);//引数の座標に移動

	private:
	};
}
#endif //__UI_H__

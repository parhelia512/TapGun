
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

		UIKIND_RETICLE,//レティクル

		UIKIND_LIFEBAR,//HPのバー部分
		UIKIND_LIFE,//HPの弾部分
		UIKIND_ARROW,//回避アイコン
		UKIND_BULLET_A,//残弾（アイコン）
		UKIND_BULLET_B,//残弾（数字）

		UIKIND_WAIT,//ウェイトアラーム
		UIKIND_ACTION,//アクションアラーム
		UIKIND_RELOAD,//リロードアラーム

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


	class LifeUI
	{
	public:
		enum LifeNUmber
		{
			Up,
			Left,
			Down,
			Right,
			LifeNum,
			
			NumberNum = 5,
		};

		LifeUI( const LifeUI& p) = delete;
		LifeUI& operator=( const LifeUI& P) = delete;
		static LifeUI* getInstance( void);
		
		void init( cocos2d::Layer* layer);
		void update( void);
		

	private:
		LifeUI();
		
		cocos2d::Sprite* bullet;
		cocos2d::Sprite* frame;
		cocos2d::Sprite* life[LifeNum];
		cocos2d::Sprite* number[NumberNum];
	};

	class LogoUI
	{
	public:
		enum LogoNumber
		{
			Action,
			Wait,
			Reload,
			LogoNum,
		};

		LogoUI( const LogoUI& p) = delete;
		LogoUI& operator=( const LogoUI& P) = delete;
		static LogoUI* getInstance( void);

		void init( cocos2d::Layer* layer);
		void update( void);
		void setLogo( LogoNumber num);
		void resetLogo( LogoNumber num);

	private:
		LogoUI();
		cocos2d::Sprite* logo[LogoNum];
	};
}
#endif //__UI_H__


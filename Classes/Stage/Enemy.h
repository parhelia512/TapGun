
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "Base/Sprite3D.h"

#endif

namespace TapGun
{

	//エネミーの攻撃タイプ
	enum _ENEMY_ATK_
	{
		AI_ATK_NONE,//攻撃モーションを行わない
		AI_ATK_FAKE,//威嚇攻撃を行う
		AI_ATK_SSHOT,//立ち撃ちを行う
		AI_ATK_NUM
	};

	//エネミーのアイドルモーション
	enum _ENEMY_IDLE_
	{
		AI_IDLE_STOP,//その場で止まるアイドルモーション
		AI_IDLE_SIDE,//左右に動くアイドルモーション
		AI_IDLE_FAKE,//撃つモーションの連続
		AI_IDLE_NUM
	};

	//エネミーの出現方法
	enum _ENEMY_APPEAR_
	{
		AI_APPEAR_RUN,//走りながら登場
		AI_APPEAR_SIDE,//横歩き
		AI_APPEAR_NUM
	};


	class Enemy
	{
	public:
		cocos2d::Vec3 standbyPos;//
		cocos2d::Vec3 targetPos;
		
		int SetAI(int idle, int atk, int appear);
		void SetNextEnemy(int num1, int num2, int num3);

		int number;
		int kind;//敵の種類
		int alive;//生存チェック
		int nextEnemiesNum[3];//この敵が消えたときに、次に出てくる敵
		int finishFlag;//この敵が消えると（倒す、または逃げる）とウェーブ終了（TRUE/FALSE）

		int hitpoint;
//		int AIType;

		//
		int AIIdle;
		int AIAtk;
		int AIappear;//出現パターン

		float atkFrame;//攻撃間隔（秒）
		float waitFrame;//出現してから移動し始めるまでの時間
		float sleepTime;//
	private:

	};
}

#endif // __ENEMY_H__


#ifndef __GAME_MODELSLAYER_H__
#define __GAME_MODELSLAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Unit.h"

#else

#include "C++/Base/Unit.h"

#endif

namespace TapGun
{
	class GameModelsLayer : public cocos2d::Layer
	{
	public:

		//メンバ変数
		int playerNum;


		virtual bool init();//レイヤーのインスタンス生成

		//初期化系
		int InitLayer(void);//レイヤーの変数初期化
		void InitAllModels();//モデル全体の初期化

		int InitPlayer(int stage_num);//プレイヤーの初期化
		int InitEnemy(int stage_num);//エネミー初期化
		int InitMap(int stage_num);//マップの初期化


		void UpdateLayer();//レイヤー更新

		//
		int GetPlayerNum();

		void UpdateModels();//親シーンから呼び出される

		//モデル表示用の構造体と関数を一時的にまとめています
		int SearchFreeUnit();//
		Unit unit[MAX_UNIT];//


		//
		void update(float delta);//現在使用しない
		void moveTime(float delta);//現在使用しない

		CREATE_FUNC(GameModelsLayer);

	private:

		//更新系
		void UpdatePlayer();//
		void UpdateEnemy();
		void UpdateBullets();

		void ShootBullet(int enemy_num);//
		void CheckHit( void);//当たり判定処理

	};
}

#endif //__GAME_MODELSLAYER_H__

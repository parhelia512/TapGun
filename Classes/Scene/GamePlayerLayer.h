
#ifndef __GAME_MODELSLAYER_H__
#define __GAME_MODELSLAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Unit.h"

#else

#include "Base/Unit.h"

#endif

namespace TapGun
{
	class GamePlayerLayer : public cocos2d::Layer
	{
	public:

		Unit unit[MAX_UNIT];//

		virtual bool init();//レイヤーのインスタンス生成
		//初期化系
		int InitLayer(void);//レイヤーの変数初期化
		int InitPlayer(int stage_num);//プレイヤーの初期化


		//更新
		void UpdateLayer();//レイヤー更新（親シーンから呼び出される）
		void UpdateWait(void);//

		void SetEnemy(void);//


		int GetPlayerNum();
		//
		void update(float delta);//現在使用しない
		void moveTime(float delta);//現在使用しない

		CREATE_FUNC(GamePlayerLayer);

	private:

		//メンバ変数
		int playerNum;

		//更新系
		void UpdatePlayer(void);//
		void UpdateEnemy(void);
		void UpdateBullets(void);
		void UpdateModels(void);//



		//プレイヤーの更新
		void ActionShot(void);
		void ActionIdle(void);
		void ActionDodge(void);
		void ActionHide(void);
		void ActionAppear(void);
		void ActionDamaged(void);
		void ActionRun(void);
		void ActionDead(void);


		void ShootBullet(int enemy_num);//
		void CheckHit(void);//当たり判定処理

		int SearchFreeUnit();//空きユニットの検索
	};
}
#endif //__GAME_MODELSLAYER_H__

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


		virtual bool init();
		//static cocos2d::Scene* CreateScene();

		int InitLayer(void);

		int InitPlayer(int stage_num);//

		int InitMap(int stage_num);
		int InitEnemy(int stage_num);

		int GetPlayerNum();

		void update(float delta);
		void moveTime(float delta);

		void UpdateModels();//親シーンから呼び出される

		//モデル表示用の構造体と関数を一時的にまとめています
		void InitAllModels();//
		int SearchFreeUnit();//
		Unit unit[MAX_UNIT];//

		int playerNum;


		void UpdateLayer();//レイヤー更新

		CREATE_FUNC(GameModelsLayer);

	private:
		void UpdatePlayer();//

		void UpdateEnemy();
		void UpdateBullets();

		void ShootBullet(int enemy_num);

	};
}

#endif //__GAME_MODELSLAYER_H__
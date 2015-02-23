
#ifndef __ENEMY_TABLE_H__
#define __ENEMY_TABLE_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Enemy.h"

#else

#include "Stage/Enemy.h"

#endif

namespace TapGun
{

	//enum _ENEMY_AI_
	//{
	//	AI_TYPE_MATO,//撃っている振りのみ
	//	AI_TYPE_SINGLE,//その場で撃つモーション（走りで登場）
	//	AI_TYPE_SINGLE_J,//サイドジャンプで登場、その後はその場で撃つのみ
	//};




	class EnemyTable
	{
	public:
		Enemy enemyData[100];
		cocos2d::Vec3 standbyPos[10];//
		cocos2d::Vec3 targetPos[20];//


		int finishNumber;//敵が最大何対出てくるか
		void InitAll();

	private:

	};
}

#endif // __MUZZLE_FLASH_H__

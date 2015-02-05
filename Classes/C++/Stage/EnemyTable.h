
#ifndef __ENEMY_TABLE_H__
#define __ENEMY_TABLE_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Enemy.h"

#else

#include "C++/Stage/Enemy.h"

#endif

namespace TapGun
{
	class EnemyTable
	{
	public:
		Enemy enemyData[100];
		cocos2d::Vec3 standbyPos[10];//
		cocos2d::Vec3 targetPos[20];//

		int finishNumber;//“G‚ªÅ‘å‰½‘Îo‚Ä‚­‚é‚©

		void InitAll();

	private:

	};
}

#endif // __MUZZLE_FLASH_H__

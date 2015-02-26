
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
	//	AI_TYPE_MATO,//�����Ă���U��̂�
	//	AI_TYPE_SINGLE,//���̏�Ō����[�V�����i����œo��j
	//	AI_TYPE_SINGLE_J,//�T�C�h�W�����v�œo��A���̌�͂��̏�Ō��̂�
	//};




	class EnemyTable
	{
	public:
		Enemy enemyData[100];
		cocos2d::Vec3 standbyPos[10];//
		cocos2d::Vec3 targetPos[20];//


		int finishNumber;//�G���ő剽�Ώo�Ă��邩
		void InitAll();

	private:

	};
}

#endif // __MUZZLE_FLASH_H__

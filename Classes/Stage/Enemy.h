
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
	class Enemy
	{
	public:
		cocos2d::Vec3 standbyPos;//
		cocos2d::Vec3 targetPos;
		
		int number;
		int kind;//�G�̎��
		int alive;//�����`�F�b�N
		int nextEnemyNum;//���̓G���������Ƃ��ɁA���ɏo�Ă���G
		int finishFlag;//���̓G��������Ɓi�|���A�܂��͓�����j�ƃE�F�[�u�I���iTRUE/FALSE�j
		int AIType;
	private:

	};
}

#endif // __ENEMY_H__


#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"

#endif

namespace TapGun
{
	class Enemy
	{
	public:
		cocos2d::Vec3 standbyPos;//
		cocos2d::Vec3 targetPos;
		
		int number;
		int kind;//“G‚Ìí—Ş

		int nextEnemyNum;//‚±‚Ì“G‚ªÁ‚¦‚½‚Æ‚«‚ÉAŸ‚Éo‚Ä‚­‚é“G

	private:

	};
}

#endif // __ENEMY_H__


#ifndef __MUZZLE_FLASH_H__
#define __MUZZLE_FLASH_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "Base/Sprite3D.h"

#endif

#define MUZZLE_COUNT 3

namespace TapGun
{
	class Muzzle
	{
	public:
		static Muzzle* createMuzzle( _Sprite3D* parentData, std::string pointName);
		void setMuzzleAction( void);
		void muzzleUpdate( void);
		
	private:
		bool shotFlag;
		int count;
		_Sprite3D* sprite3D[MUZZLE_COUNT];
	};
}

#endif // __MUZZLE_FLASH_H__

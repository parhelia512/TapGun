
#ifndef __MUZZLE_FLASH_H__
#define __MUZZLE_FLASH_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"

#endif

namespace TapGun
{
	class Muzzle
	{
	public:
		Muzzle();
		void muzzleUpdate( void);
		void muzzleflagOn( void);
		void muzzleFlagOff( void);

		_Sprite3D* sprite3D[5];

	private:

		bool shotFlag;
		int count;
	};

	class P_Muzzle : public Muzzle
	{
	public:
		void createMuzzle( _Sprite3D* parentData);

	private:
	};

	class E_Muzzle
	{
	public:
		void createMuzzle( _Sprite3D* parentData);
		void muzzleUpdate( void);
		void muzzleflagOn( void);
		void muzzleFlagOff( void);

	private:
		Muzzle* muzzleR;
		Muzzle* muzzleL;
	};
}

#endif // __MUZZLE_FLASH_H__

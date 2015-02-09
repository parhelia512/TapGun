
#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"

#endif

namespace TapGun
{
	class Wrapper
	{
	public:
		enum Flag
		{
			True = 1,
			False = 0,
		};

		Wrapper( const Wrapper &P) = delete;
		Wrapper& operator= ( const Wrapper &P) = delete;
		static Wrapper* getInstance( void);

		static cocos2d::Scene* newCreateScene( cocos2d::Layer* ( *Scene)( void));

		static cocos2d::Scene* getNowSceneObject( void);
		static cocos2d::Layer* getNowSceneLayer( void);

	private:
		Wrapper() {}

		cocos2d::Scene* nowSceneObject;
		cocos2d::Layer* nowSceneLayer;
	};
}

#endif // __WRAPPER_H__

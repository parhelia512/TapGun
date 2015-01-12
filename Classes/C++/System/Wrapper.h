
#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "cocos2d.h"

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

	static Scene* newCreateScene( layer* ( *Scene)( void));

	static Scene* getNowSceneObject( void);
	static layer* getNowSceneLayer( void);

private:
	Wrapper() {}

	Scene* nowSceneObject;
	layer* nowSceneLayer;
};

}

#endif // __WRAPPER_H__

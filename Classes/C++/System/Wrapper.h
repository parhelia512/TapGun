
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
		_TRUE = 1,
		_FALSE = 0,
	};
	cocos2d::Sprite* load2DObject( std::string fileName);
	cocos2d::Sprite3D* load3DObject( std::string fileName);
	int start3DObjectAnime( cocos2d::Sprite3D* sprite3D, int animeNumber);
	int start3DObjectAnime( cocos2d::Sprite3D* sprite3D, std::string animeName);
	int start3DObjectAnime( cocos2d::Sprite3D* sprite3D, int animeNumber, Flag loopFlag);
	int start3DObjectAnime( cocos2d::Sprite3D* sprite3D, std::string animeName, Flag loopFlag);
	int stop3DObjectAnime( cocos2d::Sprite3D* sprite3D);
	int get3DObjectAnimeState( cocos2d::Sprite3D* sprite3D);
	int release2DObject( cocos2d::Sprite* sprite);
	int release3DObject( cocos2d::Sprite3D* sprite3D);

	int loadSound( std::string fileName);
	int playSound( std::string fileName);
	int playSound( std::string fileName, Flag loopFlag);
	int stopSound( std::string fileName);
	int releaseSound( std::string fileName);

private:

};

}

#endif // __WRAPPER_H__


#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Wrapper.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "C++/System/Wrapper.h"

#else

#include "C++/System/Wrapper.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;


cocos2d::Sprite* Wrapper::load2DObject( std::string fileName)
{

}

cocos2d::Sprite3D* Wrapper::load3DObject( std::string fileName)
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

  #ifdef DEBUG
	
  #else
	
  #endif

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#else

  #ifdef _DEBUG
	
  #else
	
  #endif

#endif

}

int Wrapper::start3DObjectAnime( cocos2d::Sprite3D* sprite3D, int animeNumber)
{

}

int Wrapper::start3DObjectAnime( cocos2d::Sprite3D* sprite3D, std::string animeName)
{

}
	
int Wrapper::start3DObjectAnime( cocos2d::Sprite3D* sprite3D, int animeNumber, Flag loopFlag)
{

}
	
int Wrapper::start3DObjectAnime( cocos2d::Sprite3D* sprite3D, std::string animeName, Flag loopFlag)
{

}
	
int Wrapper::stop3DObjectAnime( cocos2d::Sprite3D* sprite3D)
{

}
	
int Wrapper::get3DObjectAnimeState( cocos2d::Sprite3D* sprite3D)
{

}
	
int Wrapper::release2DObject( cocos2d::Sprite* sprite)
{

}
	
int Wrapper::release3DObject( cocos2d::Sprite3D* sprite3D)
{

}

int Wrapper::loadSound( std::string fileName)
{

}
	
int Wrapper::playSound( std::string fileName)
{

}
	
int Wrapper::playSound( std::string fileName, Flag loopFlag)
{

}
	
int Wrapper::stopSound( std::string fileName)
{

}
	
int Wrapper::releaseSound( std::string fileName)
{

}



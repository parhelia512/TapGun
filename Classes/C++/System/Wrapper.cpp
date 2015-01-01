
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

Sprite* Wrapper::load2DObject( const string& fileName)
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto sprite = Sprite::create( fileName);
	return sprite;
#else
	string filePass = "Graph/Pictures/" + fileName;
	auto sprite = Sprite::create( filePass);
	return sprite;
#endif
}

Sprite* Wrapper::load2DObjectFrame( const string& fileName)
{	
	auto sprite = Sprite::createWithSpriteFrameName( fileName);
	if( sprite == nullptr) return nullptr;
	return sprite;
}

Sprite3D* Wrapper::load3DObject( const string& fileName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

  #ifdef DEBUG
	
  #else
	
  #endif

#else

  #ifdef _DEBUG
	
  #else
	
  #endif

#endif
	return 0;
}

int Wrapper::start3DObjectAnime( Sprite3D* sprite3D, int animeNumber)
{
	return 0;
}

int Wrapper::start3DObjectAnime( Sprite3D* sprite3D, const string& animeName)
{
	return 0;
}
	
int Wrapper::start3DObjectAnime( Sprite3D* sprite3D, int animeNumber, Flag loopFlag)
{
	return 0;
}
	
int Wrapper::start3DObjectAnime( Sprite3D* sprite3D, const string& animeName, Flag loopFlag)
{
	return 0;
}
	
int Wrapper::stop3DObjectAnime( Sprite3D* sprite3D)
{
	return 0;
}
	
int Wrapper::get3DObjectAnimeState( Sprite3D* sprite3D)
{
	return 0;
}
	
int Wrapper::release2DObject( Sprite* sprite)
{
	return 0;
}
	
int Wrapper::release3DObject( Sprite3D* sprite3D)
{
	return 0;
}

int Wrapper::loadSound( const string& fileName)
{
	return 0;
}
	
int Wrapper::playSound( const string& fileName)
{
	return 0;
}
	
int Wrapper::playSound( const string& fileName, Flag loopFlag)
{
	return 0;
}
	
int Wrapper::stopSound( const string& fileName)
{
	return 0;
}
	
int Wrapper::releaseSound( const string& fileName)
{
	return 0;
}


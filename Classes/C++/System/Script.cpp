
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Script.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "C++/System/Script.h"

#else

#include "C++/System/Script.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

int Script::loadSctiptFile( const std::string& fileName)
{

}

int Script::loadCommand( int index)
{

}


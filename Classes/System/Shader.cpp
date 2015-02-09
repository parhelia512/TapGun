
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Shader.h"

#else

#include "System/Shader.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

Shader* Shader::getInstance( void)
{
	static Shader* P;
	if( !P) P = new Shader;
	return P;
}
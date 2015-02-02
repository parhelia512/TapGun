
#ifndef  __DEFINE_H__
#define  __DEFINE_H__

#include "cocos2d.h"

namespace TapGun
{
	class SystemValue
	{
	public:
		enum LayerNumber
		{
			ERROR_MESSAGE = 10,
		};
		static cocos2d::Size windowSize;
		static cocos2d::Vec2 origin;
	};
}

#endif // __DEFINE_H__

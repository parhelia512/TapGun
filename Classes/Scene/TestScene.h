
#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

namespace TapGun
{
	class Test : public cocos2d::Layer
	{
	public:
		static double frame;

		std::string fileName;
		cocos2d::Size visibleSize;
		cocos2d::Sprite3D* sprite3d[2];
		cocos2d::Animation3D* animation[2];
		cocos2d::Animate3D* animate[2];
		static cocos2d::Scene* createScene();

		virtual bool init();
		void update( float delta);
		void moveTime( float delta);
		void menuCloseCallback(cocos2d::Ref* pSender);
		void setCocos( void);

		static cocos2d::Layer* lay;

		CREATE_FUNC(Test);
	};
}

#endif // __TEST_SCENE_H__


#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "ADX2Manager.h"

#else

#include "Adx2/ADX2Manager.h"

#endif

namespace TapGun
{
	class Test : public cocos2d::Layer
	{
	public:
		static double frame;

		static cocos2d::Scene* createScene();

		virtual bool init();
		void update( float delta);
		void moveTime( float delta);
		
		//タッチイベントのリスナー
		cocos2d::EventListenerTouchOneByOne *listener;
		bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

		CREATE_FUNC(Test);

		CC_SYNTHESIZE_RETAIN( ADX2::CueSheet*, _cueSheet, CueSheet);
	};
}

#endif // __TEST_SCENE_H__

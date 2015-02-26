
#ifndef __CREDIT_SCENE_H__
#define __CREDIT_SCENE_H__

#include "cocos2d.h"

namespace TapGun
{
	class CreditScene : public cocos2d::Layer
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

		CREATE_FUNC( CreditScene);
	};
}

#endif // __CREDIT_SCENE_H__

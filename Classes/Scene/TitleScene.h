#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

namespace TapGun
{
	class TitleScene : public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();
		
		bool init();
		void update( float delta);
		void moveTime( float delta);

		bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused_event);
		void onTouchMoved( cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchEnded( cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

		void setSprite( void);

		CREATE_FUNC( TitleScene);

	private:
		enum SpriteName
		{
			BG,
			Logo,
			Frame,
			Menu,
			SpriteNum,
		};

		enum MenuFlag
		{
			Idle	= ( 1 << 0),
			LogoIn	= ( 1 << 1),
			LogoOK	= ( 1 << 2),

			MenuIn	= ( 1 << 3),
			MenuOK	= ( 1 << 4),
			
			TitleEnd = ( 1 << 5),
		};

		enum SpriteName
		{
			BG,
			Logo,
			Frame,
			Menu,
			SpriteNum,
		};

		unsigned char menuFlag;
		int alphaCount;

		bool logoAlphaFlag;
		int logoAlphaCount;
		int logoAlphaWaitCount;
		unsigned int frame;
		cocos2d::Sprite* sprite[SpriteNum];
		cocos2d::Menu* menu[SpriteNum];

		template<class P> static bool checkFlag( P* flag, const P number);
		template<class P> static void setFlag( P* flag, const P number);
		template<class P> static void resetFlag( P* flag, const P number);
	};
}

#endif // __TITLE_SCENE_H__

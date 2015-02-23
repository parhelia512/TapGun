#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "Base/Sprite3D.h"

#endif

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

		void menuStartCallback( cocos2d::Ref* pSender);
		void menuEndCallback( cocos2d::Ref* pSender);
		void menuCreditCallback( cocos2d::Ref* pSender);

		void sprite3DLoadCallback( _Sprite3D* sprite3D, void* param);

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
			TeamLogo	= ( 1 << 0),
			TitleLogoIn	= ( 1 << 1),
			TitleLogoOK	= ( 1 << 2),

			MenuIn	= ( 1 << 3),
			MenuOK	= ( 1 << 4),
			
			TitleEnd = ( 1 << 5),
		};

		enum TeamLogoState
		{
			LogoIn,
			LogoOut,
			Wait,
			WaitTime = 75,
			AlphaValue = 5,
		};

		enum MenuName
		{
			Start,
			End,
			Credit,
			MenuNum,
		};

		TeamLogoState teamLogoState = LogoIn;
		int waitCount = 0;

		MenuFlag menuFlag;
		int alphaCount;

		bool logoAlphaFlag;
		int logoAlphaCount;
		int logoAlphaWaitCount;
		unsigned int frame;

		cocos2d::Sprite* teamLogo;
		cocos2d::Sprite* sprite[SpriteNum];
		cocos2d::Menu* menu[MenuNum];

		cocos2d::Sprite* effect[8];

		void teamLogoAction( void);
		void setSprite( void);
		void setMenu( void);
		void menuAction( void);
		void loadSound( void);

		template<class P> static bool checkFlag( P* flag, const P number);
		template<class P> static void setFlag( P* flag, const P number);
		template<class P> static void resetFlag( P* flag, const P number);
	};
}

#endif // __TITLE_SCENE_H__


#ifndef __GAME_UILAYER_H__
#define __GAME_UILAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "UI.h"

#else

#include "C++/Base/UI.h"

#endif

#define MAX_UI 20

namespace TapGun
{
	class GameUILayer : public cocos2d::Layer
	{
	public:
		//�����o�֐�
		virtual bool init();

		void update(float delta);
		void moveTime(float delta);

		void InitLayer();

		void InitAllUI(void);
		int SerchFreeUI(void);
		void SetUI(void);
		void UpdateUI(float px, float py, float pz, float rx, float ry, float rz);
		void UpdateUI(void);
		void MoveReticle(void);

		//cocos2d::Sprite* UISprite[MAX_UI];
		//cocos2d::BillBoard* UIBillBoard[MAX_UI];
		cocos2d::Sprite* UISprite[MAX_UI];
		cocos2d::BillBoard* UIBillBoard[MAX_UI];
		cocos2d::Node* UINode[MAX_UI];
		int valid[MAX_UI];

		TapGun::UI Ui[MAX_UI];

		cocos2d::EventListenerTouchOneByOne *listener;
		bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		//void menuCloseCallback(CCObject* pSender);


		CREATE_FUNC(GameUILayer);
	};
}
#endif //__GAME_UILAYER_H__

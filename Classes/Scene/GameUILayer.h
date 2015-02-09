
#ifndef __GAME_UILAYER_H__
#define __GAME_UILAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "UI.h"

#else

#include "Base/UI.h"

#endif

#define MAX_UI UIKIND_NUM

namespace TapGun
{
	class GameUILayer : public cocos2d::Layer
	{
	public:
		virtual bool init();

		void update(float delta);
		void moveTime(float delta);

		void InitLayer();

		void InitAllUI(void);
		int SerchFreeUI(void);
		void SetUI(void);
		void UpdateLayer(void);
		void MoveReticle(void);
		void UpdateLifeBar(void);
		void LoadUISprite(void);

		cocos2d::Sprite* UISprite[MAX_UI];
		cocos2d::BillBoard* UIBillBoard[MAX_UI];
		int valid[MAX_UI];
		int visible[MAX_UI];

		TapGun::UI Ui[MAX_UI];

		CREATE_FUNC(GameUILayer);
	};
}
#endif //__GAME_UILAYER_H__

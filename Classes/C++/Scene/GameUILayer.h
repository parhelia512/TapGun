
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
		void UpdateLayer(void);
		void MoveReticle(void);
		void UpdateLifeBar(void);

		//cocos2d::Sprite* UISprite[MAX_UI];
		//cocos2d::BillBoard* UIBillBoard[MAX_UI];
		cocos2d::Sprite* UISprite[MAX_UI];
		cocos2d::BillBoard* UIBillBoard[MAX_UI];
//		cocos2d::Node* UINode[MAX_UI];//Z軸を考慮する必要がなくなったので、今後削除する/*-*/
		int valid[MAX_UI];

		TapGun::UI Ui[MAX_UI];

		CREATE_FUNC(GameUILayer);
	};
}
#endif //__GAME_UILAYER_H__

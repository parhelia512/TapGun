#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"


namespace TapGun
{
	/* Scene Enumration */
	typedef enum
	{
		GameLayerTag,
		UILayerTag
	} GameSceneTag;
	
	enum _GAME_STATE_
	{
		GSTATE_INIT,
		GSTATE_PAUSE,
		GSTATE_PLAY,
		GSTATE_NUM
	};

	class GameScene : public cocos2d::Layer
	{
	public:
		virtual bool init();

		int playerNum;//

		static cocos2d::Scene* CreateScene();

		void update(float delta);
		void moveTime(float delta);

		int InitCamera(void);
		int UpdateCamera(void);

		int stage_num;//現在ステージ番号（初期化等に用いる）
		int game_state;//ゲームのステート

		//各種レイヤーの初期化に用いる
		//GameLayer* gameLayer();//ゲームレイヤークラスを使用する
		//UILayer * uiLayer();//ＵＩレイヤーを使用する

		//static GameScene* sharedLayer();
		cocos2d::EventListenerTouchOneByOne *listener;

		bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	private:

		//void UpdatePlayer( void);
		//void UpdateEnemy( void);

		//void menuCloseCallback(CCObject* pSender);

		CREATE_FUNC(GameScene);
	};

}

#endif // __GAME_SCENE_H__

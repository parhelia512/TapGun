
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

	class GameScene : public cocos2d::Layer
	{
	public:

		//メンバ変数

		//==フラグ系==


		//==変数系==

		//==メンバ関数==
		static cocos2d::Scene* CreateScene();
		virtual bool init();//シーンクリエイト時の初期化関数（自動的に呼び出される）

		void update(float delta);//更新関数（現在は使用していない）
		void moveTime(float delta);//指定フレームごとの更新関数（こちらを使用する）

		int InitCamera(void);//カメラ座標更新関数（子レイヤー初期化後に使用する）
		int UpdateCamera(void);//カメラ座標の更新（子レイヤークリエイト後に使用する）


		//各種レイヤーの初期化に用いる
		//GameLayer* gameLayer();//ゲームレイヤークラスを使用する
		//UILayer * uiLayer();//ＵＩレイヤーを使用する

		//static GameScene* sharedLayer();

		//タッチイベントのリスナー
		cocos2d::EventListenerTouchOneByOne *listener;
		bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
		void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	private:
		clock_t nowTime;//現在時刻
		float loopTime;//ループに要した時間
		float fps;//
		//void UpdatePlayer( void);
		//void UpdateEnemy( void);

		//void menuCloseCallback(CCObject* pSender);

		CREATE_FUNC(GameScene);
	};
}

#endif // __GAME_SCENE_H__

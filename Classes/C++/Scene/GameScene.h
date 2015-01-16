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

		//メンバ変数

		//==フラグ系==
		int game_state;//ゲームの現在ステート


		//==変数系==
		cocos2d::Vec2 touch_pos;//仮タッチ座標（現在はシングルタッチのみ）
		int playerNum;//Unit配列のプレイヤー番号（0で固定してもよい？）

		//将来的には管理クラスのメンバ変数に含めます
		int stage_num;//現在ステージ番号（初期化等に用いる）
		int player_state;//

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

		//void UpdatePlayer( void);
		//void UpdateEnemy( void);

		//void menuCloseCallback(CCObject* pSender);

		CREATE_FUNC(GameScene);
	};

}

#endif // __GAME_SCENE_H__

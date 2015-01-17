#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__

#include "cocos2d.h"

namespace TapGun
{

	enum _GAME_STATE_
	{
		GSTATE_INIT,
		GSTATE_PAUSE,
		GSTATE_PLAY,
		GSTATE_NUM
	};

	enum _PLAYER_STATE_
	{
		PSTATE_IDLE,
		PSTATE_SHOT,
		PSTATE_DAMAGED,
		PSTATE_RUN,
		PSTATE_DEAD,
		PSTATE_NUM
	};

	enum _ENEMY_STATE_
	{
		ESTATE_IDLE,
		ESTATE_ATTACK1,
		ESTATE_ATTACK2,
		ESTATE_ATTACK3,
		ESTATE_DAMAGED,
		ESTATE_DEAD,
		ESTATE_NUM
	};

	class GameMaster
	{
	public:
		//各種変数は適宜get関数、set関数での処理に移し替えていきます


		//変数


		//関数
		GameMaster(const GameMaster &P) = delete;
		GameMaster& operator= (const GameMaster &P) = delete;
		static GameMaster* GetInstance(void);


		static cocos2d::Camera* Get3DCamInstance(void);
		static cocos2d::Camera* Get2DCamInstance(void);

		void InitScreenSize(void);

		void InitParam(void);
		void InitParam(int wave);

		//setParam(現在はvoid型で宣言しています)
		void SetCamera2D(cocos2d::Vec3 pos);

		void SetCamera3DPos(cocos2d::Vec3 pos);
		void SetCamera3DRot(cocos2d::Vec3 rot);
		void AddCamera3DPos(cocos2d::Vec3 pos);
		void AddCamera3DRot(cocos2d::Vec3 rot);

		void InitCamera3D( void);
		void SetGameState(int state);
		void SetPlayerState(int state);
		void SetTouchPos(cocos2d::Vec2 tPos);

		//getParam
		cocos2d::Camera* GetCamera2D(void);//2D用カメラのクラスを返す
		cocos2d::Camera* GetCamera3D(void);
		cocos2d::Vec2 GetTouchPos(void);
		int GetPlayerState(void);
		int GetGameState(void);

	private:
		cocos2d::Size screenSize;
		int wave;//現在ウェーブ
		int playerState;//プレイヤーの状態
		int gameState;//ゲームの状態
		cocos2d::Vec2 touchPos;//タッチ座標（現在はシングルタッチに対応）
		static cocos2d::Camera* camera2D;
		static cocos2d::Camera* camera3D;

		GameMaster() {}


	};
}

#endif // __GAMEMASTER_H__

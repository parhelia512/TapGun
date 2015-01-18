#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__

#include "cocos2d.h"

namespace TapGun
{
	enum _CAMERA_FLAG_
	{
		CAMFLAG_DEFALUT = 1,
		CAMFLAG_3D = 2,
	};

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

		void InitCamera2D(void);
		void InitCamera3D(void);


		////////////////////////////////////////
		//setParam(現在はvoid型で宣言しています)

		//2Dカメラ用
		void SetCamera2DPos(cocos2d::Vec3 pos);//2Dカメラの位置を変更することはあまりないので必要ない？

		//3Dカメラ用
		void SetCamera3DPos(cocos2d::Vec3 pos);
		void SetCamera3DRot(cocos2d::Vec3 rot);
		void AddCamera3DPos(cocos2d::Vec3 pos);
		void AddCamera3DRot(cocos2d::Vec3 rot);


		void SetGameState(int state);
		void SetPlayerState(int state);
		void SetTouchPos(cocos2d::Vec2 tPos);



		////////////////////////////////////////
		//getParam

		//2Dカメラ用
		cocos2d::Camera* GetCamera2D(void);//2D用カメラのクラスを返す


		//3Dカメラ用
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

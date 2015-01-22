#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__

#include "cocos2d.h"





namespace TapGun
{

//この定義は今後異なるヘッダファイルに移し替えます
#define FALSE -1
#define TRUE 1

	enum _CAMERA_FLAG_
	{
		//CAMFLAG_DEFAULT = CameraFlag::DEFAULT,//
		//CAMFLAG_3D = CameraFlag::USER1
		CAMFLAG_DEFAULT = 1,//
		CAMFLAG_3D = 2
	};

	enum _GAME_STATE_
	{
		GSTATE_INIT,
		GSTATE_WAIT,
		GSTATE_PLAY,
		GSTATE_PAUSE,
		GSTATE_CONTINUE,
		GSTATE_GAMEOVER,
		GSTATE_NUM
	};

	enum _PLAYER_STATE_
	{
		PSTATE_IDLE,
		PSTATE_SHOT,
		PSTATE_DODGE,//隠れ中
		PSTATE_HIDE,//隠れている
		PSTATE_APPEAR,//隠れた状態から出る
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

	enum _TOUCH_STATE_
	{
		TSTATE_OFF,
		TSTATE_ON,
		TSTATE_MOVE,
		TSTATE_RELEASE
	};

	enum _TOUCH_FLAG_
	{
		TFLAG_OFF,
		TFLAG_ON,
		TFLAG_MOVE,
		TFLAG_RELEASE,
		TFLAG_CANCEL,
		TFLAG_NUM
	};

	class GameMaster
	{
	public:


		//変数
		static cocos2d::Node* CamNode;


		//関数
		GameMaster(const GameMaster &P) = delete;
		GameMaster& operator= (const GameMaster &P) = delete;
		static GameMaster* GetInstance(void);


		static cocos2d::Camera* Get2DCamInstance(void);
		static cocos2d::Camera* Get3DCamInstance(void);
//		static cocos2d::Node* Get3DCamInstance(void);

		void InitScreenSize(void);


		void InitParam(void);
		void InitParam(int wave);

		void InitCamera2D(void);
		void InitCamera3D(void);


		//2Dカメラ用
		void SetCamera2DPos(cocos2d::Vec3 pos);//2Dカメラの位置を変更することはあまりないので必要ない？
		cocos2d::Camera* GetCamera2D(void);//2D用カメラのクラスポインタを返す

		//3Dカメラ用
		void SetCamera3DPos(cocos2d::Vec3 pos);
		void SetCamera3DRot(cocos2d::Vec3 rot);
		void AddCamera3DPos(cocos2d::Vec3 pos);
		void AddCamera3DRot(cocos2d::Vec3 rot);
		cocos2d::Camera* GetCamera3D(void);
		cocos2d::Node* GetCameraNode(void);


		void SetGameState(int state);
		void SetPlayerState(int state);

		//タッチ関連
		void UpdateTouchManager(void);//タッチ管理クラスを更新
		void SetTouchPos(cocos2d::Touch* tch);//タッチ座標を取得
		int SetTouchFlag(int state);//タッチフラグを取得
		cocos2d::Vec2 GetTouchPosInView(void);//タッチ座標を返す
		cocos2d::Vec2 GetTouchPos(void);//タッチ座標を返す

		int GetTouchFlag(void);//タッチフラグを返す
		int GetTouchState(void);//タッチ状態を返す

		int GetPlayerState(void);
		int GetGameState(void);

	private:
		cocos2d::Size screenSize;
		int wave;//現在ウェーブ
		int playerState;//プレイヤーの状態
		int gameState;//ゲームの状態


		cocos2d::Touch* touch;//タッチ管理
		int touchState;//タッチの状態
		int touchFlag;//

		static cocos2d::Camera* camera2D;
		static cocos2d::Camera* camera3D;

		GameMaster() {}
	};
}

#endif // __GAMEMASTER_H__

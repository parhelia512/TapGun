#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__

#include "cocos2d.h"


namespace TapGun
{

	//この定義は今後異なるヘッダファイルに移し替えます
#define FALSE -1
#define TRUE 1


	//プレイヤーのパラメータ定義
#define STS_PLAYERHP 6//プレイヤーの最大HP
#define STS_RAPIDSPEED 8//プレイヤーの連射速度（フレーム）
#define STS_MAXBULLETS 30//プレイヤーの最大弾数
#define STS_MUTEKIFRAME 120//無敵時間

#define STS_HIDEWAIT (12)// + 12)//回避モーションが終了するまでの全体フレーム
#define STS_HIDESTART 1//回避ボタンを押してから回避モーションが始まるまでの時間
#define STS_MUTEKISTART 0//回避モーションが始まってから無敵時間に移行するまでの時間
#define STS_APPEARSTART 1//回避ボタンを離してから突撃モーションが始まるまでの時間
#define STS_MUTEKIEND (STS_HIDEWAIT - STS_MUTEKISTART)//突撃モーションが始まってから無敵時間が終了するまでの時間
#define STS_RELOADSTART 12//回避モーションが始まってからリロードが行われるまでの時間

#define BATTLE_FEILD_X 0.8//タッチで攻撃可能な画面割合

	//回避ボタンの当たり判定定義（ボタンのスプライトと当たり判定を分けて実装します）
#define HIDE_UI_RECT_X 0.18f//当たり判定矩形
#define HIDE_UI_RECT_Y 0.18f//当たり判定矩形
#define HIDE_UI_POS_X 0.09f//当たり判定中心
#define HIDE_UI_POS_Y 0.2f//当たり判定中心

	//以上のステータスをもとに座標を計算する
#define HIDE_UI_X0 (HIDE_UI_RECT_X * 0.5f - HIDE_UI_POS_X)
#define HIDE_UI_Y0 (HIDE_UI_RECT_Y * 0.5f - HIDE_UI_POS_Y)
#define HIDE_UI_X1 (HIDE_UI_RECT_X * 0.5f + HIDE_UI_POS_X)
#define HIDE_UI_Y1 (HIDE_UI_RECT_Y * 0.5f + HIDE_UI_POS_Y)


//Action時のカメラの設定(右)
#define C_PERSE_R 35//カメラ視野角
#define C_SETX_R -0.62f
#define C_SETY_R 1.61f
#define C_SETZ_R 5.3f
#define C_ROTX_R -4.0f
#define C_ROTY_R 10.0f
#define C_ROTZ_R 0.0f

//Action時のカメラの設定(左)
#define C_PERSE_L 55//カメラ視野角
#define C_SETX_L 0.62f
#define C_SETY_L 6.21f
#define C_SETZ_L 12.3f
#define C_ROTX_L -20.0f
#define C_ROTY_L -35.0f
#define C_ROTZ_L 0.0f

//Wait時のカメラの設定
#define W_PERSE 35//カメラ視野角
#define W_SETX 0.0f
#define W_SETY 1.61f
#define W_SETZ 2.9f

#define W_ROTX 0.0f
#define W_ROTY 0.0f
#define W_ROTZ 0.0f

//プレイヤーが回避する時の軸の座標（プレイヤーから見た相対座標、左側時）
//プレイヤーは0度基準で配置しているので、X軸Y軸がカメラとそれぞれ反転しています
#define HIDEPOINT_X 0.35f
#define HIDEPOINT_Y 0.35f

//回避した時のカメラの移動後の座標（カメラから見た相対座標、左側時）
#define HIDECAMERA_X 0.8f
#define HIDECAMERA_Y -0.8f

	//
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
		GSTATE_PLAY_INIT,
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

	enum _PLAYERSIDE_
	{
		PSIDE_RIGHT,
		PSIDE_LEFT
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

	enum _STAGE_POINT_DEF_
	{
		POINT_NONE,//使用しない
		POINT_BATTLE,//バトルマス
		POINT_CHANGE,//方向転換
		POINT_CLEAR,
	};

	enum _STAGE_POINT_
	{
		//後で名前を設定
		POINT_START,
		POINT_STAGE1,
		POINT_S2_1,
		POINT_STAGE2,
		POINT_S3_1,
		POINT_S3_2,

		POINT_FINISH,
	};

	//プレイヤーの進行座標を定義する構造体
	typedef struct
	{
		cocos2d::Vec3 pos;
		cocos2d::Vec3 rot;
		int pointType;
		int playerSide;
		cocos2d::Point hidePoint;//回避動作の軸となる座標
	}StagePoint;

	class GameMaster
	{
	public:

		//変数

		//各種フラグ（後でprivateに修正する）
		int waitFlag;//ウェイトモードを進行させるフラグ
		int sPoint;//現在のステージポイント
		int rapidFrame;//連射待ち時間
		int wave;//現在ウェーブ
		StagePoint stagePoint[100];//プレイヤーの進行座標を定義する構造体

		int playerSide;//プレイヤーが左右どちらに立っているかのフラグ
		int playerHitFlag;//プレイヤーの無敵状態のフラグ（TRUE/FALSE）
		int nowBullets;//プレイヤーの現在弾数

		int flgPlayerATK;//プレイヤーの攻撃処理判定を行うか（TRUE/FALSE）

		int hideFrame;//回避フレーム
		int mutekiFrame;//無敵時間

		//関数
		GameMaster(const GameMaster &P) = delete;
		GameMaster& operator= (const GameMaster &P) = delete;
		static GameMaster* GetInstance(void);

		static cocos2d::Camera* Get2DCamInstance(void);
		static cocos2d::Camera* Get3DCamInstance(void);
		static cocos2d::Node* GetCamNodeInstance(void);

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

		void SetCameraNodePos(cocos2d::Vec3 pos);
		void SetCameraNodeRot(cocos2d::Vec3 rot);
		void AddCameraNodePos(cocos2d::Vec3 pos);
		void AddCameraNodeRot(cocos2d::Vec3 rot);

		cocos2d::Camera* GetCamera3D(void);
		const cocos2d::Node* GetCameraNode(void);

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

		//ゲーム状態のセットと取得
		int GetGameState(void);
		void SetGameState(int gState);

	private:
		int playerState;//プレイヤーの状態
		int gameState;//ゲームの状態

		cocos2d::Touch* touch;//タッチ管理
		int touchState;//タッチの状態
		int touchFlag;//

		//プレイヤーのステータス
		int playerHP;//プレイヤーの体力

		cocos2d::Size screenSize;

		static cocos2d::Camera* camera2D;
		static cocos2d::Camera* camera3D;
		static cocos2d::Node* CamNode;

		//
		cocos2d::Vec2 setHidePoint(StagePoint stagePoint);

		GameMaster() {}
	};
}

#endif // __GAMEMASTER_H__

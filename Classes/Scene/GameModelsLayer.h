
#ifndef __GAME_MODELSLAYER_H__
#define __GAME_MODELSLAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Unit.h"
#include "Player.h"
//#include "muzzle.h"
#include "EnemyTable.h"

#else

#include "Base/Unit.h"
#include "Base/Player.h"
//#include "Object/muzzle.h"
#include "Stage/EnemyTable.h"

#endif

//#define DEBUG_CENTER//デバッグ用。回転軸を示すモデルを描画

namespace TapGun
{

	enum _UNIT_NUM_
	{
		UNIT0_MAP = 0,//0はマップ
		UNIT1_ENEMY = 1,//1~20は敵
		UNIT2_BULLET = 21,//21~70は弾
		UNIT3_MAX = MAX_UNIT
	};

	typedef struct
	{
		cocos2d::Node* gNode;
		cocos2d::Node* lNode;
		cocos2d::Node* lNode2;
	}CalcNode;


	class GameModelsLayer : public cocos2d::Layer
	{
	public:
		Player player;

#ifdef DEBUG_CENTER
		Unit center;
#endif
		Unit calc;
		Unit unit[MAX_UNIT];//

		EnemyTable enemyTable[100];//敵の出現テーブル

		timeval* nowTV;//現在時刻
		timeval* preTV;//
		float nowTime;//現在時刻（秒）
		float preTime;//前フレームの時刻（秒）

		//Muzzle muzzle;//プレイヤーのマズル

		//Node* gNode;
		//Node* lNode;
		CalcNode cNode;
		cocos2d::Vec3 camTarget;//回避時のカメラの移動先座標
		cocos2d::Vec3 camCenter;//回避時のカメラの移動前座標

		virtual bool init();//レイヤーのインスタンス生成
		//初期化系
		void LoadModels(void);//スプライトを生成
		void InitLayer(void);//レイヤーの変数初期化
		void InitAllModels();//モデル全体の初期化
		void InitPlayer(int stage_num);//プレイヤーの初期化
		int InitEnemy(int stage_num);//エネミー初期化
		void InitBullet(void);
		int InitMap(int stage_num);//マップの初期化

		void checkNextEnemy(int enemyNum);//

		cocos2d::Vec2 calcRot(float pRot, int pSide);//角度計算
		cocos2d::Vec2 calcCamPos(float pRot, int pSide);//角度計算
		cocos2d::Vec2 calcCamPos2(float pRot, int pSide);//角度計算
		cocos2d::Vec2 calcCamPos3(float pRot, int pSide);//角度計算

		//更新系
//		void UpdateLayer();//レイヤー更新（親シーンから呼び出される）
		void UpdateWait(void);//
		void UpdatePlayer(void);//
		void UpdateEnemy(void);
		void UpdateBullets(void);
		void CheckHit(void);//当たり判定処理

		//ゲーム遷移チェック
		int CheckNextStage(void);

		void SetEnemy(void);//

		void update(float delta);//現在使用しない
		void moveTime(float delta);//現在使用しない

		CREATE_FUNC(GameModelsLayer);

	private:

		//敵のAIセット


		//プレイヤーの更新
		void ActionShot(void);
		void ActionIdle(void);
		void ActionDodge(void);
		void ActionHide(void);
		void ActionAppear(void);
		void ActionDamaged(void);
		void ActionRecover(void);
		void ActionRun(void);
		void ActionDead(void);

		//エネミーの更新
		void ActionEStandby(int num);
		void ActionEIdle(int num);
		void ActionEDodge(int num);
//		void ActionEHide(int num);
//		void ActionEAppear(int num);
		void ActionEDamaged(int num);
		void ActionERecover(int num);
//		void ActionERun(int num);
		void ActionEDead(int num);
		void ActionEMove(int num);
		void ActionEAttack(int num);

		//エネミーの更新
		//void ActionEnemy1(int num);//その場で威嚇射撃をし続ける
		//void ActionEnemy2(int num);//一定タイミングで撃つ
		//void ActionEnemy3(int num);//左右に動いて警戒

		//敵の処理
		void setNextEnemy(int num);

		void ShootBullet(int enemy_num);//

//		int SearchFreeUnit();//空きユニットの検索

		int SearchFreeEnemy();//空きユニットの検索


		int enemyStuck;//各ステージごとの残り敵数

		//計算用
		float getNowTime();
	};
}
#endif //__GAME_MODELSLAYER_H__

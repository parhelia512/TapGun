
#ifndef __GAME_MODELSLAYER_H__
#define __GAME_MODELSLAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Unit.h"
#include "Player.h"
//#include "muzzle.h"
#include "EnemyTable.h"

#else

#include "C++/Base/Unit.h"
#include "C++/Base/Player.h"
//#include "C++/Object/muzzle.h"
#include "C++/Stage/EnemyTable.h"

#endif

namespace TapGun
{
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
		Unit center;
		Unit calc;
		Unit unit[MAX_UNIT];//

		EnemyTable enemyTable[100];//敵の出現テーブル

//		Muzzle muzzle;//プレイヤーのマズル

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
		int InitMap(int stage_num);//マップの初期化

		void checkNextEnemy(int enemyNum);//

		cocos2d::Vec2 calcRot(float pRot, int pSide);//角度計算
		cocos2d::Vec2 calcCamPos(float pRot, int pSide);//角度計算
		cocos2d::Vec2 calcCamPos2(float pRot, int pSide);//角度計算
		cocos2d::Vec2 calcCamPos3(float pRot, int pSide);//角度計算

		//更新
		void UpdateLayer();//レイヤー更新（親シーンから呼び出される）
		void UpdateWait(void);//

		void SetEnemy(void);//

		void update(float delta);//現在使用しない
		void moveTime(float delta);//現在使用しない

		CREATE_FUNC(GameModelsLayer);

	private:

		//メンバ変数
		//		cocos2d::Node* hideNodeLeft;
		//		cocos2d::Node* hideNodeRight;
		//		cocos2d::Point hidePoint;


		//更新系
		void UpdatePlayer(void);//
		void UpdateEnemy(void);
		void UpdateBullets(void);

		int CheckNextStage(void);

		//プレイヤーの更新
		void ActionShot(void);
		void ActionIdle(void);
		void ActionDodge(void);
		void ActionHide(void);
		void ActionAppear(void);
		void ActionDamaged(void);
		void ActionRun(void);
		void ActionDead(void);

		//エネミーの更新
		void ActionEnemy1(int num);
		void ActionEnemy2(int num);

		//敵の処理
		void setNextEnemy(int num);

		void ShootBullet(int enemy_num);//
		void CheckHit(void);//当たり判定処理

		int SearchFreeUnit();//空きユニットの検索

		int enemyStuck;//各ステージごとの残り敵数

	};
}
#endif //__GAME_MODELSLAYER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "EnemyTable.h"
#include "Unit.h"

#else

#include "Stage/EnemyTable.h"
#include "Base/Unit.h"

#endif

USING_NS_CC;
using namespace TapGun;

void EnemyTable::InitAll()
{
	for (int i = 0; i < 10; i++)
	{
		standbyPos[i] = Vec3(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < 20; i++)
	{
		targetPos[i] = Vec3(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < 100; i++)
	{
		enemyData[i].kind = EKIND_TWIN;//敵は現在すべてツインマシンガンで初期化
		for (int j = 0; j < 3; j++)
		{
			enemyData[j].nextEnemiesNum[j] = -1;
		}
		enemyData[i].number = -1;
		enemyData[i].standbyPos = Vec3(0.0f, 0.0f, 0.0f);
		enemyData[i].targetPos = Vec3(0.0f, 0.0f, 0.0f);
		enemyData[i].alive = FALSE;
		enemyData[i].finishFlag = FALSE;

		enemyData[i].hitpoint = 0;

		enemyData[i].AIIdle = -1;
		enemyData[i].AIAtk = -1;
		enemyData[i].AIappear = -1;//出現パターン

		enemyData[i].atkFrame = 0.0f;//攻撃間隔（秒）
		enemyData[i].waitFrame = 0.0f;//出現してから移動し始めるまでの時間
	}
}
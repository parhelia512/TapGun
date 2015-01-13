#include "GameModelsLayer.h"

#define PI 3.1415926

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)



#else




#endif

USING_NS_CC;
using namespace TapGun;

static GameModelsLayer *multiSceneLayerInstance;

#define A

/*
インクリメント
*/
//GameModelsLayer::GameLayer()
//{
//	for(int i = 0; i < MAX_MODEL; i++)
//	{
//		unit[MAX_MODEL].valid = 0;
//
//	}
//}

Scene* GameModelsLayer::CreateScene()
{
	Scene *scene = Scene::create();
	GameModelsLayer *layer = GameModelsLayer::create();
	scene->addChild(layer);
	return scene;
}


/**
*	ゲーム本編のモデルレイヤーの初期化
*
*	@author	sasebon
*	@param	なし
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
bool GameModelsLayer::init()
{

	if(!Layer::init())
	{
		return false;
	}
	multiSceneLayerInstance = this;

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	//auto listener = EventListenerTouchOneByOne::create();

	/*
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameModelsLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameModelsLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameModelsLayer::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	*/

	//this->scheduleUpdate();
	//this->schedule(schedule_selector(GameModelsLayer::moveTime), 0.016f);

	return true;
}


/**
*	ゲーム本編のUIレイヤーの各種数値初期化
*
*	@author	sasebon
*	@param	なし
*	@return	初期化成功／不可のbool値
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitLayer(void)
{
	InitAllModels();

	playerNum = -1;
	playerNum = InitPlayer(0);//とりあえず引数0
	//InitMap(0);//正規のマップデータが降りてくるまでいったん保留します
	InitEnemy(0);

	return playerNum;
}

/**
*	全モデル初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void GameModelsLayer::InitAllModels()
{
	for(int i = 0; i < MAX_MODEL; i++)
	{
		unit[i].Init();//メンバ変数初期化
	}
}



/**
*	プレイヤー初期化
*
*	@author	sasebon
*	@param	ステージ番号
*	@return	正常:Unit配列のプレイヤー番号 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitPlayer(int stage_num)
{
	std::string fileName1 = "mot_player_hide shot";
	std::string fileName2 = "box_tex.png";

	int num = SearchFreeUnit();
	if(FALSE == num)
	{
		return FALSE;
	}
	unit[num].Init();//メンバ変数の初期化をしておく
	unit[num].sprite3d = Sprite3D::create(fileName1, fileName2);
	unit[num].Init(num,UKIND_PLAYER1);
	playerNum = num;

	unit[num].wrapper = Node::create();//モデルの親ノード
	unit[num].wrapper->addChild(unit[num].sprite3d);//親ノードにスプライトを紐付け
	addChild(unit[num].wrapper);//親ノードをレイヤーに紐付け

	switch(stage_num)
	{
	case 0:

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setRotation3D(Vec3(0.0f, 180.0f, 0.0f));//プレイヤーは反対を向く
		unit[num].sprite3d->setPosition3D(Vec3(2.0f, 0.0f, -8.5f));

		break;
	defalult:
		return FALSE;
		break;
	}


	//当たり判定の定義（仮）
	unit[num].collision_vec = Vec3(1.2, 3.0, 1.2);
	unit[num].SetCollision();

	//アニメーション読み込み
	//auto animation = Animation3D::create(fileName1);
	//auto animate = Animate3D::create(animation);
	//animate->setSpeed(1);

	//unit[num].sprite3d->runAction(RepeatForever::create(animate));

	return num;
}






/**
*	エネミー初期化
*
*	@author	sasebon
*	@param	ステージ番号
*	@return	正常:1 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitEnemy(int stage_num)
{
	//※ステージスクリプトの内容を読み込んで初期化を行います

	int num = -1;
	std::string fileName1 = "mot_enemy_dei1";
	std::string fileName2 = "tex_boy.png";

	switch(stage_num)
	{
	case 0:


		//テストエネミーの読み込み：１
		num = SearchFreeUnit();
		if(-1 == num)
		{
			return false;
		}

		unit[num].sprite3d = Sprite3D::create(fileName1, fileName2);
		unit[num].Init(num, UKIND_ENEMY);

		unit[num].wrapper = Node::create();//モデルの親ノード
		unit[num].wrapper->addChild(unit[num].sprite3d);
		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setPosition3D(Vec3(4.0f, 0.0f, -18.5f));

		unit[num].aabbBody = unit[num].sprite3d->getAABB();//


		//アニメーション読み込み
		{
			//auto animation = Animation3D::create(fileName1);
			//auto animate = Animate3D::create(animation);
			//animate->setSpeed(1);
			//unit[num].sprite3d->runAction(RepeatForever::create(animate));
		}


		//テストエネミーの読み込み：２
		fileName1 = "mot_enemy_dei2";
		fileName2 = "tex_boy.png";

		num = SearchFreeUnit();
		if(-1 == num)
		{
			return false;
		}
		unit[num].Init();//メンバ変数の初期化をしておく

		unit[num].sprite3d = Sprite3D::create(fileName1, fileName2);
		unit[num].Init(num, UKIND_ENEMY);

		unit[num].wrapper = Node::create();//モデルの親ノード
		unit[num].wrapper->addChild(unit[num].sprite3d);
		addChild(unit[num].wrapper);

		unit[num].sprite3d->setScale(1.0f);
		unit[num].sprite3d->setPosition3D(Vec3(3.0f, 0.0f, -23.5f));

		//アニメーション読み込み
		{
			//auto animation2 = Animation3D::create(fileName1);
			//auto animate2 = Animate3D::create(animation2);
			//animate2->setSpeed(1);
			//unit[num].sprite3d->runAction(RepeatForever::create(animate2));
		}

		break;
	defalut:
		break;
	}



	return TRUE;
}


/**
*	ステージオブジェクトの初期化
*
*	@author	sasebon
*	@param	ステージ番号
*	@return	正常:1 初期化失敗:-1
*	@date	1/8 Ver 1.0
*/
int GameModelsLayer::InitMap(int stage_num)
{
	std::string fileName1 = "map.c3t";
	std::string fileName2 = "stage_tex.png";

	int num = SearchFreeUnit();
	if(-1 == num)
	{
		return false;
	}
	unit[num].Init();//メンバ変数の初期化をしておく

#ifdef A//
	unit[num].sprite3d = Sprite3D::create(fileName1);
	unit[num].sprite3d->setTexture(fileName2);
#elif defined B//
	unit[num].sprite3d = Sprite3D::create(fileName1, fileName2);
#endif
	unit[num].valid = 1;
	unit[num].kind = UKIND_MAP;

	unit[num].wrapper = Node::create();//モデルの親ノード
	unit[num].wrapper->addChild(unit[num].sprite3d);
	addChild(unit[num].wrapper);
	//addChild(unit[num].sprite3d);

	unit[num].sprite3d->setScale(1.0f);
	unit[num].sprite3d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	unit[num].sprite3d->setPosition3D(Vec3(0.0f, -5.5f, 0.0f));

	return TRUE;
}







void GameModelsLayer::UpdateModels()
{
	//float yrot = 1.0f;
	//Vec3 tmpVec3 = unit[1].sprite3d->getRotation3D();
	//tmpVec3.y += yrot;
	//unit[1].sprite3d->setRotation3D(tmpVec3);
}



void GameModelsLayer::UpdatePlayer()
{
	//

}



void GameModelsLayer::UpdateEnemy()
{
	for(int i = 0; i < MAX_MODEL; i++)
	{
		if(-1 != unit[i].valid && UKIND_ENEMY == unit[i].kind)
		{
			unit[i].frame += 1;
			if(120 <= unit[i].frame)
			{
				ShootBullet(i);//i番のエネミーが弾を発射する
				unit[i].frame = 0;
			}
		}
	}
}



/*

*/
void GameModelsLayer::ShootBullet(int enemy_num)
{
	int num = SearchFreeUnit();
	if(FALSE != num)
	{
		unit[num].sprite3d = Sprite3D::create("tama", "tama.png");
		unit[num].Init(num, UKIND_EBULLET);

		unit[num].wrapper = Node::create();//モデルの親ノード
		unit[num].wrapper->addChild(unit[num].sprite3d);
		addChild(unit[num].wrapper);


		unit[num].sprite3d->setScale(0.02f);

		////当たり判定の定義（仮）
		//unit[num].aabbBody = unit[num].sprite3d->getAABB();
		//unit[num].aabbBody.set(Vec3(-0.3, -0.3, -0.3), Vec3(0.3, 0.3, 0.3));
		//unit[num].obbHead = OBB(unit[num].aabbBody);//
		////unit[num].obbHead.set();
		unit[num].collision_vec = Vec3(0.2, 0.2, 0.2);//当たり判定矩形の大きさを設定
		unit[num].SetCollision();//当たり判定をセット

		//弾を撃ったエネミーの座標と、プレイヤーの座標を元に、弾の移動方向を求める
		Vec3 enemy_pos = unit[enemy_num].sprite3d->getPosition3D();
		Vec3 player_pos = unit[playerNum].sprite3d->getPosition3D();

		//unit[num].speed_vec = Vec3(enemy_pos.x, 0, 0);
		unit[num].speed_vec = player_pos - enemy_pos;//この方法が正しければ使用する

		//ベクトルの正規化を行う
		float vx = unit[num].speed_vec.x;
		float vz = unit[num].speed_vec.z;

		float dist = sqrtf(vx * vx + vz * vz);//二次元的な距離
		vx = vx / dist;
		vz = vz / dist;

		//正規化が終わったら、速度をかけて方向ベクトルの計算終了
		unit[num].speed = 0.8f;
		unit[num].speed_vec.x = vx * unit[num].speed;
		unit[num].speed_vec.z = vz * unit[num].speed;
		unit[num].speed_vec.y = 0;//yは今のところ0で扱う

		unit[num].sprite3d->setPosition3D(enemy_pos);
		unit[num].sprite3d->setPositionY(1.2f);

	}
}


/*

*/
void GameModelsLayer::UpdateBullets()
{
	//全ての敵弾ユニットを更新
	for(int i = 0; i < MAX_MODEL; i++)
	{
		if(FALSE != unit[i].valid && UKIND_EBULLET == unit[i].kind)
		{
			unit[i].UpdatePos();//座標と一緒に当たり判定を移動
			unit[playerNum].UpdatePos();//当たり判定更新

			//unit[i].sprite3d->getBoundingBox();



			//プレイヤーとの当たり判定を処理
			if(unit[playerNum].obbHead.intersects(unit[i].obbHead))
			{
				unit[i].sprite3d->setVisible(false);
			}
		}
	}
}



int GameModelsLayer::GetPlayerNum()
{
	return playerNum;
}


int GameModelsLayer::SearchFreeUnit()
{
	for(int i = 0; i < MAX_MODEL; i++)
	{
		if(FALSE == unit[i].valid)
		{
			return i;
		}
	}

	return -1;
}




/*
指定フレームごとに呼び出される
*/
void GameModelsLayer::moveTime(float delta)
{

}



void GameModelsLayer::update(float delta)
{

}


/*
bool GameModelsLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return true;
}


void GameModelsLayer::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{

}



void GameModelsLayer::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{

}


//void GameModelsLayer::onTouchCancelled = CC_CALLBACK_2(GameModelsLayer::onTouchCancelled, this);
//{
//
//	//画面をタッチした時の処理
//
//}

*/
#include"UI.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#else


#endif


using namespace TapGun;
USING_NS_CC;


/**
*	インクリメント
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
//UI::UI(void)
//{
//	初期化内容は随時更新します
//
//	管理フラグ
//	valid = FALSE;
//	kind = UIKIND_NONE;//UI種別をNONEに
//
//	変数
//	speed = 0.0f;//移動速度
//	speedVec = Vec2(0.0f, 0.0f);//移動ベクトル
//	targetPos = Vec2(0.0f, 0.0f);//移動目標
//
//	frame = 0;//管理フレーム
//}


/**
*	UIクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::Init(void)
{
	//初期化内容は随時更新します

	//管理フラグ
	valid = FALSE;
	kind = UIKIND_NONE;//UI種別をNONEに

	//変数
	//speed = 0.0f;//移動速度
	//speedVec = Vec3(0, 0, 0);//移動ベクトル
	//targetPos = Vec3(0, 0, 0);//移動目標

	frame = 0;//管理フレーム
}







/**
*	UIクラスのメンバ変数を初期化
*
*	@author	sasebon
*	@param	UI配列の番号,UI種別
*	@return	正常終了:1 初期化エラー:-1
*	@date	1/8 Ver 1.0
*/
int UI::Init(int num, int utype)
{
	//初期化内容は随時更新します


	//num番のUI構造体が使用されているか初期化されていない、またはUI種別が不正、または配列外の場合はエラー
	if(FALSE != valid || 0 > utype || UIKIND_NUM <= utype || 0 > num || MAX_UI <= num)
	{
		return FALSE;
	}

	//フラグの初期化
	valid = TRUE;
	kind = utype;

	//変数
	speed = 0.0f;
	//speedVec = Vec3(0, 0, 0);
	//targetPos = Vec3(0, 0, 0);

	frame = 0;//管理フレーム

	//モデルの種別によって当たり判定の設定を行う
	//敵や弾の種類（副種別）によってさらに条件分けする
	switch(utype)
	{
	case UIKIND_ARROW:

		break;
	default:

		break;
	}
}




//UI* UI::Create( void)
//{
//	auto sprite = new UI();
//	return sprite;
//}





/**
*	当たり判定の初期化
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::SetCollision(void)
{

}




/**
*	速度をもとにしたUI移動
*
*	@author	sasebon
*	@param	なし
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::UpdatePos(void)
{

}



/**
*	引数座標へのUI移動
*
*	@author	sasebon
*	@param	座標
*	@return	なし
*	@date	1/8 Ver 1.0
*/
void UI::UpdatePos(Vec2 pos)
{
}

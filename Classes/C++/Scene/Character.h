
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

using namespace cocos2d;

namespace TapGun
{
	enum _CHAR_KIND_
	{
		CKIND_NONE,
		CKIND_PLAYER,
		CKIND_ENEMY,
		CKIND_EBULLET,//敵弾
		CKIND_MAP
	};

	class Character
	{
	public:

		int valid;
		int kind;
		int frame;//

		Sprite3D* sprite3d;//モデルのローカル座標
		Node* wrapper;//モデルの親ノード（モデル基準座標として使用する。通常は(0,0,0)座標）
		Animation3D* animation;
		Animate3D* animate;
		Vec3 pos;//モデル座標
		Vec3 target_pos;//モデルが移動するときの目標座標（自キャラや弾の移動に用いる）
		Vec3 speed_vec;//移動速度
		float speed;//

		void Init(void);//数値の初期化（今後はコンストラクタに置き換える？）

		//Character();
		//~Character();
	private:
	};
}

#endif //__CHARACTER_H__

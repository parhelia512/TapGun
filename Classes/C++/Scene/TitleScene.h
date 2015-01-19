#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

namespace TapGun
{


	#include "cocos2d.h"

	class TitleScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone


	int game_state;

	
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void ReplaceGameScene(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);
};
}

#endif // __TITLE_SCENE_H__

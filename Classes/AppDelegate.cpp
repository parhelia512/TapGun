
#include "AppDelegate.h"
#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "TestScene.h"
#include "C++/Scene/GameScene.h"

#else

#include "C++/Scene/TestScene.h"
#include "C++/Scene/GameScene.h"

#endif

USING_NS_CC;
using namespace TapGun;

cocos2d::Size SystemValue::windowSize;
cocos2d::Vec2 SystemValue::origin;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 16, 8 };//深度バッファを16bitに設定
	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
	auto glview = director -> getOpenGLView();

	if(!glview)
	{
		glview = GLViewImpl::create( "TapGun");
		director -> setOpenGLView( glview);
	}

	director -> setDisplayStats( true) ;
	glview -> setDesignResolutionSize( 1280, 800, ResolutionPolicy::SHOW_ALL);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview -> setFrameSize( 1280, 800);
#endif
	director -> setAnimationInterval( 1.0 / 60);

	auto scene = Test::createScene();
//	auto scene = GameScene::CreateScene();
	director -> runWithScene( scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance() -> stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance() -> startAnimation();
}

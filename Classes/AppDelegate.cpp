#include "AppDelegate.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "TestScene.h"
#else
#include "C++/Scene/TestScene.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
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
//	glview -> setDesignResolutionSize( 1280, 800, ResolutionPolicy::SHOW_ALL);
	director -> setAnimationInterval( 1.0 / 60);

	auto scene = TapGun::Test::createScene();
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

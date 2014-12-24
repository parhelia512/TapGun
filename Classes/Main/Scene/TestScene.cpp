
#include "TestScene.h"

USING_NS_CC;
using namespace TapGun;

double Test::frame;

Scene* Test::createScene()
{
	auto scene = Scene::create();
	auto layer = Test::create();
	scene->addChild(layer);
	return scene;
}

bool Test::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(Test::menuCloseCallback, this));
	fileName = "point.c3t";
#else
	auto closeItem = MenuItemImage::create(
										   "Graph/Pictures/CloseNormal.png",
										   "Graph/Pictures/CloseSelected.png",
										   CC_CALLBACK_1(Test::menuCloseCallback, this));
	fileName = "Graph/Models/test.c3b";
#endif
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	auto label = LabelTTF::create("Hello World", "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	
	auto _bg = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
	this->addChild(_bg);
//
//#define COUNT 1
//	Sprite3D *sprite3D[COUNT];
//	for( int i = 0; i < COUNT; i++)
//	{
//		sprite3D[i] = Sprite3D::create( "map.c3b");
//		sprite3D[i] -> setTexture( "stage_tex.png");
//		sprite3D[i] -> setPosition3D( Vec3( visibleSize.width / 2, -visibleSize.height / 8, 0.0f));
//		sprite3D[i] -> setScale( 40.0f);
//		addChild( sprite3D[i]);
//	}



	for( int i = 0; i < 1; i++)
	{
		sprite3d[i] = Sprite3D::create( fileName);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		sprite3d[i] -> setTexture( "box_tex.png");
#else
		sprite3d[i] -> setTexture( "Graph/Textures/box_tex.png");
#endif
		sprite3d[i] -> setScale( 250.0f);
		sprite3d[i] -> setPosition3D( Vec3( visibleSize.width / 2, visibleSize.height / 2, 0));
		auto animation = Animation3D::create( fileName);
		animate[i] = Animate3D::create( animation);
//		if( i == 0)
//		{
//			sprite3d[0] -> setPosition3D( Vec3( visibleSize.width / 4, visibleSize.height / 4, 0.0f));
//			animate[0] = Animate3D::create( animation, 0, 0.016 * 44);
//			animate[0] -> setSpeed(1);
//		}
//		if( i == 1)
//		{
//			sprite3d[1] -> setPosition3D( Vec3( visibleSize.width / 4 * 3, visibleSize.height / 4, 0.0f));
//			animate[1] = Animate3D::create( animation, 0.016 * 45, 0.016 * 60);
//			animate[1] -> setSpeed(1);
//		}
		sprite3d[i] -> runAction( RepeatForever::create( animate[i]));
		addChild( sprite3d[i]);
	}
	/*
	auto shader = new GLProgram();
	shader -> initWithFilenames( "test.vsh", "test.fsh");
	shader -> bindAttribLocation( GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shader -> bindAttribLocation( GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	shader -> bindAttribLocation( GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shader -> link();
	shader -> updateUniforms();
	shader -> setUniformLocationWith1i( shader -> getUniformLocationForName( "u_mosaicLevel"), 10);
	shader -> setUniformLocationWith2f( shader -> getUniformLocationForName( "u_texSize"), visibleSize.width / 4, visibleSize.height / 3);
	sprite3d -> setShaderProgram( shader);
	*/

	auto sprite = Sprite::create( "nikotyan.png");
	sprite -> setPosition( visibleSize.width / 2, visibleSize.height / 2);
//	addChild( sprite);
	
	this -> scheduleUpdate();
	this -> schedule(schedule_selector(Test::moveTime), 0.016f);
	return true;
}

void Test::moveTime( float delta)
{
	
}

void Test::update( float delta)
{
	static auto frame = 0;
	frame++;
	auto f = frame % 180;
//	sprite3d[0] -> setRotation3D( Vec3( f, 0.0f, 0.0f));
	auto p = frame % 20;
	sprite3d[0] -> setPosition3D( Vec3( visibleSize.width / 2, visibleSize.height / 2, 0));
//	sprite3d[0] -> setPosition3D( Vec3( 0, 0, 0));
}

void Test::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

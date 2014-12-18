#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
 //   this->addChild(sprite, 0);

	auto _bg = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
	this->addChild(_bg);
//
//#define COUNT 1
//	Sprite3D *sprite3D[COUNT];
//	for( int i = 0; i < COUNT; i++)
//	{
//		sprite3D[i] = Sprite3D::create( "sarari.c3b");
////		sprite3D[i] -> setTexture( "tortoise.png");
//		addChild( sprite3D[i]);
//		auto animation = Animation3D::create( "sarari.c3b");
//		auto animate = Animate3D::create( animation, 0.f, 1.933f);
//		sprite3D[i] -> runAction( RepeatForever::create( animate));
//		//		Animate3D::create(animation, 1.933f, 2.8f);
//		sprite3D[i] -> setPosition(Vec2( visibleSize.width / 2, visibleSize.height / 2));
//		sprite3D[i] -> setPositionZ( 0.0);
//		auto rotation = RotateBy::create( 10, Vec3(0, 360, 0));
//		sprite3D[i] -> runAction( RepeatForever::create(rotation));
//	}


	fileName = "test_box.c3b";
	for( int i = 0; i < 2; i++)
	{
		sprite3d[i] = Sprite3D::create( fileName);
		sprite3d[i] -> setTexture( "box_tex.png");
		sprite3d[i] -> setScale( 3.0f);
		animation[i] = Animation3D::create( fileName);
		animate[i] = Animate3D::create( animation[i]);
		sprite3d[i] -> runAction( RepeatForever::create( animate[i]));
		if( i == 0) sprite3d[0] -> setPosition3D( Vec3( visibleSize.width / 4, visibleSize.height / 4, 0.0f));
		else sprite3d[1] -> setPosition3D( Vec3( visibleSize.width / 4 * 3, visibleSize.height / 4, 0.0f));
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

	this -> scheduleUpdate();
	this -> schedule(schedule_selector(HelloWorld::moveTime), 0.016f);
	return true;
}

void HelloWorld::moveTime( float delta)
{
	static int frame = 1;
	if( frame % 60 == 0)
	{
		sprite3d[0] -> pauseSchedulerAndActions();
		
	}
	else if( frame % 60 == 30)
	{
		sprite3d[0] -> resumeSchedulerAndActions();
	}
	if( frame == 120)
	{
		sprite3d[1] -> stopAllActions();
		animation[1] = Animation3D::create( fileName);
		animate[1] = Animate3D::create( animation[1]);
		sprite3d[1] -> runAction( RepeatForever::create( animate[1]));
	}
	frame++;
}

void HelloWorld::update( float delta)
{
	
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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

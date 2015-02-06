
#include "cocos2d.h"
#include "Muzzle.h"
#include "Sprite3D.h"

USING_NS_CC;
using namespace TapGun;

Muzzle::Muzzle()
{
	for( int i = 1; i < 5; i++)
	{
		auto str = __String::createWithFormat( "Muzzle/mazuru_%i.c3b", i);
		sprite3D[i] = _Sprite3D::create( str -> getCString());
		sprite3D[i] -> setVisible( false);
		sprite3D[i] -> setScale( 3.0f);
		sprite3D[i] -> setPosition3D( Vec3( 0, 0, 0));
		sprite3D[i] -> setRotation3D( Vec3( 180, 0, 0));
	}
}

void Muzzle::update( void)
{
	if( shotFlag)
	{
		if( count > 4) count = 0;

		switch( count)
		{
		case 0:
			sprite3D[4] -> setVisible( false);
			sprite3D[0] -> setVisible( true);
			break;
		case 1:
			sprite3D[0] -> setVisible( false);
			sprite3D[1] -> setVisible( true);
			break;
		case 2:
			sprite3D[1] -> setVisible( false);
			sprite3D[2] -> setVisible( true);
			break;
		case 3:
			sprite3D[2] -> setVisible( false);
			sprite3D[3] -> setVisible( true);
			break;
		case 4:
			sprite3D[3] -> setVisible( false);
			sprite3D[4] -> setVisible( true);
			break;
		default:
			break;
		}
		count++;
	}
	else
	{
		for( auto &p : sprite3D) { p -> setVisible( false); }
	}
}

void Muzzle::flagOn( void) { shotFlag = true; }

void Muzzle::flagOff( void) { shotFlag = false; }

void P_Muzzle::createMuzzle( _Sprite3D* parentData)
{
	auto point = parentData -> getAttachNode( "po_");
	for( auto &p : sprite3D) { point -> addChild( p); }
}

void E_Muzzle::createMuzzle( _Sprite3D* parentData)
{
	muzzleR = new Muzzle();
	muzzleL = new Muzzle();

	for( int i = 1; i < 5; i++)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		muzzleR -> sprite3D[i] -> setTexture( "tex_mazuruE.png");
		muzzleL -> sprite3D[i] -> setTexture( "tex_mazuruE.png");
#else
		muzzleR -> sprite3D[i] -> setTextrue( "Graph/Models/tex_mazuruE.png");
		muzzleL -> sprite3D[i] -> setTextrue( "Graph/Models/tex_mazuruE.png");
#endif
		auto point = parentData -> getAttachNode( "po_1");
		point -> addChild( muzzleR -> sprite3D[i]);
		point = parentData -> getAttachNode( "po_2");
		point -> addChild( muzzleL -> sprite3D[i]);
	}
}

void E_Muzzle::update( void)
{
	muzzleR -> update();
	muzzleL -> update();
}

void E_Muzzle::flagOn( void)
{
	muzzleR -> flagOn();
	muzzleL -> flagOn();
}

void E_Muzzle::flagOff( void)
{
	muzzleR -> flagOff();
	muzzleL -> flagOff();
}


#include "cocos2d.h"
#include "Muzzle.h"

USING_NS_CC;
using namespace std;
using namespace TapGun;

Muzzle* Muzzle::createMuzzle( _Sprite3D* parentData, string pointName)
{
	auto p = new Muzzle();
	auto point = parentData -> getAttachNode( pointName);
	if( !point) { return nullptr; }
	for( int i = 0; i < MUZZLE_COUNT; i++)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		auto str = __String::createWithFormat( "muzzle%i.c3t", i + 1);
#else
		auto str = __String::createWithFormat( "Muzzle/muzzle%i.c3t", i + 1);
#endif
		p -> sprite3D[i] = _Sprite3D::create( str -> getCString());
		p -> sprite3D[i] -> setVisible( false);
//		p -> sprite3D[i] -> setScale( 3.0f);
		p -> sprite3D[i] -> setPosition3D( Vec3( 0, 0, 0));
		p -> sprite3D[i] -> setRotation3D( Vec3( 90, 0, 180));
		point -> addChild( p -> sprite3D[i]);
	}
	return p;
}

void Muzzle::setMuzzleAction( void) { shotFlag = true; }

void Muzzle::muzzleUpdate( void)
{
	if( shotFlag)
	{
		if( count == MUZZLE_COUNT - 1)
		{
			shotFlag = false;
			count = 0;
			for( auto &p : sprite3D) { p -> setVisible( false); }
			return;
		}

		switch( count)
		{
		case 0:
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
		default:
			break;
		}
		count++;
	}
}

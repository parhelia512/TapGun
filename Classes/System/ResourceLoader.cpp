
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"
#include "ResourceLoader.h"

#else

#include "Base/Sprite3D.h"
#include "System/ResourceLoader.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

ResourceLoader* ResourceLoader::getInstance( void)
{
	static ResourceLoader* p = nullptr;
	if( p == nullptr) { p = new ResourceLoader(); }
	return p;
}

void ResourceLoader::loadModel( const string& fileName)
{
	_Sprite3D::createAsync( fileName, CC_CALLBACK_2( ResourceLoader::sprite3DLoadCallback, this, fileName), nullptr);
}

void ResourceLoader::loadModel( const string& modelPath, const string& texturePath)
{
	_Sprite3D::createAsync( modelPath, texturePath, CC_CALLBACK_2( ResourceLoader::sprite3DLoadCallback, this, modelPath), nullptr);
}

void ResourceLoader::loadModel( const string& modelPath, const string& texturePath, const string& animaPath)
{
	_Sprite3D::createAsync( modelPath, texturePath, animaPath, CC_CALLBACK_2( ResourceLoader::sprite3DLoadCallback, this, modelPath), nullptr);
}

_Sprite3D* ResourceLoader::getSprite3D( int count)
{
	if( loadFlag[count] == true) { return models[count]; }
	else { return nullptr; }
}

void ResourceLoader::sprite3DLoadCallback( _Sprite3D* sprite3D, void* param, const string& fileName)
{
	static int count[4] = { Map, EnemyStart, BulletStart, Player };
	string str = fileName;

	int point = str.rfind( '/', str.size());
	str.erase( 0, str.size() - ( str.size() - point) + 1);

	point = str.rfind( '.', str.size());
	if( point > 0) { str.erase( str.size() - ( str.size() - point), str.size()); }

	if( str == "map507")
	{
		loadFlag[count[0]] = true;
		models[count[0]] = sprite3D;
		models[count[0]] -> retain();
	}
	else if( str == "enemy")
	{
		loadFlag[count[1]] = true;
		models[count[1]] = sprite3D;
		models[count[1]] -> retain();
		count[1]++;
	}
	else if( str == "tama")
	{
		loadFlag[count[2]] = true;
		models[count[2]] = sprite3D;
		models[count[2]] -> retain();
		count[2]++;
	}
	else if( str == "player")
	{
		loadFlag[count[3]] = true;
		models[count[3]] = sprite3D;
		models[count[3]] -> retain();
	}
	else
	{
		log( "3DModelFileLoadError : FileName LoadPath no math");
	}

	
}


#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Directory.h"

#else

#include "C++/System/Directory.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

Directory* Directory::getInstance( void)
{
	static Directory* P;
	if( !P) P = new Directory;
	return P;
}

map< int, string> Directory::searchModelFile( const string& keyName)
{
	return searchResourceFile( keyName.c_str());
}

map< int, string> Directory::searchTextureFile( const string& keyName)
{
	return searchResourceFile( keyName.c_str());
}

map< int, string> Directory::searchResourceFile( const char* keyName)
{
	map< int, string> str;
	FileUtils* fu = FileUtils::getInstance();

	str[0] = fu -> fullPathForFilename( "Graph/Models/test.c3t");

	return str;
}

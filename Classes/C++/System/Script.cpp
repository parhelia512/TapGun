
#include <iostream>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Script.h"
#include "Errorfunc.h"

#else

#include "C++/System/Script.h"
#include "C++/System/Errorfunc.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

/**
 *	スクリプトファイルの読み込みと設定（未完成）
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0 エラー発生:-1
 *	@date	12/28 Ver 0.1
 */
int Script::loadScriptFile( const std::string& fileName)
{
	char *error;
	string str;
	string command;
	string parameter;
	istringstream stream(str);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	string filePass = fileName + ".script";
#else
	string filePass = "Script/" + fileName + ".script";
#endif

	file.open( filePass, ios::in);

	if( file.fail())
	{
		return -1;
	}

	getline( file, str);
	getline( stream, command, ',');
	getline( stream, parameter);

}

int Script::loadCommand( int index)
{
	return 0;
}


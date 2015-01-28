
#include <iostream>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Errorfunc.h"
#include "Script.h"
#include "Sound.h"

#else

#include "C++/System/Errorfunc.h"
#include "C++/System/Script.h"
#include "C++/System/Sound.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

/**
*	スクリプト管理クラスのインスタンス取得
*
*	@author	minaka
*	@param	fileName ファイル名
*	@return	正常終了:0 エラー発生:-1
*	@date	1/7 Ver 1.0
*/
Script* Script::getInstance( void)
{
	static Script* P;
	if( !P) P = new Script;
	return P;
}

/**
*	スクリプトファイルの読み込みと設定
*
*	@author	minaka
*	@param	fileName ファイル名
*	@param	layer 描画設定するレイヤー
*	@return	エラーメッセージ
*	@date	1/8 Ver 1.0
*/
string Script::loadScriptFile( const string& fileName, Layer* layer)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	string filePath = fileName + ".script";
	#else
	string filePath = "Script/" + fileName + ".script";
	#endif
	ifstream file( filePath, ios::in);
	if( file.fail())
	{
		string error = "スクリプトファイルが開けません ファイル:" + fileName;
		return error;
	}

	string str;
	lineCounter = 0;
	while( getline( file, str))
	{
		lineCounter++;
		string tmp;
		istringstream stream( str);
		getline( stream, tmp, ',');
		if( tmp == "Create" || tmp == "create")
		{
			string s = str;
			s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
			functionNameCreate( s);
		}
		else if( tmp == "Anime" || tmp == "anime")
	{
		string s = str;
		s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
		functionNameAnime( s);
	}
	else if( tmp == "Print" || tmp == "print")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNamePrint( s, layer);
}
else if( tmp == "Clear" || tmp == "clear")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNameClear( s);
}
else if( tmp == "Delete" || tmp == "delete")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNameDelete( s);
}
else if( tmp == "Play" || tmp == "play")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNamePlay( s);
}
else if( tmp == "Stop" || tmp == "stop")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNameStop( s);
}
else if( tmp == "Pause" || tmp == "pause")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNamePause( s);
}
else if( tmp == "Resume" || tmp == "resume")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNameResume( s);
}
else if( tmp == "StopAll" || tmp == "stopAll")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNameStopAll( s);
}
else if( tmp == "PauseAll" || tmp == "pauseAll")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNamePauseAll( s);
}
else if( tmp == "ResumeAll" || tmp == "resumeAll")
{
	string s = str;
	s.erase( 0, s.size() - ( s.size() - ( tmp.size() + 1)));
	functionNameResumeAll( s);
}
else
{
	string error = tmp + "この命令は未実装です ";
	string s = lineCounter + "行目 ファイル:" + fileName;;
	error = error + s;
	return error;
}
}
}

string Script::functionNameCreate( const string& scriptText)
{
	FileNameFlag flag;
	string str;
	string command;
	string fileName = scriptText;
	int point = fileName.rfind( '.', fileName.size());

	if( point == string::npos)
	{
		flag = FileNameFlag::Text;
	}
	fileName.erase( 0, fileName.size() - ( fileName.size() - point));
	if( fileName == ".png" || fileName == ".jpg" || fileName == ".bmp")
	{
		flag = FileNameFlag::Picture;
	}
	else if( fileName == ".obj" || fileName == ".c3t" || fileName == ".c3b")
{
	flag = FileNameFlag::Model;
}
else if( fileName == ".mp3" || fileName == ".wav")
{
	flag = FileNameFlag::Sound;
}
else
{
	string error = "スクリプトで指定されたファイルは読み込めません " + lineCounter;
	error = error + "行目 ファイル:" + fileName;
	return error;
}

istringstream stream( str);

if( flag == FileNameFlag::Sound)
{
	auto data = new InputSoundData;
	auto sound = Sound::getInstance();
	for( int i = 0; str.size() > 0; i++)
	{
		getline( stream, command, ',');
		str.erase( 0, str.size() - ( str.size() - ( command.size() + 1)));
		if( *str.data() == ',') break; // ','が2個繋がっていた場合、処理終了

			if( i == 0)
			{
				data -> dataName = command;
			}
			else
			{
				// Tag or Pos
				if( *command.data() == '#' )//|| *command.data() == '＃')
				{
					command.erase( 0, 1);
					data -> tag = command;
				}
				else
				{
					break;
				}
			}
		}
		sound -> loadSE( data -> dataName);
		soundList.push_back( data);
	}
	else
	{
		auto data = new InputSpriteData;
		for( int i = 0; str.size() > 0; i++)
		{
			getline( stream, command, ',');
			str.erase( 0, str.size() - ( str.size() - ( command.size() + 1)));
			if( *str.data() == ',') break; // ','が2個繋がっていた場合、処理終了

				if( i == 0)
				{
					data -> dataName = command;
				}
				else
				{
					if( *command.data() == '#')// || *command.data() == '＃')
					{
						command.erase( 0, 1);
						data -> tag = command;
					}
					else if( command.find( "posX", 0) != string::npos || command.find( "PosX", 0) != string::npos)
				{
					command.erase( 0, 5);
					data -> position.x = atof( command.c_str());
				}
				else if( command.find( "posY", 0) != string::npos || command.find( "PosY", 0) != string::npos)
			{
				command.erase( 0, 5);
				data -> position.y = atof( command.c_str());
			}
			else if( command.find( "posZ", 0) != string::npos || command.find( "PosZ", 0) != string::npos)
		{
			command.erase( 0, 5);
			data -> position.z = atof( command.c_str());
		}
		else if( command.find( "layer", 0) != string::npos || command.find( "Layer", 0) != string::npos)
	{
		command.erase( 0, 6);
		data -> layerNumber = atof( command.c_str());
	}
	else
	{
		break;
	}
}
}

switch( flag)
{
	case FileNameFlag::Text:
{
	auto sprite = LabelTTF::create( data -> dataName, "Arial", 20);
	sprite -> setPosition( Vec2( data -> position.x, data -> position.y));
	//			layer -> addChild( sprite, data -> layerNumber);
	break;
}
case FileNameFlag::Picture:
{
	auto sprite = Sprite::create( data -> dataName);
	sprite -> setPosition( Vec2( data -> position.x, data -> position.y));
	//			layer -> addChild( sprite, data -> layerNumber);
	break;
}
case FileNameFlag::Model:
{
	auto sprite = Sprite3D::create( data -> dataName);

	sprite -> setPosition3D( data -> position);
	//			layer -> addChild( sprite, data -> layerNumber);
	break;
}
default:
auto sprite = nullptr;
break;
};
spriteList.push_back( data);
}
}

string Script::functionNameAnime( const string& scriptText)
{
	return 0;
}

string Script::functionNamePrint( const string& scriptText, Layer* layer)
{
	return 0;
}

string Script::functionNameClear( const string& scriptText)
{
	return 0;
}

string Script::functionNameDelete( const string& scriptText)
{
	return 0;
}

string Script::functionNamePlay( const string& scriptText)
{
	return 0;
}

string Script::functionNameStop( const string& scriptText)
{
	return 0;
}

string Script::functionNamePause( const string& scriptText)
{
	return 0;
}

string Script::functionNameResume( const string& scriptText)
{
	return 0;
}

string Script::functionNameStopAll( const string& scriptText)
{
	return 0;
}

string Script::functionNamePauseAll( const string& scriptText)
{
	return 0;
}

string Script::functionNameResumeAll( const string& scriptText)
{
	return 0;
}

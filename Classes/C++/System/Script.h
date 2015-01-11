
#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <fstream>

namespace TapGun
{

struct InputSpriteData;
struct InputSoundData;
struct TimeSheet;
class Script 
{
public:
	Script( const Script& p) = delete;	
	Script& operator=( const Script& P) = delete;
	static Script* getInstance( void);

	std::string loadScriptFile( const std::string& fileName,  cocos2d::Layer* layer);
	int updateScriptFunction( void);
	void releaseScriptData( void);

private:
	int lineCounter;
	std::ifstream file;
	std::vector<InputSpriteData*> spriteList;
	std::vector<InputSoundData*> soundList;
	std::vector<TimeSheet*> timeList;

	Script() {}
	std::string functionNameCreate( const std::string& scriptText);
	std::string functionNameAnime( const std::string& scriptText);
	std::string functionNamePrint( const std::string& scriptText, cocos2d::Layer* layer);
	std::string functionNameClear( const std::string& scriptText);
	std::string functionNameDelete( const std::string& scriptText);
	std::string functionNamePlay( const std::string& scriptText);
	std::string functionNameStop( const std::string& scriptText);
	std::string functionNamePause( const std::string& scriptText);
	std::string functionNameResume( const std::string& scriptText);
	std::string functionNameStopAll( const std::string& scriptText);
	std::string functionNamePauseAll( const std::string& scriptText);
	std::string functionNameResumeAll( const std::string& scriptText);
};

enum FileNameFlag
{
	Text,
	Picture,
	Model,
	Sound,
};

struct InputSpriteData
{
	bool animeLoopFlag;
	int layerNumber;
	std::string tag;
	std::string dataName;
	cocos2d::Vec3 position;
};

struct InputSoundData
{
	bool LoopFlag;
	std::string tag;
	std::string dataName;
};

struct TimeSheet
{
	float startTime;
	float endTime;
	std::string tag;
	std::string dataName;
};

}

#endif // __SCRIPT_H__

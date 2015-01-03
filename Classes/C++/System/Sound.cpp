
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sound.h"

#else

#include "C++/System/Sound.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

Sound* Sound::getInstance( void)
{
	static Sound* P;
	if( !P) P = new Sound;
	return P;
}

int Sound::loadBGM( const string& fileName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Sound::getInstance() -> bgmFileName = fileName;
#else
	Sound::getInstance() -> bgmFileName = "Sound/BGM/" + fileName;
#endif
	SimpleAudioEngine::getInstance() -> preloadBackgroundMusic( Sound::getInstance() -> bgmFileName.c_str());
	return 0;
}

int Sound::loadBGM( const string& fileName, float Volume)
{
	Sound::getInstance() -> loadBGM( fileName);
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	return 0;
}

int Sound::playBGM( void)
{
	string str = Sound::getInstance() -> bgmFileName;
	if( str.length() != NULL)
	{
		SimpleAudioEngine::getInstance() -> playBackgroundMusic( str.c_str(), false);
		return 0;
	}
	return -1;
}

int Sound::playBGM( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	Sound::getInstance() -> playBGM();
	return 0;
}
	
int Sound::playBGMLoop( void)
{
	string str = Sound::getInstance() -> bgmFileName;
	if( str.length() != NULL)
	{
		SimpleAudioEngine::getInstance() -> playBackgroundMusic( str.c_str(), true);
		return 0;
	}
	return -1;
}

int Sound::playBGMLoop( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	Sound::getInstance() -> playBGMLoop();
	return 0;
}

int Sound::setBGMVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	return 0;
}

int Sound::stopBGM( void)
{
	SimpleAudioEngine::getInstance() -> stopBackgroundMusic();
	return 0;
}

int Sound::pauseBGM( void)
{
	SimpleAudioEngine::getInstance() -> pauseBackgroundMusic();
	return 0;
}

int Sound::resumeBGM( void)
{
	SimpleAudioEngine::getInstance() -> resumeBackgroundMusic();
	return 0;
}

int Sound::restartBGM( void)
{
	SimpleAudioEngine::sharedEngine() -> rewindBackgroundMusic();
	return 0;
}

int Sound::playCheckBGM( void)
{
	if( SimpleAudioEngine::sharedEngine() -> isBackgroundMusicPlaying())
	{
		return 1;		// Ä¶’†
	}
	else
	{
		return 0;
	}
}
	
int Sound::releaseBGM( void)
{
	// –¢ŽÀ‘•
	return 0;
}

int Sound::loadSE( const std::string& fileName)
{
	SoundData *data = new SoundData;
	data -> fileName = fileName;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	data -> filePath = fileName;
#else
	data -> filePath = "Sound/SE/" + fileName;
#endif
	SimpleAudioEngine::getInstance() -> preloadEffect( data -> filePath.c_str());
	seDataList.push_back( data);
	data -> ID = seDataList.size() - 1;
	return 0;
}

int Sound::loadSE( const std::string& fileName, float Volume)
{
	Sound::getInstance() -> loadSE( fileName);
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

int Sound::playSE( const std::string& fileName)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		if( seDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> playEffect( seDataList[i] -> filePath.c_str());
			return 0;
		}
	}
	return -1;
}

int Sound::playSE( const std::string& fileName, float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	Sound::getInstance() -> playSE( fileName);
	return 0;
}

int Sound::setSEVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

int Sound::stopSE( const std::string& fileName)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		if( seDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> stopEffect( seDataList[i] -> ID);
			return 0;
		}
	}
	return -1;
}

int Sound::pauseSE( const std::string& fileName)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		if( seDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> pauseEffect( seDataList[i] -> ID);
			return 0;
		}
	}
	return -1;
}

int Sound::resumeSE( const std::string& fileName)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		if( seDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> pauseEffect( seDataList[i] -> ID);
			return 0;
		}
	}
	return -1;
}

int Sound::stopSEAll( void)
{
	SimpleAudioEngine::getInstance() -> stopAllEffects();
	return 0;
}

int Sound::pauseSEAll( void)
{
	SimpleAudioEngine::getInstance() -> pauseAllEffects();
	return 0;
}

int Sound::resumeSEAll( void)
{
	SimpleAudioEngine::getInstance() -> resumeAllEffects();
	return 0;
}

int Sound::releaseSE( const std::string& fileName)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		if( seDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> unloadEffect( seDataList[i] -> filePath.c_str());
			return 0;
		}
	}	
	return -1;
}

int Sound::releaseSEAll( void)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		SimpleAudioEngine::getInstance() -> unloadEffect( seDataList[i] -> filePath.c_str());
	}
	vector<SoundData*>().swap(seDataList);
	return 0;
}

int Sound::loadVoice( const std::string& fileName)
{
	SoundData *data = new SoundData;
	data -> fileName = fileName;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	data -> filePath = fileName;
#else
	data -> filePath = "Sound/Voice/" + fileName;
#endif
	SimpleAudioEngine::getInstance() -> preloadEffect( data -> filePath.c_str());
	voiceDataList.push_back( data);
	data -> ID = voiceDataList.size() - 1;
	return 0;
}

int Sound::loadVoice( const std::string& fileName, float Volume)
{
	Sound::getInstance() -> loadVoice( fileName);
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

int Sound::playVoice( const std::string& fileName)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		if( voiceDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> playEffect( voiceDataList[i] -> filePath.c_str());
			return 0;
		}
	}
	return -1;
}

int Sound::playVoice( const std::string& fileName, float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	Sound::getInstance() -> playVoice( fileName);
	return 0;
}

int Sound::setVoiceVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

int Sound::stopVoice( const std::string& fileName)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		if( voiceDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> stopEffect( voiceDataList[i] -> ID);
			return 0;
		}
	}
	return -1;
}

int Sound::pauseVoice( const std::string& fileName)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		if( voiceDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> pauseEffect( voiceDataList[i] -> ID);
			return 0;
		}
	}
	return -1;
}

int Sound::resumeVoice( const std::string& fileName)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		if( voiceDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> pauseEffect( voiceDataList[i] -> ID);
			return 0;
		}
	}
	return -1;
}

int Sound::stopVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> stopAllEffects();
	return 0;
}

int Sound::pauseVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> pauseAllEffects();
	return 0;
}

int Sound::resumeVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> resumeAllEffects();
	return 0;
}

int Sound::releaseVoice( const std::string& fileName)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		if( voiceDataList[i] -> fileName == fileName)
		{
			SimpleAudioEngine::getInstance() -> unloadEffect( voiceDataList[i] -> filePath.c_str());
			return 0;
		}
	}	
	return -1;
}

int Sound::releaseVoiceAll( void)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		SimpleAudioEngine::getInstance() -> unloadEffect( voiceDataList[i] -> filePath.c_str());
	}
	vector<SoundData*>().swap(voiceDataList);
	return 0;
}


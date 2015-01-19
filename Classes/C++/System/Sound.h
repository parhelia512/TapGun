
#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"

namespace TapGun
{
	struct SoundData
	{
		int ID;
		std::string fileName;
		std::string filePath;
	};
	
	class Sound
	{
	public:
		Sound( const Sound &P) = delete;
		Sound& operator= ( const Sound &P) = delete;
		static Sound* getInstance( void);

		int loadBGM( const std::string& fileName);
		int loadBGM( const std::string& fileName, float Volume);
		int playBGM( void);
		int playBGM( float Volume);
		int playBGMLoop( void);
		int playBGMLoop( float Volume);
		int setBGMVolume( float Volume);
		int stopBGM( void);
		int pauseBGM( void);
		int resumeBGM( void);
		int restartBGM( void);
		int playCheckBGM( void);
		int releaseBGM( void);

		int loadSE( const std::string& fileName);
		int loadSE( const std::string& fileName, float Volume);
		int playSE( const std::string& fileName);
		int playSE( const std::string& fileName, float Volume);
		int setSEVolume( float Volume);
		int stopSE( const std::string& fileName);
		int pauseSE( const std::string& fileName);
		int resumeSE( const std::string& fileName);
		int stopSEAll( void);
		int pauseSEAll( void);
		int resumeSEAll( void);
		int releaseSE( const std::string& fileName);
		int releaseSEAll( void);

		int loadVoice( const std::string& fileName);
		int loadVoice( const std::string& fileName, float Volume);
		int playVoice( const std::string& fileName);
		int playVoice( const std::string& fileName, float Volume);
		int setVoiceVolume( float Volume);
		int stopVoice( const std::string& fileName);
		int pauseVoice( const std::string& fileName);
		int resumeVoice( const std::string& fileName);
		int stopVoiceAll( void);
		int pauseVoiceAll( void);
		int resumeVoiceAll( void);
		int releaseVoice( const std::string& fileName);
		int releaseVoiceAll( void);

	private:
		std::string bgmFileName;
		std::vector<SoundData*> seDataList;
		std::vector<SoundData*> voiceDataList;
		Sound() {}

	};
}

#endif // __SOUND_H__

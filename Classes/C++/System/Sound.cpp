
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

/**
 *	サウンド管理クラスのインスタンス取得
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0 エラー発生:-1
 *	@date	12/28 Ver 1.0
 */
Sound* Sound::getInstance( void)
{
	static Sound* P;
	if( !P) P = new Sound;
	return P;
}

/**
 *	BGMファイルの読み込み
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	BGMファイルの読み込み（ボリューム調整付き）
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::loadBGM( const string& fileName, float Volume)
{
	Sound::getInstance() -> loadBGM( fileName);
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	return 0;
}

/**
 *	BGMの再生
 *
 *	@author	minaka 
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playBGM( void)
{
	string str = Sound::getInstance() -> bgmFileName;
	if( str.length() != NULL && !Sound::getInstance() -> playCheckBGM())
	{
		SimpleAudioEngine::getInstance() -> playBackgroundMusic( str.c_str(), false);
		return 0;
	}
	return -1;
}

/**
 *	BGMの再生（ボリューム調整付き）
 *
 *	@author	minaka
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playBGM( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	Sound::getInstance() -> playBGM();
	return 0;
}

/**
 *	BGMのループ再生
 *
 *	@author	minaka 
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	BGMのループ再生（ボリューム調整付き）
 *
 *	@author	minaka
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playBGMLoop( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	Sound::getInstance() -> playBGMLoop();
	return 0;
}

/**
 *	BGMのボリューム設定
 *
 *	@author	minaka
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::setBGMVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	return 0;
}

/**
 *	BGMの停止
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::stopBGM( void)
{
	SimpleAudioEngine::getInstance() -> stopBackgroundMusic();
	return 0;
}

/**
 *	BGMの一時停止
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::pauseBGM( void)
{
	SimpleAudioEngine::getInstance() -> pauseBackgroundMusic();
	return 0;
}

/**
 *	BGMの再開
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::resumeBGM( void)
{
	SimpleAudioEngine::getInstance() -> resumeBackgroundMusic();
	return 0;
}

/**
 *	BGMのリスタート
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::restartBGM( void)
{
	SimpleAudioEngine::sharedEngine() -> rewindBackgroundMusic();
	return 0;
}


/**
 *	BGMの再生中チェック
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playCheckBGM( void)
{
	if( SimpleAudioEngine::sharedEngine() -> isBackgroundMusicPlaying())
	{
		return 1;		// 再生中
	}
	else
	{
		return 0;
	}
}
	

/**
 *	BGM用メモリの解放（未実装）
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::releaseBGM( void)
{
	// 未実装
	return 0;
}

/**
 *	SEファイルの読み込み
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	SEファイルの読み込み（ボリューム調整付き）
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::loadSE( const std::string& fileName, float Volume)
{
	Sound::getInstance() -> loadSE( fileName);
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	SEの再生
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	SEの再生（ボリューム調整付き）
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playSE( const std::string& fileName, float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	Sound::getInstance() -> playSE( fileName);
	return 0;
}

/**
 *	SE全体のボリューム調整
 *
 *	@author	minaka 
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::setSEVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	SEの停止
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	SEの再開
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	SEのリスタート
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	全SEの停止
 *		※この停止命令はVoiceと共有
 *	@author	minaka 
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::stopSEAll( void)
{
	SimpleAudioEngine::getInstance() -> stopAllEffects();
	return 0;
}

/**
 *	全SEの再開
 *		※この停止命令はVoiceと共有
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::pauseSEAll( void)
{
	SimpleAudioEngine::getInstance() -> pauseAllEffects();
	return 0;
}

/**
 *	全SEのリスタート
 *		※この停止命令はVoiceと共有
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::resumeSEAll( void)
{
	SimpleAudioEngine::getInstance() -> resumeAllEffects();
	return 0;
}

/**
 *	SE用のメモリ解放
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	全SE用のメモリ解放
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::releaseSEAll( void)
{
	for( int i = 0; i < seDataList.size(); i++)
	{
		SimpleAudioEngine::getInstance() -> unloadEffect( seDataList[i] -> filePath.c_str());
	}
	vector<SoundData*>().swap(seDataList);
	return 0;
}

/**
 *	Voiceファイルの読み込み
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	Voiceファイルの読み込み（ボリューム調整付き）
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::loadVoice( const std::string& fileName, float Volume)
{
	Sound::getInstance() -> loadVoice( fileName);
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	Voiceファイルの再生
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	Voiceファイルの読み込み（ボリューム調整付き）
 *
 *	@author	minaka 
 *	@param	fileName ファイル名
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playVoice( const std::string& fileName, float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	Sound::getInstance() -> playVoice( fileName);
	return 0;
}

/**
 *	Voice全体のボリューム調整
 *		※ボリュームレベルはSEと共有
 *	@author	minaka
 *	@param	Volume ボリュームレベル ( 0.0 ~ 100.0 )
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::setVoiceVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	Voiceの停止
 *		
 *	@author	minaka
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	Voiceの再開
 *		
 *	@author	minaka
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	Voiceのリスタート
 *		
 *	@author	minaka
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	全Voiceの停止
 *		※この停止命令はSEと共有	
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::stopVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> stopAllEffects();
	return 0;
}

/**
 *	全Voiceの再開
 *		※この再開命令はSEと共有	
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::pauseVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> pauseAllEffects();
	return 0;
}

/**
 *	全Voiceのリスタート
 *		※このリスタート命令はSEと共有	
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::resumeVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> resumeAllEffects();
	return 0;
}

/**
 *	Voice用のメモリ解放
 *
 *	@author	minaka
 *	@param	fileName ファイル名
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
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

/**
 *	全Voice用のメモリ解放
 *
 *	@author	minaka
 *	@return	正常終了:0
 *	@date	1/4 Ver 1.0
 */
int Sound::releaseVoiceAll( void)
{
	for( int i = 0; i < voiceDataList.size(); i++)
	{
		SimpleAudioEngine::getInstance() -> unloadEffect( voiceDataList[i] -> filePath.c_str());
	}
	vector<SoundData*>().swap(voiceDataList);
	return 0;
}


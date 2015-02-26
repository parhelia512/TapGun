
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sound.h"

#else

#include "System/Sound.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;
using namespace CocosDenshion;

/**
 *	�T�E���h�Ǘ��N���X�̃C���X�^���X�擾
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0 �G���[����:-1
 *	@date	12/28 Ver 1.0
 */
Sound* Sound::getInstance( void)
{
	static Sound* P;
	if( !P) P = new Sound;
	return P;
}

/**
 *	BGM�t�@�C���̓ǂݍ���
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	BGM�t�@�C���̓ǂݍ��݁i�{�����[�������t���j
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::loadBGM( const string& fileName, float Volume)
{
	Sound::getInstance() -> loadBGM( fileName);
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	return 0;
}

/**
 *	BGM�̍Đ�
 *
 *	@author	minaka 
 *	@return	����I��:0
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
 *	BGM�̍Đ��i�{�����[�������t���j
 *
 *	@author	minaka
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playBGM( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	Sound::getInstance() -> playBGM();
	return 0;
}

/**
 *	BGM�̃��[�v�Đ�
 *
 *	@author	minaka 
 *	@return	����I��:0
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
 *	BGM�̃��[�v�Đ��i�{�����[�������t���j
 *
 *	@author	minaka
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playBGMLoop( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	Sound::getInstance() -> playBGMLoop();
	return 0;
}

/**
 *	BGM�̃{�����[���ݒ�
 *
 *	@author	minaka
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::setBGMVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setBackgroundMusicVolume( ( Volume / 100));
	return 0;
}

/**
 *	BGM�̒�~
 *
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::stopBGM( void)
{
	SimpleAudioEngine::getInstance() -> stopBackgroundMusic();
	return 0;
}

/**
 *	BGM�̈ꎞ��~
 *
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::pauseBGM( void)
{
	SimpleAudioEngine::getInstance() -> pauseBackgroundMusic();
	return 0;
}

/**
 *	BGM�̍ĊJ
 *
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::resumeBGM( void)
{
	SimpleAudioEngine::getInstance() -> resumeBackgroundMusic();
	return 0;
}

/**
 *	BGM�̃��X�^�[�g
 *
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::restartBGM( void)
{
	SimpleAudioEngine::sharedEngine() -> rewindBackgroundMusic();
	return 0;
}


/**
 *	BGM�̍Đ����`�F�b�N
 *
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playCheckBGM( void)
{
	if( SimpleAudioEngine::sharedEngine() -> isBackgroundMusicPlaying())
	{
		return 1;		// �Đ���
	}
	else
	{
		return 0;
	}
}
	

/**
 *	BGM�p�������̉���i�������j
 *
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::releaseBGM( void)
{
	// ������
	return 0;
}

/**
 *	SE�t�@�C���̓ǂݍ���
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	SE�t�@�C���̓ǂݍ��݁i�{�����[�������t���j
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::loadSE( const std::string& fileName, float Volume)
{
	Sound::getInstance() -> loadSE( fileName);
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	SE�̍Đ�
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	SE�̍Đ��i�{�����[�������t���j
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playSE( const std::string& fileName, float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	Sound::getInstance() -> playSE( fileName);
	return 0;
}

/**
 *	SE�S�̂̃{�����[������
 *
 *	@author	minaka 
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::setSEVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	SE�̒�~
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	SE�̍ĊJ
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	SE�̃��X�^�[�g
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	�SSE�̒�~
 *		�����̒�~���߂�Voice�Ƌ��L
 *	@author	minaka 
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::stopSEAll( void)
{
	SimpleAudioEngine::getInstance() -> stopAllEffects();
	return 0;
}

/**
 *	�SSE�̍ĊJ
 *		�����̒�~���߂�Voice�Ƌ��L
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::pauseSEAll( void)
{
	SimpleAudioEngine::getInstance() -> pauseAllEffects();
	return 0;
}

/**
 *	�SSE�̃��X�^�[�g
 *		�����̒�~���߂�Voice�Ƌ��L
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::resumeSEAll( void)
{
	SimpleAudioEngine::getInstance() -> resumeAllEffects();
	return 0;
}

/**
 *	SE�p�̃��������
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	�SSE�p�̃��������
 *
 *	@author	minaka
 *	@return	����I��:0
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
 *	Voice�t�@�C���̓ǂݍ���
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	Voice�t�@�C���̓ǂݍ��݁i�{�����[�������t���j
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::loadVoice( const std::string& fileName, float Volume)
{
	Sound::getInstance() -> loadVoice( fileName);
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	Voice�t�@�C���̍Đ�
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	Voice�t�@�C���̓ǂݍ��݁i�{�����[�������t���j
 *
 *	@author	minaka 
 *	@param	fileName �t�@�C����
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::playVoice( const std::string& fileName, float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	Sound::getInstance() -> playVoice( fileName);
	return 0;
}

/**
 *	Voice�S�̂̃{�����[������
 *		���{�����[�����x����SE�Ƌ��L
 *	@author	minaka
 *	@param	Volume �{�����[�����x�� ( 0.0 ~ 100.0 )
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::setVoiceVolume( float Volume)
{
	SimpleAudioEngine::getInstance() -> setEffectsVolume( ( Volume / 100));
	return 0;
}

/**
 *	Voice�̒�~
 *		
 *	@author	minaka
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	Voice�̍ĊJ
 *		
 *	@author	minaka
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	Voice�̃��X�^�[�g
 *		
 *	@author	minaka
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	�SVoice�̒�~
 *		�����̒�~���߂�SE�Ƌ��L	
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::stopVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> stopAllEffects();
	return 0;
}

/**
 *	�SVoice�̍ĊJ
 *		�����̍ĊJ���߂�SE�Ƌ��L	
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::pauseVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> pauseAllEffects();
	return 0;
}

/**
 *	�SVoice�̃��X�^�[�g
 *		�����̃��X�^�[�g���߂�SE�Ƌ��L	
 *	@author	minaka
 *	@return	����I��:0
 *	@date	1/4 Ver 1.0
 */
int Sound::resumeVoiceAll( void)
{
	SimpleAudioEngine::getInstance() -> resumeAllEffects();
	return 0;
}

/**
 *	Voice�p�̃��������
 *
 *	@author	minaka
 *	@param	fileName �t�@�C����
 *	@return	����I��:0
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
 *	�SVoice�p�̃��������
 *
 *	@author	minaka
 *	@return	����I��:0
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


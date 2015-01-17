
#include <fstream>
//#include <string>
//#include <iostream>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "C++/Base/Sprite3D.h"

#endif

using namespace std;
<<<<<<< HEAD

namespace TapGun
{
	/**
	 *	3DƒXƒvƒ‰ƒCƒg‚Ìì¬	
	 *
	 *	@author	minaka
	 *	@param	firstPath ƒŠƒ\[ƒXƒtƒ@ƒCƒ‹–¼
	 *	@return	ì¬‚µ‚½ƒXƒvƒ‰ƒCƒg‚Ö‚Ìƒ|ƒCƒ“ƒ^
	 *	@date	1/3	Ver 1.0
	 */
	Sprite3D* Sprite3D::create( char* firstPath)
	{
		return createObject( firstPath, nullptr, nullptr);
	}

	/**
	 *	3DƒXƒvƒ‰ƒCƒg‚Ìì¬	
	 *
	 *	@author	minaka
	 *	@param	firstPath ƒŠƒ\[ƒXƒtƒ@ƒCƒ‹–¼
	 *	@param	secondPath ƒŠƒ\[ƒXƒtƒ@ƒCƒ‹–¼
	 *	@return	ì¬‚µ‚½ƒXƒvƒ‰ƒCƒg‚Ö‚Ìƒ|ƒCƒ“ƒ^
	 *	@date	1/3	Ver 1.0
	 */
	Sprite3D* Sprite3D::create( char* firstPath, char* secondPath)
	{
		return createObject( firstPath, secondPath, nullptr);
	}

	/**
	 *	3DƒXƒvƒ‰ƒCƒg‚Ìì¬	
	 *
	 *	@author	minaka
	 *	@param	firstPath ƒŠƒ\[ƒXƒtƒ@ƒCƒ‹–¼
	 *	@param	secondPath ƒŠƒ\[ƒXƒtƒ@ƒCƒ‹–¼
	 *	@param	thirdPath ƒŠƒ\[ƒXƒtƒ@ƒCƒ‹–¼
	 *	@return	ì¬‚µ‚½ƒXƒvƒ‰ƒCƒg‚Ö‚Ìƒ|ƒCƒ“ƒ^
	 *	@date	1/5	Ver 1.0
	 */
	Sprite3D* Sprite3D::create( char* firstPath, char* secondPath, char* thirdPath)
	{
		return createObject( firstPath, secondPath, thirdPath);
	}

	Sprite3D* Sprite3D::createObject( char* firstPath, char* secondPath, char* thirdPath)
	{
		bool Flag[ResouceType::Num] = { false };
		char* str[] { firstPath, secondPath, thirdPath };
		string filePath;
		auto sprite = new (nothrow) Sprite3D();
		
		if( firstPath == nullptr) return nullptr;

		for( auto num : str)
		{
			if( num == nullptr) break;

			switch( checkResourcePath(num))
			{
			case ResouceType::NoExt:
				if( Flag[ResouceType::NoExt] == false)
				{
					filePath = getResourcePath( ResouceType::NoExt);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	  #ifdef DEBUG
					filePath = filePath + num + ".c3t";
	  #else
					filePath = filePath + num + ".c3b";
	  #endif
	#else
	  #ifdef _DEBUG
					filePath = filePath + num + ".c3t";
	  #else
					filePath = filePath + num + ".c3b";
	  #endif
	#endif
					if (sprite && sprite->initWithFile(filePath))
					{
						sprite->_contentSize = sprite->getBoundingBox().size;
						sprite->autorelease();
					}
					Flag[ResouceType::NoExt] = true;
				}
				else
				{
					return nullptr;
				}
				break;

			case ResouceType::Model:
				if( Flag[ResouceType::Model] == false)
				{
					filePath = getResourcePath( ResouceType::Model);
					filePath = filePath + num;
					if (sprite && sprite->initWithFile(filePath))
					{
						sprite->_contentSize = sprite->getBoundingBox().size;
						sprite->autorelease();
					}
					Flag[ResouceType::Model] = true;
				}
				else
				{
					return nullptr;
				}
				break;

			case ResouceType::Anime:
				if( Flag[ResouceType::Anime] == false)
				{
					filePath = getResourcePath( ResouceType::Anime) + filePath;
					sprite -> load3DModelAnimeData( filePath);
					Flag[ResouceType::Anime] = true;
				}
				else
				{
					return nullptr;
				}
				break;

			case ResouceType::Texture:
				if( Flag[ResouceType::Texture] == false)
				{
					filePath = getResourcePath( ResouceType::Texture) + filePath;
					sprite -> load3DModelTextureData( filePath);
					sprite -> setTextureList();
					Flag[ResouceType::Texture] = true;
				}
				else
				{
					return nullptr;
				}
				break;

			case ResouceType::Picture:
				if( Flag[ResouceType::Picture] == false)
				{
					filePath = getResourcePath( ResouceType::Picture);
					filePath = filePath + num; 
					sprite->setTexture(filePath);
					Flag[ResouceType::Picture] = true;
				}
				else
				{
					return nullptr;
				}
				break;

			default:
				CC_SAFE_DELETE(sprite);
				return nullptr;
			}
		}
		if( Flag[ResouceType::NoExt] == false)
		{
			CC_SAFE_DELETE(sprite);
			return nullptr;
		}
		return sprite;
	}

	ResouceType Sprite3D::checkResourcePath( const string& filePath)
	{
		string str = filePath;
		int point = str.rfind( '.', str.size());
		if( point == string::npos) return ResouceType::NoExt;
		str.erase( 0, str.size() - ( str.size() - point));
		if( str == ".obj" || str == ".c3t" || str == ".c3b") return ResouceType::Model;
		else if( str == ".anime") return ResouceType::Anime;
		else if( str == ".texture") return ResouceType::Texture;
		else return ResouceType::Picture;
	}

	string Sprite3D::getResourcePath( ResouceType type)
	{
		switch( type)
		{
		case ResouceType::NoExt:
		case ResouceType::Model:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			return "";
	#else
			return "Graph/Models/";
	#endif
			break;

		case ResouceType::Anime:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			return "";
	#else
			return "Parameter/Animation/";
	#endif
			break;

		case ResouceType::Texture:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			return "";
	#else
			return "Parameter/Texture/";
	#endif
			break;

		case ResouceType::Picture:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			return "";
	#else
			return "Graph/Textures/";
	#endif
			break;

		default:
			break;
=======
using namespace TapGun;

/**
*	3Dã‚¹ãƒ—ãƒ©ã‚¤ãƒˆã®ä½œæˆ
*
*	@author	minaka
*	@param	firstPath ãƒªã‚½ãƒ¼ã‚¹ãƒ•ã‚¡ã‚¤ãƒ«å
*	@return	ä½œæˆã—ãŸã‚¹ãƒ—ãƒ©ã‚¤ãƒˆã¸ã®ãƒã‚¤ãƒ³ã‚¿
*	@date	1/3	Ver 1.0
*/
Sprite3D* Sprite3D::create(const string& firstPath)
{
	string filePath;
	switch( checkResourcePath( firstPath))
{
	case ResouceType::NoExt:
	filePath = getResourcePath( ResouceType::NoExt);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#ifdef DEBUG
	filePath = filePath + firstPath + ".c3t";
	#else
	filePath = filePath + firstPath + ".c3b";
	#endif
	#else
	#ifdef _DEBUG
	filePath = filePath + firstPath + ".c3t";
	#else
	filePath = filePath + firstPath + ".c3b";
	#endif
	#endif
	break;

	case ResouceType::Model:
	filePath = getResourcePath( ResouceType::Model);
	filePath = filePath + firstPath;
	break;

	default:
	return nullptr;
}
auto sprite = new (nothrow) Sprite3D();
if (sprite && sprite->initWithFile(filePath))
{
	sprite->_contentSize = sprite->getBoundingBox().size;
	sprite->autorelease();
	return sprite;
}
CC_SAFE_DELETE(sprite);
return nullptr;
}

/**
*	3Dã‚¹ãƒ—ãƒ©ã‚¤ãƒˆã®ä½œæˆ
*
*	@author	minaka
*	@param	firstPath ãƒªã‚½ãƒ¼ã‚¹ãƒ•ã‚¡ã‚¤ãƒ«å
*	@param	secondPath ãƒªã‚½ãƒ¼ã‚¹ãƒ•ã‚¡ã‚¤ãƒ«å
*	@return	ä½œæˆã—ãŸã‚¹ãƒ—ãƒ©ã‚¤ãƒˆã¸ã®ãƒã‚¤ãƒ³ã‚¿
*	@date	1/3	Ver 1.0
*/
Sprite3D* Sprite3D::create( const string& firstPath, const string& secondPath)
{
	const int num = 2;
	bool Flag[ResouceType::Num] = { false };
	string filePath;
	string str[num] = { firstPath, secondPath };
	auto sprite = new (nothrow) Sprite3D();
	for( int i = 0; i < num; i++)
	{
		switch( checkResourcePath(str[i]))
	{
		case ResouceType::NoExt:
		if( Flag[ResouceType::NoExt] == false)
		{
			filePath = getResourcePath( ResouceType::NoExt);
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			#ifdef DEBUG
			filePath = filePath + str[i] + ".c3t";
			#else
			filePath = filePath + str[i] + ".c3b";
			#endif
			#else
			#ifdef _DEBUG
			filePath = filePath + str[i] + ".c3t";
			#else
			filePath = filePath + str[i] + ".c3b";
			#endif
			#endif
			if (sprite && sprite->initWithFile(filePath))
			{
				sprite->_contentSize = sprite->getBoundingBox().size;
				sprite->autorelease();
			}
			Flag[ResouceType::NoExt] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Model:
		if( Flag[ResouceType::Model] == false)
		{
			filePath = getResourcePath( ResouceType::Model);
			filePath = filePath + str[i];
			if (sprite && sprite->initWithFile(filePath))
			{
				sprite->_contentSize = sprite->getBoundingBox().size;
				sprite->autorelease();
			}
			Flag[ResouceType::Model] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Anime:
		if( Flag[ResouceType::Anime] == false)
		{
			//filePath = getResourcePath( ResouceType::Anime) + filePath;
			sprite -> load3DModelAnimeData( str[i]);
			Flag[ResouceType::Anime] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Texture:
		if( Flag[ResouceType::Texture] == false)
		{
			//filePath = getResourcePath( ResouceType::Texture) + filePath;
			sprite -> load3DModelTextureData( str[i]);
			sprite -> setTextureList();
			Flag[ResouceType::Texture] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Picture:
		if( Flag[ResouceType::Picture] == false)
		{
			filePath = getResourcePath( ResouceType::Picture);
			filePath = filePath + str[i];
			sprite->setTexture(filePath);
			Flag[ResouceType::Picture] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		default:
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
}
return sprite;
}

/**
*	3Dã‚¹ãƒ—ãƒ©ã‚¤ãƒˆã®ä½œæˆ
*
*	@author	minaka
*	@param	firstPath ãƒªã‚½ãƒ¼ã‚¹ãƒ•ã‚¡ã‚¤ãƒ«å
*	@param	secondPath ãƒªã‚½ãƒ¼ã‚¹ãƒ•ã‚¡ã‚¤ãƒ«å
*	@param	thirdPath ãƒªã‚½ãƒ¼ã‚¹ãƒ•ã‚¡ã‚¤ãƒ«å
*	@return	ä½œæˆã—ãŸã‚¹ãƒ—ãƒ©ã‚¤ãƒˆã¸ã®ãƒã‚¤ãƒ³ã‚¿
*	@date	1/5	Ver 1.0
*/
Sprite3D* Sprite3D::create( const string& firstPath, const string& secondPath, const string& thirdPath)
{
	const int num = 3;
	bool Flag[ResouceType::Num] = { false };
	string filePath;
	string str[num] = { firstPath, secondPath, thirdPath };
	auto sprite = new (nothrow) Sprite3D();
	for( int i = 0; i < num; i++)
	{
		switch( checkResourcePath(str[i]))
	{
		case ResouceType::NoExt:
		if( Flag[ResouceType::NoExt] == false)
		{
			filePath = getResourcePath( ResouceType::NoExt);
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			#ifdef DEBUG
			filePath = filePath + str[i] + ".c3t";
			#else
			filePath = filePath + str[i] + ".c3b";
			#endif
			#else
			#ifdef _DEBUG
			filePath = filePath + str[i] + ".c3t";
			#else
			filePath = filePath + str[i] + ".c3b";
			#endif
			#endif
			if (sprite && sprite->initWithFile(filePath))
			{
				sprite->_contentSize = sprite->getBoundingBox().size;
				sprite->autorelease();
			}
			Flag[ResouceType::NoExt] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Model:
		if( Flag[ResouceType::Model] == false)
		{
			filePath = getResourcePath( ResouceType::Model);
			filePath = filePath + str[i];
			if (sprite && sprite->initWithFile(filePath))
			{
				sprite->_contentSize = sprite->getBoundingBox().size;
				sprite->autorelease();
			}
			Flag[ResouceType::Model] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Anime:
		if( Flag[ResouceType::Anime] == false)
		{
			filePath = getResourcePath( ResouceType::Anime) + filePath;
			sprite -> load3DModelAnimeData( filePath);
			Flag[ResouceType::Anime] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Texture:
		if( Flag[ResouceType::Texture] == false)
		{
			filePath = getResourcePath( ResouceType::Texture) + filePath;
			sprite -> load3DModelTextureData( filePath);
			sprite -> setTextureList();
			Flag[ResouceType::Texture] = true;
		}
		else
		{
			return nullptr;
		}
		break;

		case ResouceType::Picture:
		if( Flag[ResouceType::Picture] == false)
		{
			filePath = getResourcePath( ResouceType::Picture);
			filePath = filePath + str[i];
			sprite->setTexture(filePath);
			Flag[ResouceType::Picture] = true;
		}
		else
		{
			return nullptr;
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
		}
		break;

		default:
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
<<<<<<< HEAD

	/**
	 *	3Dƒ‚ƒfƒ‹ƒf[ƒ^—pƒAƒjƒ[ƒVƒ‡ƒ“İ’èƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ
	 *
	 *	@author	minaka
	 *	@param	fileName ƒ‚ƒfƒ‹ƒf[ƒ^–¼
	 *	@return	³íI—¹:0 ƒGƒ‰[”­¶:-1
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::load3DModelAnimeData( const string& fileName)
	{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		string filePath = fileName;
	#else
		string filePath = "Parameter/Animation/" + fileName;
	#endif
		ifstream file( filePath, ios::in);
		if( file.fail()) 
		{
			return -1;
		}
		string str;
		ModelAnimeData *data = new ModelAnimeData;
		while( getline( file, str))
		{
			string tmp;
			istringstream stream(str);
			getline( stream, tmp, ',');
			data -> animeName = tmp;
			getline( stream, tmp, ',');
			data -> startFrame = atof(tmp.c_str());
			getline( stream, tmp);
			data -> endFrame = atof(tmp.c_str());
			this -> modelAnimeList.push_back( data);
		}

		return 0;
	}

	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒAƒjƒ[ƒVƒ‡ƒ“Ä¶
	 *
	 *	@author	minaka
	 *	@param	animeName ƒAƒjƒ[ƒVƒ‡ƒ“–¼
	 *	@return	³íI—¹:0 ƒGƒ‰[”­¶:-1
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::startAnimation( const string& animeName)
	{
		for( int i = 0; i < modelAnimeList.size(); i++)
		{
			if( animeName == modelAnimeList[i] -> animeName)
			{
				this -> animate = cocos2d::Animate3D::create( this -> animation, 0.016 * (modelAnimeList[i] -> startFrame * 2),
					0.016 * (modelAnimeList[i] -> endFrame * 2));
				runAction( this -> animate);
				return 0;
			}
		}
		return -1;
	}

	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒAƒjƒ[ƒVƒ‡ƒ“Ä¶iƒ‹[ƒvj
	 *
	 *	@author	minaka
	 *	@param	animeName ƒAƒjƒ[ƒVƒ‡ƒ“–¼
	 *	@return	³íI—¹:0 ƒGƒ‰[”­¶:-1
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::startAnimationLoop( const string& animeName)
	{
		for( int i = 0; i < modelAnimeList.size(); i++)
		{
			if( animeName == modelAnimeList[i] -> animeName)
			{
				this -> animate = cocos2d::Animate3D::create( this -> animation, 0.016 * (modelAnimeList[i] -> startFrame * 2),
					0.016 * (modelAnimeList[i] -> endFrame * 2));
				runAction( cocos2d::RepeatForever::create( this -> animate));
				return 0;
			}
		}
		return -1;
	}

	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒAƒjƒ[ƒVƒ‡ƒ“’â~
	 *
	 *	@author	minaka
	 *	@param	animeName ƒAƒjƒ[ƒVƒ‡ƒ“–¼
	 *	@return	³íI—¹:0
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::stopAnimation( const string& animeName)
	{
		stopAction( this -> animate);
		return 0;
	}

	/**
	 *	‘S‚Ä‚ÌƒAƒjƒ[ƒVƒ‡ƒ“‚ğ’â~
	 *
	 *	@author	minaka
	 *	@return	³íI—¹:0
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::stopALLAnimation( void)
=======
}
return sprite;
}

ResouceType Sprite3D::checkResourcePath( const string& filePath)
{
	string str = filePath;
	int point = str.rfind( '.', str.size());
	if( point == string::npos) return ResouceType::NoExt;
	str.erase( 0, str.size() - ( str.size() - point));
	if( str == ".obj" || str == ".c3t" || str == ".c3b") return ResouceType::Model;
	else if( str == ".anime") return ResouceType::Anime;
	else if( str == ".texture") return ResouceType::Texture;
	else return ResouceType::Picture;
}

string Sprite3D::getResourcePath( ResouceType type)
{
	switch( type)
{
	case ResouceType::NoExt:
	case ResouceType::Model:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return "";
	#else
	return "Graph/Models/";
	#endif
	break;

	case ResouceType::Anime:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return "";
	#else
	return "Parameter/Animation/";
	#endif
	break;

	case ResouceType::Texture:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return "";
	#else
	return "Parameter/Texture/";
	#endif
	break;

	case ResouceType::Picture:
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return "";
	#else
	return "Graph/Textures/";
	#endif
	break;

	default:
	break;
}
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ãƒ‡ãƒ¼ã‚¿ç”¨ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³è¨­å®šãƒ•ã‚¡ã‚¤ãƒ«ã®èª­ã¿è¾¼ã¿
*
*	@author	minaka
*	@param	fileName ãƒ¢ãƒ‡ãƒ«ãƒ‡ãƒ¼ã‚¿å
*	@return	æ­£å¸¸çµ‚äº†:0 ã‚¨ãƒ©ãƒ¼ç™ºç”Ÿ:-1
*	@date	1/3	Ver 1.0
*/
int Sprite3D::load3DModelAnimeData( const string& fileName)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	string filePath = fileName;
	#else
	string filePath = "Parameter/Animation/" + fileName;
	#endif
	ifstream file( filePath, ios::in);
	if( file.fail())
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
	{
		stopAllActions();
		return 0;
	}

	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒAƒjƒ[ƒVƒ‡ƒ“Ä¶‘¬“x‚ğİ’è
	 *
	 *	@author	minaka
	 *	@param	speed ƒAƒjƒ[ƒVƒ‡ƒ“‘¬“x
	 *	@return	³íI—¹:0
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::setAnimationSpeed( float speed)
	{
		animate -> setSpeed( speed);
		return 0;
	}

<<<<<<< HEAD
	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒAƒjƒ[ƒVƒ‡ƒ“ó‘Ôƒ`ƒFƒbƒN
	 *
	 *	@author	minaka
	 *	@return	ƒAƒjƒ[ƒVƒ‡ƒ“’†‚Å‚Í‚È‚¢:0@ƒAƒjƒ[ƒVƒ‡ƒ“’†:1 
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::checkAnimationState( void)
=======
	return 0;
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³å†ç”Ÿ
*
*	@author	minaka
*	@param	animeName ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³å
*	@return	æ­£å¸¸çµ‚äº†:0 ã‚¨ãƒ©ãƒ¼ç™ºç”Ÿ:-1
*	@date	1/3	Ver 1.0
*/
int Sprite3D::startAnimation( const string& animeName)
{
	for( int i = 0; i < modelAnimeList.size(); i++)
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
	{
		if ( numberOfRunningActions() == 0 ) 
		{
<<<<<<< HEAD
=======
			this -> animate = cocos2d::Animate3D::create( this -> animation, 0.016 * (modelAnimeList[i] -> startFrame * 2),
			0.016 * (modelAnimeList[i] -> endFrame * 2));
			runAction( this -> animate);
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
			return 0;
		} 
		else 
		{
			return 1;
		}
	}
<<<<<<< HEAD

	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒAƒjƒ[ƒVƒ‡ƒ“î•ñ‰ğ•ú
	 *
	 *	@author	minaka
	 *	@date	1/3	Ver 1.0
	 */
	void Sprite3D::releaseAnimation( void)
	{
		vector<ModelAnimeData*>().swap(modelAnimeList);
	}

	/**
	 *	3Dƒ‚ƒfƒ‹ƒf[ƒ^—pƒeƒNƒXƒ`ƒƒİ’èƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ
	 *
	 *	@author	minaka
	 *	@param	fileName ƒ‚ƒfƒ‹ƒf[ƒ^–¼
	 *	@return	³íI—¹:0 ƒGƒ‰[”­¶:-1
	 *	@date	1/5	Ver 1.0
	 */
	int Sprite3D::load3DModelTextureData( const string& fileName)
=======
	return -1;
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³å†ç”Ÿï¼ˆãƒ«ãƒ¼ãƒ—ï¼‰
*
*	@author	minaka
*	@param	animeName ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³å
*	@return	æ­£å¸¸çµ‚äº†:0 ã‚¨ãƒ©ãƒ¼ç™ºç”Ÿ:-1
*	@date	1/3	Ver 1.0
*/
int Sprite3D::startAnimationLoop( const string& animeName)
{
	for( int i = 0; i < modelAnimeList.size(); i++)
	{
		if( animeName == modelAnimeList[i] -> animeName)
		{
			this -> animate = cocos2d::Animate3D::create( this -> animation, 0.016 * (modelAnimeList[i] -> startFrame * 2),
			0.016 * (modelAnimeList[i] -> endFrame * 2));
			runAction( cocos2d::RepeatForever::create( this -> animate));
			return 0;
		}
	}
	return -1;
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³åœæ­¢
*
*	@author	minaka
*	@param	animeName ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³å
*	@return	æ­£å¸¸çµ‚äº†:0
*	@date	1/3	Ver 1.0
*/
int Sprite3D::stopAnimation( const string& animeName)
{
	stopAction( this -> animate);
	return 0;
}

/**
*	å…¨ã¦ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³ã‚’åœæ­¢
*
*	@author	minaka
*	@return	æ­£å¸¸çµ‚äº†:0
*	@date	1/3	Ver 1.0
*/
int Sprite3D::stopALLAnimation( void)
{
	stopAllActions();
	return 0;
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³å†ç”Ÿé€Ÿåº¦ã‚’è¨­å®š
*
*	@author	minaka
*	@param	speed ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³é€Ÿåº¦
*	@return	æ­£å¸¸çµ‚äº†:0
*	@date	1/3	Ver 1.0
*/
int Sprite3D::setAnimationSpeed( float speed)
{
	animate -> setSpeed( speed);
	return 0;
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³çŠ¶æ…‹ãƒã‚§ãƒƒã‚¯
*
*	@author	minaka
*	@return	ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³ä¸­ã§ã¯ãªã„:0ã€€ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³ä¸­:1
*	@date	1/3	Ver 1.0
*/
int Sprite3D::checkAnimationState( void)
{
	if ( numberOfRunningActions() == 0 )
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
	{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		string filePath = fileName;
	#else
		string filePath = "Parameter/Texture/" + fileName;
	#endif
		ifstream file( filePath, ios::in);
		if( file.fail()) 
		{
			return -1;
		}
		string str;
		while( getline( file, str))
		{
			ModelTextureData *data = new ModelTextureData;
			string tmp;
			istringstream stream(str);
			getline( stream, tmp, ',');
			data -> meshName = tmp;
			getline( stream, tmp);
			data -> textureName = tmp;
			this -> modelTextureList.push_back( data);
		}

		return 0;
	}
<<<<<<< HEAD

	/**
	 *	3Dƒ‚ƒfƒ‹ƒf[ƒ^‚ÉƒeƒNƒXƒ`ƒƒ‚ğİ’è
	 *
	 *	@author	minaka
	 *	@date	1/5	Ver 1.0
	 */
	void Sprite3D::setTextureList( void)
=======
	else
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
	{
		for( int i = 0; i < modelTextureList.size(); i++)
		{
			string filePath = "Graph/Textures/" + modelTextureList[i] -> textureName;
			auto mesh = this -> getMeshByName( modelTextureList[i] -> meshName);
			mesh -> setTexture( filePath);
		}
	}
<<<<<<< HEAD

	/**
	 *	3Dƒ‚ƒfƒ‹‚ÌƒeƒNƒXƒ`ƒƒî•ñ‰ğ•ú
	 *
	 *	@author	minaka
	 *	@date	1/3	Ver 1.0
	 */
	void Sprite3D::releaseTexture( void)
=======
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³æƒ…å ±è§£æ”¾
*
*	@author	minaka
*	@date	1/3	Ver 1.0
*/
void Sprite3D::releaseAnimation( void)
{
	vector<ModelAnimeData*>().swap(modelAnimeList);
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ãƒ‡ãƒ¼ã‚¿ç”¨ãƒ†ã‚¯ã‚¹ãƒãƒ£è¨­å®šãƒ•ã‚¡ã‚¤ãƒ«ã®èª­ã¿è¾¼ã¿
*
*	@author	minaka
*	@param	fileName ãƒ¢ãƒ‡ãƒ«ãƒ‡ãƒ¼ã‚¿å
*	@return	æ­£å¸¸çµ‚äº†:0 ã‚¨ãƒ©ãƒ¼ç™ºç”Ÿ:-1
*	@date	1/5	Ver 1.0
*/
int Sprite3D::load3DModelTextureData( const string& fileName)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	string filePath = fileName;
	#else
	string filePath = "Parameter/Texture/" + fileName;
	#endif
	ifstream file( filePath, ios::in);
	if( file.fail())
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
	{
		vector<ModelTextureData*>().swap(modelTextureList);
	}

	int Sprite3D::setShaderFile( const string& fileName)
	{
		auto shader = new cocos2d::GLProgram();
		string filePath[2] = { "Shader/" + fileName + ".vsh", "Shader/" + fileName + ".fsh"};
		shader -> initWithFilenames( filePath[0], filePath[1]);
		shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
		shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_COLOR, cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
		shader -> link();
		shader -> updateUniforms();
		this -> setShaderProgram( shader);
		return 0;
	}

	int Sprite3D::setShaderFile( const string& vshFile, const string& fshFile)
	{
		auto shader = new cocos2d::GLProgram();
		string filePath[2] = { "Shader/" + vshFile + ".vsh", "Shader/" + fshFile + ".fsh"};
		shader -> initWithFilenames( filePath[0], filePath[1]);
		shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
		shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_COLOR, cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
		shader -> link();
		shader -> updateUniforms();
		this -> setShaderProgram( shader);
		return 0;
	}

<<<<<<< HEAD
	Sprite3D::~Sprite3D()
=======
/**
*	3Dãƒ¢ãƒ‡ãƒ«ãƒ‡ãƒ¼ã‚¿ã«ãƒ†ã‚¯ã‚¹ãƒãƒ£ã‚’è¨­å®š
*
*	@author	minaka
*	@date	1/5	Ver 1.0
*/
void Sprite3D::setTextureList( void)
{
	for( int i = 0; i < modelTextureList.size(); i++)
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a
	{
		_meshes.clear();
		_meshVertexDatas.clear();
		CC_SAFE_RELEASE_NULL(_skeleton);
		removeAllAttachNode();
		releaseAnimation();
	}
<<<<<<< HEAD

}
=======
}

/**
*	3Dãƒ¢ãƒ‡ãƒ«ã®ãƒ†ã‚¯ã‚¹ãƒãƒ£æƒ…å ±è§£æ”¾
*
*	@author	minaka
*	@date	1/3	Ver 1.0
*/
void Sprite3D::releaseTexture( void)
{
	vector<ModelTextureData*>().swap(modelTextureList);
}

int Sprite3D::setShaderFile( const string& fileName)
{
	auto shader = new cocos2d::GLProgram();
	string filePath[2] = { "Shader/" + fileName + ".vsh", "Shader/" + fileName + ".fsh"};
	shader -> initWithFilenames( filePath[0], filePath[1]);
	shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
	shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_COLOR, cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
	shader -> link();
	shader -> updateUniforms();
	this -> setShaderProgram( shader);
	return 0;
}

int Sprite3D::setShaderFile( const string& vshFile, const string& fshFile)
{
	auto shader = new cocos2d::GLProgram();
	string filePath[2] = { "Shader/" + vshFile + ".vsh", "Shader/" + fshFile + ".fsh"};
	shader -> initWithFilenames( filePath[0], filePath[1]);
	shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
	shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	shader -> bindAttribLocation( cocos2d::GLProgram::ATTRIBUTE_NAME_COLOR, cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
	shader -> link();
	shader -> updateUniforms();
	this -> setShaderProgram( shader);
	return 0;
}

Sprite3D::~Sprite3D()
{
	_meshes.clear();
	_meshVertexDatas.clear();
	CC_SAFE_RELEASE_NULL(_skeleton);
	removeAllAttachNode();
	releaseAnimation();
}
>>>>>>> 1d61bef2fa7bd9bd2e46ac652fcfe5d4564b9a1a


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
	 *	3Dスプライトの作成	
	 *
	 *	@author	minaka
	 *	@param	firstPath リソースファイル名
	 *	@return	作成したスプライトへのポインタ
	 *	@date	1/3	Ver 1.0
	 */
	Sprite3D* Sprite3D::create( char* firstPath)
	{
		return createObject( firstPath, nullptr, nullptr);
	}

	/**
	 *	3Dスプライトの作成	
	 *
	 *	@author	minaka
	 *	@param	firstPath リソースファイル名
	 *	@param	secondPath リソースファイル名
	 *	@return	作成したスプライトへのポインタ
	 *	@date	1/3	Ver 1.0
	 */
	Sprite3D* Sprite3D::create( char* firstPath, char* secondPath)
	{
		return createObject( firstPath, secondPath, nullptr);
	}

	/**
	 *	3Dスプライトの作成	
	 *
	 *	@author	minaka
	 *	@param	firstPath リソースファイル名
	 *	@param	secondPath リソースファイル名
	 *	@param	thirdPath リソースファイル名
	 *	@return	作成したスプライトへのポインタ
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
*	3D繧ｹ繝励Λ繧､繝医�ｮ菴懈��
*
*	@author	minaka
*	@param	firstPath 繝ｪ繧ｽ繝ｼ繧ｹ繝輔ぃ繧､繝ｫ蜷�
*	@return	菴懈�舌＠縺溘せ繝励Λ繧､繝医∈縺ｮ繝昴う繝ｳ繧ｿ
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
*	3D繧ｹ繝励Λ繧､繝医�ｮ菴懈��
*
*	@author	minaka
*	@param	firstPath 繝ｪ繧ｽ繝ｼ繧ｹ繝輔ぃ繧､繝ｫ蜷�
*	@param	secondPath 繝ｪ繧ｽ繝ｼ繧ｹ繝輔ぃ繧､繝ｫ蜷�
*	@return	菴懈�舌＠縺溘せ繝励Λ繧､繝医∈縺ｮ繝昴う繝ｳ繧ｿ
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
*	3D繧ｹ繝励Λ繧､繝医�ｮ菴懈��
*
*	@author	minaka
*	@param	firstPath 繝ｪ繧ｽ繝ｼ繧ｹ繝輔ぃ繧､繝ｫ蜷�
*	@param	secondPath 繝ｪ繧ｽ繝ｼ繧ｹ繝輔ぃ繧､繝ｫ蜷�
*	@param	thirdPath 繝ｪ繧ｽ繝ｼ繧ｹ繝輔ぃ繧､繝ｫ蜷�
*	@return	菴懈�舌＠縺溘せ繝励Λ繧､繝医∈縺ｮ繝昴う繝ｳ繧ｿ
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
	 *	3Dモデルデータ用アニメーション設定ファイルの読み込み
	 *
	 *	@author	minaka
	 *	@param	fileName モデルデータ名
	 *	@return	正常終了:0 エラー発生:-1
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
	 *	3Dモデルのアニメーション再生
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@return	正常終了:0 エラー発生:-1
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
	 *	3Dモデルのアニメーション再生（ループ）
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@return	正常終了:0 エラー発生:-1
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
	 *	3Dモデルのアニメーション停止
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@return	正常終了:0
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::stopAnimation( const string& animeName)
	{
		stopAction( this -> animate);
		return 0;
	}

	/**
	 *	全てのアニメーションを停止
	 *
	 *	@author	minaka
	 *	@return	正常終了:0
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
*	3D繝｢繝�繝ｫ繝�繝ｼ繧ｿ逕ｨ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ險ｭ螳壹ヵ繧｡繧､繝ｫ縺ｮ隱ｭ縺ｿ霎ｼ縺ｿ
*
*	@author	minaka
*	@param	fileName 繝｢繝�繝ｫ繝�繝ｼ繧ｿ蜷�
*	@return	豁｣蟶ｸ邨ゆｺ�:0 繧ｨ繝ｩ繝ｼ逋ｺ逕�:-1
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
	 *	3Dモデルのアニメーション再生速度を設定
	 *
	 *	@author	minaka
	 *	@param	speed アニメーション速度
	 *	@return	正常終了:0
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::setAnimationSpeed( float speed)
	{
		animate -> setSpeed( speed);
		return 0;
	}

<<<<<<< HEAD
	/**
	 *	3Dモデルのアニメーション状態チェック
	 *
	 *	@author	minaka
	 *	@return	アニメーション中ではない:0　アニメーション中:1 
	 *	@date	1/3	Ver 1.0
	 */
	int Sprite3D::checkAnimationState( void)
=======
	return 0;
}

/**
*	3D繝｢繝�繝ｫ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蜀咲函
*
*	@author	minaka
*	@param	animeName 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蜷�
*	@return	豁｣蟶ｸ邨ゆｺ�:0 繧ｨ繝ｩ繝ｼ逋ｺ逕�:-1
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
	 *	3Dモデルのアニメーション情報解放
	 *
	 *	@author	minaka
	 *	@date	1/3	Ver 1.0
	 */
	void Sprite3D::releaseAnimation( void)
	{
		vector<ModelAnimeData*>().swap(modelAnimeList);
	}

	/**
	 *	3Dモデルデータ用テクスチャ設定ファイルの読み込み
	 *
	 *	@author	minaka
	 *	@param	fileName モデルデータ名
	 *	@return	正常終了:0 エラー発生:-1
	 *	@date	1/5	Ver 1.0
	 */
	int Sprite3D::load3DModelTextureData( const string& fileName)
=======
	return -1;
}

/**
*	3D繝｢繝�繝ｫ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蜀咲函�ｼ医Ν繝ｼ繝暦ｼ�
*
*	@author	minaka
*	@param	animeName 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蜷�
*	@return	豁｣蟶ｸ邨ゆｺ�:0 繧ｨ繝ｩ繝ｼ逋ｺ逕�:-1
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
*	3D繝｢繝�繝ｫ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蛛懈ｭ｢
*
*	@author	minaka
*	@param	animeName 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蜷�
*	@return	豁｣蟶ｸ邨ゆｺ�:0
*	@date	1/3	Ver 1.0
*/
int Sprite3D::stopAnimation( const string& animeName)
{
	stopAction( this -> animate);
	return 0;
}

/**
*	蜈ｨ縺ｦ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞●豁｢
*
*	@author	minaka
*	@return	豁｣蟶ｸ邨ゆｺ�:0
*	@date	1/3	Ver 1.0
*/
int Sprite3D::stopALLAnimation( void)
{
	stopAllActions();
	return 0;
}

/**
*	3D繝｢繝�繝ｫ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ蜀咲函騾溷ｺｦ繧定ｨｭ螳�
*
*	@author	minaka
*	@param	speed 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ騾溷ｺｦ
*	@return	豁｣蟶ｸ邨ゆｺ�:0
*	@date	1/3	Ver 1.0
*/
int Sprite3D::setAnimationSpeed( float speed)
{
	animate -> setSpeed( speed);
	return 0;
}

/**
*	3D繝｢繝�繝ｫ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ迥ｶ諷九メ繧ｧ繝�繧ｯ
*
*	@author	minaka
*	@return	繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ荳ｭ縺ｧ縺ｯ縺ｪ縺�:0縲�繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ荳ｭ:1
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
	 *	3Dモデルデータにテクスチャを設定
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
	 *	3Dモデルのテクスチャ情報解放
	 *
	 *	@author	minaka
	 *	@date	1/3	Ver 1.0
	 */
	void Sprite3D::releaseTexture( void)
=======
}

/**
*	3D繝｢繝�繝ｫ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ諠�蝣ｱ隗｣謾ｾ
*
*	@author	minaka
*	@date	1/3	Ver 1.0
*/
void Sprite3D::releaseAnimation( void)
{
	vector<ModelAnimeData*>().swap(modelAnimeList);
}

/**
*	3D繝｢繝�繝ｫ繝�繝ｼ繧ｿ逕ｨ繝�繧ｯ繧ｹ繝√Ε險ｭ螳壹ヵ繧｡繧､繝ｫ縺ｮ隱ｭ縺ｿ霎ｼ縺ｿ
*
*	@author	minaka
*	@param	fileName 繝｢繝�繝ｫ繝�繝ｼ繧ｿ蜷�
*	@return	豁｣蟶ｸ邨ゆｺ�:0 繧ｨ繝ｩ繝ｼ逋ｺ逕�:-1
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
*	3D繝｢繝�繝ｫ繝�繝ｼ繧ｿ縺ｫ繝�繧ｯ繧ｹ繝√Ε繧定ｨｭ螳�
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
*	3D繝｢繝�繝ｫ縺ｮ繝�繧ｯ繧ｹ繝√Ε諠�蝣ｱ隗｣謾ｾ
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

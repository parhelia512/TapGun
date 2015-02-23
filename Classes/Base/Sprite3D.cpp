
#include <fstream>
#include "cocos2d.h"
#include "base/CCAsyncTaskPool.h"
#include "3d/CCMesh.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "Base/Sprite3D.h"

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <CCFileUtils-android.h>

#endif

USING_NS_CC;
using namespace std;

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
	_Sprite3D* _Sprite3D::create( const string& firstPath)
	{
		return createObject( firstPath.c_str(), nullptr, nullptr);
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
	_Sprite3D* _Sprite3D::create( const string& firstPath, const string& secondPath)
	{
		return createObject( firstPath.c_str(), secondPath.c_str(), nullptr);
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
	_Sprite3D* _Sprite3D::create( const string& firstPath, const string& secondPath, const string& thirdPath)
	{
		return createObject( firstPath.c_str(), secondPath.c_str(), thirdPath.c_str());
	}

	void _Sprite3D::createAsync( const string& modelPath, const function<void(_Sprite3D*, void*)>& callback, void* callbackparam)
	{
		createObjectAsync( modelPath.c_str(), "", nullptr, callback, callbackparam);
	}
		
	void _Sprite3D::createAsync( const string& modelPath, const string& texturePath, const function<void(_Sprite3D*, void*)>& callback, void* callbackparam)
	{
		createObjectAsync( modelPath.c_str(), texturePath.c_str(), nullptr, callback, callbackparam);
	}

	void _Sprite3D::createAsync( const string& modelPath, const string& texturePath, const string& animePath, const function<void(_Sprite3D*, void*)>& callback, void* callbackparam)
	{
		createObjectAsync( modelPath.c_str(), texturePath.c_str(), animePath.c_str(), callback, callbackparam);
	}

	_Sprite3D* _Sprite3D::createObject( const char* firstPath, const char* secondPath, const char* thirdPath)
	{
		string filePath;
		bool Flag[ResouceType::Num] = { false };
		map< int, string> str;
		auto sprite = new (nothrow) _Sprite3D();

		if( &firstPath == nullptr) return nullptr;
		else str[0] = firstPath;
		if( secondPath != nullptr) str[1] = secondPath;
		if( thirdPath != nullptr) str[2] = thirdPath;

		for( int i = 0; i < str.size(); i++)
		{
			if( &str.at(i) == nullptr) break;

			switch( checkResourcePath(str.at(i)))
			{
			case ResouceType::NoExt:
				if( Flag[ResouceType::NoExt] == false)
				{
					filePath = getResourcePath( ResouceType::NoExt);
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				  #ifdef DEBUG
					filePath = filePath + str.at(i) + ".c3t";
				  #else
					filePath = filePath + str.at(i) + ".c3b";
				  #endif
				#else
				#ifdef _DEBUG
					filePath = filePath + str.at(i) + ".c3t";
				  #else
					filePath = filePath + str.at(i) + ".c3b";
				  #endif
				#endif
					if( sprite && sprite -> initWithFile( filePath))
					{
						sprite -> _contentSize = sprite -> getBoundingBox().size;
						sprite -> autorelease();
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
					filePath = filePath + str.at(i);
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
					filePath = getResourcePath( ResouceType::Anime);
					filePath = filePath + str.at(i);
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
					filePath = getResourcePath( ResouceType::Texture);
					filePath = filePath + str.at(i);
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
					filePath = filePath + str.at(i);
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
		if( Flag[ResouceType::NoExt] == false && Flag[ResouceType::Model] == false)
		{
			CC_SAFE_DELETE(sprite);
			return nullptr;
		}
		return sprite;
	}

	void _Sprite3D::createObjectAsync( const char* modelPath, const char* texturePath, const char* animePath, const function<void(_Sprite3D*, void*)>& callback, void* callbackparam)
	{
		string filePath;
		bool Flag[ResouceType::Num] = { false };
		map< int, string> str;
		auto sprite = new (nothrow) _Sprite3D();

		if( &modelPath == nullptr) return;
		else str[0] = modelPath;
		if( texturePath != nullptr) str[1] = texturePath;
		if( animePath != nullptr) str[2] = animePath;

		for( int i = 0; i < str.size(); i++)
		{
			if( &str.at(i) == nullptr) break;

			switch( checkResourcePath(str.at(i)))
			{
			case ResouceType::NoExt:
				if( Flag[ResouceType::NoExt] == false && Flag[ResouceType::Model] == false)
				{					
					filePath = getResourcePath( ResouceType::NoExt);
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				  #ifdef DEBUG
					filePath = filePath + str.at(i) + ".c3t";
				  #else
					filePath = filePath + str.at(i) + ".c3b";
				  #endif
				#else
				#ifdef _DEBUG
					filePath = filePath + str.at(i) + ".c3t";
				  #else
					filePath = filePath + str.at(i) + ".c3b";
				  #endif
				#endif

					if( sprite -> loadFromCache( filePath))
					{
						sprite -> autorelease();
						if( !str.empty()) { sprite -> setTexture( texturePath); }
						callback( sprite, callbackparam);
						return;
					}
	
					sprite -> _asyncLoadParam.afterLoadCallback = callback;
					string str = texturePath;
					if( str.size() > 4) { sprite -> _asyncLoadParam.texPath = getResourcePath( ResouceType::Model) + texturePath; }
					else { sprite -> _asyncLoadParam.texPath = texturePath; }
					sprite -> _asyncLoadParam.modlePath = filePath;
					sprite -> _asyncLoadParam.callbackParam = callbackparam;
					sprite -> _asyncLoadParam.materialdatas = new (nothrow) MaterialDatas();
					sprite -> _asyncLoadParam.meshdatas = new (nothrow) MeshDatas();
					sprite -> _asyncLoadParam.nodeDatas = new (nothrow) NodeDatas();
					AsyncTaskPool::getInstance() -> enqueue( AsyncTaskPool::TaskType::TASK_IO, CC_CALLBACK_1( _Sprite3D::afterAsyncLoad, sprite), (void*)(&sprite -> _asyncLoadParam), [sprite]()
					{
						sprite -> _asyncLoadParam.result = sprite -> loadFromFile( sprite -> _asyncLoadParam.modlePath, sprite -> _asyncLoadParam.nodeDatas, sprite -> _asyncLoadParam.meshdatas, sprite -> _asyncLoadParam.materialdatas);
					});

					Flag[ResouceType::NoExt] = true;
				}
				break;

			case ResouceType::Model:
				if( Flag[ResouceType::Model] == false && Flag[ResouceType::NoExt] == false)
				{
					filePath = getResourcePath( ResouceType::Model);
					filePath = filePath + str.at(i);

					if( sprite -> loadFromCache( filePath))
					{
						sprite -> autorelease();
						if( !str.empty()) { sprite -> setTexture( texturePath); }
						callback( sprite, callbackparam);
						return;
					}
	
					sprite -> _asyncLoadParam.afterLoadCallback = callback;
					string str = texturePath;
					if( str.size() > 4) { sprite -> _asyncLoadParam.texPath = getResourcePath( ResouceType::Model) + texturePath; }
					else { sprite -> _asyncLoadParam.texPath = texturePath; }
					sprite -> _asyncLoadParam.modlePath = filePath;
					sprite -> _asyncLoadParam.callbackParam = callbackparam;
					sprite -> _asyncLoadParam.materialdatas = new (nothrow) MaterialDatas();
					sprite -> _asyncLoadParam.meshdatas = new (nothrow) MeshDatas();
					sprite -> _asyncLoadParam.nodeDatas = new (nothrow) NodeDatas();
					AsyncTaskPool::getInstance() -> enqueue( AsyncTaskPool::TaskType::TASK_IO, CC_CALLBACK_1( _Sprite3D::afterAsyncLoad, sprite), (void*)(&sprite -> _asyncLoadParam), [sprite]()
					{
						sprite -> _asyncLoadParam.result = sprite -> loadFromFile( sprite -> _asyncLoadParam.modlePath, sprite -> _asyncLoadParam.nodeDatas, sprite -> _asyncLoadParam.meshdatas, sprite -> _asyncLoadParam.materialdatas);
					});
					Flag[ResouceType::Model] = true;
				}
				break;

			case ResouceType::Anime:
				if( Flag[ResouceType::Anime] == false)
				{
					filePath = getResourcePath( ResouceType::Anime);
					filePath = filePath + str.at(i);
					sprite -> load3DModelAnimeData( filePath);
					Flag[ResouceType::Anime] = true;
				}
				break;

			default:
//				CC_SAFE_DELETE( sprite);
				break;
			}
		}
		if( Flag[ResouceType::NoExt] == false && Flag[ResouceType::Model] == false)
		{
			CC_SAFE_DELETE(sprite);
			return;
		}
	}

	void _Sprite3D::afterAsyncLoad( void* param)
	{
		_Sprite3D::AsyncLoadParam* asyncParam = (_Sprite3D::AsyncLoadParam*)param;
		autorelease();
		if( asyncParam)
		{
			if( asyncParam -> result)
			{
				_meshes.clear();
				_meshVertexDatas.clear();
				CC_SAFE_RELEASE_NULL( _skeleton);
				removeAllAttachNode();
			
				//create in the main thread
				auto& meshdatas = asyncParam -> meshdatas;
				auto& materialdatas = asyncParam -> materialdatas;
				auto& nodeDatas = asyncParam -> nodeDatas;
				if( initFrom( *nodeDatas, *meshdatas, *materialdatas))
				{
					auto spritedata = Sprite3DCache::getInstance() -> getSpriteData( asyncParam -> modlePath);
					if( spritedata == nullptr)
					{
						//add to cache
						auto data = new (std::nothrow) Sprite3DCache::Sprite3DData();
						data -> materialdatas = materialdatas;
						data -> nodedatas = nodeDatas;
						data -> meshVertexDatas = _meshVertexDatas;
						for( const auto mesh : _meshes) { data -> glProgramStates.pushBack( mesh -> getGLProgramState()); }
					
						Sprite3DCache::getInstance() -> addSprite3DData( asyncParam -> modlePath, data);
						meshdatas = nullptr;
						materialdatas = nullptr;
						nodeDatas = nullptr;
					}
				}
				delete meshdatas;
				delete materialdatas;
				delete nodeDatas;
			
				if( asyncParam -> texPath != "") { setTexture( asyncParam -> texPath); }
			}
			else
			{
				CCLOG( "file load failed: %s ", asyncParam -> modlePath.c_str());
			}
			asyncParam -> afterLoadCallback( this, asyncParam -> callbackParam);
		}
	}

	bool _Sprite3D::loadFromCache( const string& path)
	{
		auto spritedata = Sprite3DCache::getInstance() -> getSpriteData( path);
		if( spritedata)
		{
			for( auto it : spritedata -> meshVertexDatas) { _meshVertexDatas.pushBack( it); }
			_skeleton = Skeleton3D::create( spritedata -> nodedatas -> skeleton);
			CC_SAFE_RETAIN( _skeleton);
		
			for( const auto& it : spritedata -> nodedatas -> nodes)
			{
				if( it) { createNode( it, this, *(spritedata -> materialdatas), spritedata -> nodedatas -> nodes.size() == 1); }
			}
		
			for( const auto& it : spritedata -> nodedatas -> skeleton)
			{
				if( it) { createAttachSprite3DNode( it,*(spritedata -> materialdatas)); }
			}
		
			for( ssize_t i = 0; i < _meshes.size(); i++) { _meshes.at( i) -> setGLProgramState( spritedata -> glProgramStates.at( i)); }
			return true;
		}
	
		return false;
	}

	ResouceType _Sprite3D::checkResourcePath( const string& filePath)
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

	string _Sprite3D::getResourcePath( ResouceType type)
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
	*	3Dモデルデータ用アニメーション設定ファイルの読み込み
	*
	*	@author	minaka
	*	@param	fileName モデルデータ名
	*	@return	正常終了:0 エラー発生:-1
	*	@date	1/3	Ver 1.0
	*/
	int _Sprite3D::load3DModelAnimeData( const string& fileName)
	{
	  #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string dir = FileUtils::getInstance() -> fullPathForFilename( fileName);
		ifstream file( dir, ios::in);
	  #elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		string fileData = FileUtilsAndroid::getInstance() -> getStringFromFile( fileName);
		stringstream file(fileData);
	  #else
		ifstream file( fileName, ios::in);
	  #endif
		if( file.fail())
		{
			return -1;
		}
		string str;
		while( getline( file, str))
		{
			string name;
			string path;
			string tmp;
			istringstream stream(str);
			getline( stream, tmp, ',');
	  #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			auto point = tmp.rfind( '/', tmp.size()) + 1;
			tmp.erase( 0, tmp.size() - ( tmp.size() - point));
			path = tmp;
	  #else
			path = "Graph/Models/" + tmp;
	  #endif
			getline( stream, tmp);
			name = tmp;
			modelAnimeList[name] = path;
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
	int _Sprite3D::startAnimation( const string& animeName)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation);
		if( animate == nullptr) return -1;
		runAction( animate);
		return 0;
	}

	/**
	*	3Dモデルのアニメーション再生（ループ）
	*
	*	@author	minaka
	*	@param	animeName アニメーション名
	*	@return	正常終了:0 エラー発生:-1
	*	@date	1/3	Ver 1.0
	*/
	int _Sprite3D::startAnimationLoop( const string& animeName)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation);
		if( animate == nullptr) return -1;
		runAction( cocos2d::RepeatForever::create( animate));
		return 0;
	}

	/**
	 *	3Dモデルのアニメーション逆再生
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@return	正常終了:0 エラー発生:-1
	 *	@date	1/20	Ver 1.0
	 */
	int _Sprite3D::startAnimationReverse( const string& animeName)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation);
		if( animate == nullptr) return -1;
		animate -> setSpeed( -1);
		runAction( animate);
		return 0;
	}

	/**
	 *	3Dモデルのアニメーション逆再生（ループ）
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@return	正常終了:0 エラー発生:-1
	 *	@date	1/20	Ver 1.0
	 */
	int _Sprite3D::startAnimationReverseLoop( const string& animeName)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation);
		if( animate == nullptr) return -1;
		animate -> setSpeed( -1);
		runAction( cocos2d::RepeatForever::create( animate));
		return 0;
	}

	/**
	*	3Dモデルのアニメーショントリミング再生
	*
	*	@author	minaka
	*	@param	animeName アニメーション名
	*	@param	startTime / 60 トリミング開始フレーム
	*	@param	endTime トリミング終了フレーム
	*	@return	正常終了:0 エラー発生:-1
	*	@date	1/23	Ver 1.0
	*/
	int _Sprite3D::startAnimation( const string& animeName, int startTime, int endTime)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation, startTime / 60, endTime / 60);
		if( animate == nullptr) return -1;
		runAction( animate);
		return 0;
	}

	/**
	*	3Dモデルのアニメーショントリミング再生（ループ）
	*
	*	@author	minaka
	*	@param	animeName アニメーション名
	*	@param	startTime トリミング開始フレーム
	*	@param	endTime トリミング終了フレーム
	*	@return	正常終了:0 エラー発生:-1
	*	@date	1/23	Ver 1.0
	*/
	int _Sprite3D::startAnimationLoop( const string& animeName, int startTime, int endTime)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation, startTime / 60, endTime / 60);
		if( animate == nullptr) return -1;
		runAction( cocos2d::RepeatForever::create( animate));
		return 0;
	}

	/**
	 *	3Dモデルのアニメーショントリミング逆再生
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@param	startTime トリミング開始フレーム
	 *	@param	endTime トリミング終了フレーム
	 *	@return	正常終了:0 エラー発生:-1
	 *	@date	1/23	Ver 1.0
	 */
	int _Sprite3D::startAnimationReverse( const string& animeName, int startTime, int endTime)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation, startTime / 60, endTime / 60);
		if( animate == nullptr) return -1;
		animate -> setSpeed( -1);
		runAction( animate);
		return 0;
	}

	/**
	 *	3Dモデルのアニメーショントリミング逆再生（ループ）
	 *
	 *	@author	minaka
	 *	@param	animeName アニメーション名
	 *	@param	startTime トリミング開始フレーム
	 *	@param	endTime トリミング終了フレーム
	 *	@return	正常終了:0 エラー発生:-1
	 *	@date	1/23	Ver 1.0
	 */
	int _Sprite3D::startAnimationReverseLoop( const string& animeName, int startTime, int endTime)
	{
		string str = modelAnimeList[animeName];
		if( str == "") return -1;
		animation = cocos2d::Animation3D::create( str);
		if( animation == nullptr) return -1;
		animate = cocos2d::Animate3D::create( animation, startTime / 60, endTime / 60);
		if( animate == nullptr) return -1;
		animate -> setSpeed( -1);
		runAction( cocos2d::RepeatForever::create( animate));
		return 0;
	}

	/**
	*	3Dモデルのアニメーション停止
	*
	*	@author	minaka
	*	@param	animeName アニメーション名
	*	@return	正常終了:0
	*	@date	1/3	Ver 1.0
	*/
	int _Sprite3D::stopAnimation( void)
	{
		stopAction( animate);
		return 0;
	}

	/**
	*	全てのアニメーションを停止
	*
	*	@author	minaka
	*	@return	正常終了:0
	*	@date	1/3	Ver 1.0
	*/
	int _Sprite3D::stopALLAnimation( void)
	{
		stopAllActions();
		return 0;
	}

	int _Sprite3D::pauseAnimation( void)
	{
		if( numberOfRunningActions() == 0)
		{
			return 0;
		}
		else
		{
			
		}
	}
	
	int _Sprite3D::restartAnimation( void)
	{
		
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
	int _Sprite3D::setAnimationSpeed( float speed)
	{
		animate -> setSpeed( speed);
		return 0;
	}

	/**
	*	3Dモデルのアニメーション状態チェック
	*
	*	@author	minaka
	*	@return	アニメーション中ではない:0　アニメーション中:1
	*	@date	1/3	Ver 1.0
	*/
	int _Sprite3D::checkAnimationState( void)
	{
		if( numberOfRunningActions() == 0 )
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	/**
	*	3Dモデルのアニメーション情報解放
	*
	*	@author	minaka
	*	@date	1/3	Ver 1.0
	*/
	void _Sprite3D::releaseAnimation( void)
	{
		map< const string, string>().swap( modelAnimeList);
	}

	/**
	*	3Dモデルデータ用テクスチャ設定ファイルの読み込み
	*
	*	@author	minaka
	*	@param	fileName モデルデータ名
	*	@return	正常終了:0 エラー発生:-1
	*	@date	1/5	Ver 1.0
	*/
	int _Sprite3D::load3DModelTextureData( const string& fileName)
	{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		std::string dir = FileUtils::getInstance() -> fullPathForFilename( fileName);
		ifstream file( dir, ios::in);
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		string fileData = FileUtilsAndroid::getInstance() -> getStringFromFile( fileName);
		stringstream file(fileData);
	#else
		ifstream file( fileName, ios::in);
	#endif
		if( file.fail())
		{
			return -1;
		}
		string str;
		textureData *data = new textureData;
		while( getline( file, str))
		{
			string tmp;
			istringstream stream(str);
			getline( stream, tmp, ',');
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			auto point = tmp.rfind( '/', tmp.size()) + 1;
			tmp.erase( 0, tmp.size() - ( tmp.size() - point));
			data -> path = tmp;
		#else
			data -> path = "Graph/Textures/" + tmp;
		#endif
			getline( stream, tmp);
			data -> name = tmp;
			modelTextureList.push_back(*data);
		}
		return 0;
	}

	/**
	*	3Dモデルデータにテクスチャを設定
	*
	*	@author	minaka
	*	@date	1/5	Ver 1.0
	*/
	void _Sprite3D::setTextureList( void)
	{
		for( auto &data : modelTextureList)
		{
			auto mesh = getMeshByName( data.name);
			mesh -> setTexture( data.path);
		}

	}

	/**
	*	3Dモデルのテクスチャ情報解放
	*
	*	@author	minaka
	*	@date	1/3	Ver 1.0
	*/
	void _Sprite3D::releaseTexture( void)
	{
		vector<textureData>().swap( modelTextureList);
	}

	int _Sprite3D::setShaderFile( const string& fileName)
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

	int _Sprite3D::setShaderFile( const string& vshFile, const string& fshFile)
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
	
	double getSec( void)
	{
		timeval tv;
		gettimeofday(&tv, nullptr);
		return (tv.tv_sec) + (tv.tv_usec) * 1e-6;
	}
}


#ifndef __SPRITE3D_H__
#define __SPRITE3D_H__

#include "cocos2d.h"

namespace TapGun
{
	enum ResouceType
	{
		NoExt,
		Model,
		Anime,
		Texture,
		Picture,
		Num,
	};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	struct animeData
	{
		std::string name;
		std::string path;
		animeData* next;
	};

	struct textureData
	{
		std::string name;
		std::string path;
		textureData* next;
	};
#else
	struct textureData
	{
		std::string name;
		std::string path;
	};
#endif
	class _Sprite3D : public cocos2d::Sprite3D
	{
	public:
		static _Sprite3D* create( const std::string& firstPath);
		static _Sprite3D* create( const std::string& firstPath, const std::string& secondPath);
		static _Sprite3D* create( const std::string& firstPath, const std::string& secondPath, const std::string& thirdPath);

		int startAnimation( const std::string& animeName);
		int startAnimationLoop( const std::string& animeName);
		int startAnimationReverse( const std::string& animeName);
		
		int stopAnimation( const std::string& animeName);
		int stopALLAnimation( void);

		int setAnimationSpeed( float speed);

		int checkAnimationState( void);

		void releaseAnimation( void);

		void releaseTexture( void);

		int setShaderFile( const std::string& fileName);
		int setShaderFile( const std::string& vshFile, const std::string& fshFile);

		CC_CONSTRUCTOR_ACCESS:
		_Sprite3D() {}

	protected:

	private:
		cocos2d::Animation3D*           animation;
		cocos2d::Animate3D*             animate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		animeData* modelAnimeListStart;
		textureData* modelTextureListStart;
#else
		std::map< const std::string, std::string>	modelAnimeList;
		std::vector< textureData>	modelTextureList;
#endif
		void setTextureList(void);
		int load3DModelAnimeData( const std::string& fileName);
		int load3DModelTextureData( const std::string& fileName);
		static _Sprite3D* createObject( const char* firstPath, const char* secondPath, const char* thirdPath);
		static std::string getResourcePath( ResouceType type);
		static ResouceType checkResourcePath( const std::string& filePath);
	};
}

#endif // __SPRITE3D_H__

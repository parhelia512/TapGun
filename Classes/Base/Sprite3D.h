
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

	struct textureData
	{
		std::string name;
		std::string path;
	};

	class _Sprite3D : public cocos2d::Sprite3D
	{
	public:
		static _Sprite3D* create( const std::string& firstPath);
		static _Sprite3D* create( const std::string& firstPath, const std::string& secondPath);
		static _Sprite3D* create( const std::string& firstPath, const std::string& secondPath, const std::string& thirdPath);

		int startAnimation( const std::string& animeName);
		int startAnimation( const std::string& animeName, int startTime, int endTime);
		int startAnimationLoop( const std::string& animeName);
		int startAnimationLoop( const std::string& animeName, int startTime, int endTime);
		int startAnimationReverse( const std::string& animeName);
		int startAnimationReverse( const std::string& animeName, int startTime, int endTime);
		int startAnimationReverseLoop( const std::string& animeName);
		int startAnimationReverseLoop( const std::string& animeName, int startTime, int endTime);
		
		int stopAnimation( void);
		int stopALLAnimation( void);

		int pauseAnimation( void);
		int restartAnimation( void);
		
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
		double time;
		cocos2d::Animation3D*           animation;
		cocos2d::Animate3D*             animate;
		std::map< const std::string, std::string>	modelAnimeList;
		std::vector< textureData>	modelTextureList;

		void setTextureList(void);
//		int startAnimation( const std::string& animeName);
		int load3DModelAnimeData( const std::string& fileName);
		int load3DModelTextureData( const std::string& fileName);
		static _Sprite3D* createObject( const char* firstPath, const char* secondPath, const char* thirdPath);
		static std::string getResourcePath( ResouceType type);
		static ResouceType checkResourcePath( const std::string& filePath);
	};
}

#endif // __SPRITE3D_H__


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

	struct ModelAnimeData
	{
		std::string animeName;
		float startFrame;
		float endFrame;
	};

	struct ModelTextureData
	{
		std::string meshName;
		std::string textureName;
	};

	class Sprite3D : public cocos2d::Sprite3D
	{
	public:
		static Sprite3D* create( char* firstPath);
		static Sprite3D* create( char* firstPath, char* secondPath);
		static Sprite3D* create( char* firstPath, char* secondPath, char* thirdPath);

		int startAnimation( const std::string& animeName);
		int startAnimationLoop( const std::string& animeName);

		int stopAnimation( const std::string& animeName);
		int stopALLAnimation( void);

		int setAnimationSpeed( float speed);

		int checkAnimationState( void);

		void releaseAnimation( void);

		void releaseTexture( void);

		int setShaderFile( const std::string& fileName);
		int setShaderFile( const std::string& vshFile, const std::string& fshFile);

	CC_CONSTRUCTOR_ACCESS:
		Sprite3D() {}
		virtual ~Sprite3D();

	protected:

	private:
		cocos2d::Animation3D*           animation;
		cocos2d::Animate3D*             animate;
		std::vector<ModelAnimeData*>	modelAnimeList;
		std::vector<ModelTextureData*>	modelTextureList;

		void setTextureList(void);
		int load3DModelAnimeData( const std::string& fileName);
		int load3DModelTextureData( const std::string& fileName);
		static Sprite3D* createObject( char* firstPath, char* secondPath, char* thirdPath);
		static std::string getResourcePath( ResouceType type);
		static ResouceType checkResourcePath( const std::string& filePath);
	};
}

#endif // __SPRITE3D_H__

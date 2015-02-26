
#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include "cocos2d.h"

namespace TapGun
{
	class Directory
	{
	public:
		Directory( const Directory &P) = delete;
		Directory& operator= ( const Directory &P) = delete;
		static Directory* getInstance( void);

		static std::map< int, std::string> searchModelFile( const std::string& keyName);
		static std::map< int, std::string> searchTextureFile( const std::string& keyName);
	private:
		Directory() {}
		static std::map< int, std::string> searchResourceFile( const char* keyName);

	};
}

#endif // __DIRECTORY_H__

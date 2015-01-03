
#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "cocos2d.h"

namespace TapGun
{

class Wrapper 
{
public:
	enum Flag 
	{
		True = 1,
		False = 0,
	};

	Wrapper( const Wrapper &P) = delete;
	Wrapper& operator= ( const Wrapper &P) = delete;
	static Wrapper* getInstance( void);

	int loadSound( const std::string& fileName);
	int playSound( const std::string& fileName);
	int playSoundLoop( const std::string& fileName);
	int stopSound( const std::string& fileName);
	int releaseSound( const std::string& fileName);

private:
	Wrapper() {}

};

}

#endif // __WRAPPER_H__

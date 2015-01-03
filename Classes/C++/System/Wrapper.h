
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

private:
	Wrapper() {}

};

}

#endif // __WRAPPER_H__

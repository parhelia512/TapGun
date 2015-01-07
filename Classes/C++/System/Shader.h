
#ifndef __SHADER_H__
#define __SHADER_H__

#include "cocos2d.h"

namespace TapGun
{

class Shader 
{
public:
	Shader( const Shader &P) = delete;
	Shader& operator= ( const Shader &P) = delete;
	static Shader* getInstance( void);



private:
	Shader() {}

};

}

#endif // __SHADER_H__

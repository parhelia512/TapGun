
#ifndef __ERROR_FUNC_H__
#define __ERROR_FUNC_H__

#include "cocos2d.h"

namespace TapGun
{

class Errorfunc
{
public:
	#define SET_MESSAGE( string) setMessage( __LINE__, __FILE__, __FUNCTION__, string)
	static Errorfunc* getInstance( void);
	void setMessage( int lineNumber, std::string fileName, std::string functionName, std::string errorMessage);
	void drawMessage( cocos2d::Layer* layer);
	void releaseMessage( void);
	
	Errorfunc( const Errorfunc &P) = delete;
	Errorfunc& operator= ( const Errorfunc &P) = delete;

private:
	struct ErrorData
	{
		int lineNumber;
		std::string fileName;
		std::string functionName;
		std::string errorMessage;
	};
	Errorfunc() {}
	std::vector<ErrorData> errorList;
};



}

#endif // __ERROR_FUNC_H__

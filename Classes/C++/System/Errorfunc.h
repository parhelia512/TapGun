
#ifndef __ERROR_FUNC_H__
#define __ERROR_FUNC_H__

#include "cocos2d.h"

namespace TapGun
{
	struct ErrorData
	{
		int lineNumber;
		std::string fileName;
		std::string functionName;
		std::string errorMessage;
	};

	class Errorfunc
	{
	public:
	#define SET_MESSAGE( str) Errorfunc::getInstance() -> setMessage( __LINE__, __FILE__, __FUNCTION__, str)
		Errorfunc( const Errorfunc &P) = delete;
		Errorfunc& operator= ( const Errorfunc &P) = delete;
		static Errorfunc* getInstance( void);

		void setMessage( int lineNumber, std::string fileName, std::string functionName, std::string errorMessage);
		void drawMessage( cocos2d::Layer* layer);
		void releaseMessage( void);

	private:
		std::vector<ErrorData*> errorList;

		Errorfunc() {}
	};
}

#endif // __ERROR_FUNC_H__

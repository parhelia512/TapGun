
#include "cocos2d.h"
#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Errorfunc.h"

#else

#include "C++/System/Errorfunc.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

/**
 *	数値を文字列へ変換
 *
 *	@author	minaka
 *	@param	value 変換元となるデータ
 *	@return	変換した文字列
 *	@date	12/28 Ver 1.0
 */
template<class T> string valueToString( T value)
{
	ostringstream os ;
	os << value ;
	return os.str();
}

/**
 *	エラー処理クラスのインスタンスを取得
 *
 *	@author	minaka
 *	@return	作成済みのインスタンスへのポインタ
 *	@date	12/28 Ver 1.0
 */
Errorfunc* Errorfunc::getInstance( void)
{
	static Errorfunc* P;
	if( !P) P = new Errorfunc;
	return P;
}

/**
 *	エラー情報を設定
 *
 *	@author	minaka
 *	@param	lineNumber	 呼び出し先行番号
 *	@param	fileName	 呼び出し先ファイル名
 *	@param	functionName 呼び出し先関数名
 *	@param	errorMessage 表示したい文字列
 *	@date	12/28 Ver 1.0
 */
void Errorfunc::setMessage( int lineNumber, string fileName, string functionName, string errorMessage)
{
	ErrorData* data			= new ErrorData;
	data -> lineNumber		= lineNumber;
	data -> fileName		= fileName;
	data -> functionName	= functionName;
	data -> errorMessage	= errorMessage;
	errorList.push_back( data);
}

/**
 *	エラー情報を表示
 *
 *	@author	minaka
 *	@param	layer 表示するレイヤーへのポインタ
 *	@date	12/28 Ver 1.0
 */
void Errorfunc::drawMessage( Layer* layer)
{
	int size = errorList.size();
	string str;
	
	if( size == 0) return;
	auto bg = LayerColor::create( Color4B::BLACK, SystemValue::windowSize.width, SystemValue::windowSize.height);
	layer -> addChild( bg, SystemValue::ERROR_MESSAGE);
	for( int i = 0; i < size; i++)
	{
		size_t pos1;
		string fileName;
		string filePass = errorList[i] -> fileName;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		pos1 = filePass.rfind('\\');
		if( pos1 != string::npos)
		{
			fileName = filePass.substr( pos1 + 1, filePass.size() - pos1 - 1);
		}
#else
		pos1 = filePass.rfind('/');
		if( pos1 != string::npos)
		{
			fileName = filePass.substr( pos1 + 1, filePass.size() - pos1 - 1);
		}
#endif
		str = "Error! / " + fileName + " / " + errorList[i] -> functionName + " / "
			+ valueToString( errorList[i] -> lineNumber) + " / " + errorList[i] -> errorMessage;
		auto message = Label::create( str, "Arial", 20);
		message -> setPosition( Point( message -> getContentSize().width / 2 + 10, SystemValue::windowSize.height - message -> getContentSize().height - (message -> getContentSize().height * i)));
		layer -> addChild( message, SystemValue::ERROR_MESSAGE);
	}
	releaseMessage();
}

/**
 *	エラー処理で使用したメモリの開放
 *
 *	@author	minaka
 *	@date	12/28 Ver 1.0
 */
void Errorfunc::releaseMessage( void)
{
	vector<ErrorData*>().swap(errorList);
}

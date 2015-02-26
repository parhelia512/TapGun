
#include "cocos2d.h"
#include "Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Errorfunc.h"

#else

#include "System/Errorfunc.h"

#endif

USING_NS_CC;
using namespace std;
using namespace TapGun;

/**
 *	���l�𕶎���֕ϊ�
 *
 *	@author	minaka
 *	@param	value �ϊ����ƂȂ�f�[�^
 *	@return	�ϊ�����������
 *	@date	12/28 Ver 1.0
 */
template<class T> string valueToString( T value)
{
	ostringstream os ;
	os << value ;
	return os.str();
}

/**
 *	�G���[�����N���X�̃C���X�^���X���擾
 *
 *	@author	minaka
 *	@return	�쐬�ς݂̃C���X�^���X�ւ̃|�C���^
 *	@date	12/28 Ver 1.0
 */
Errorfunc* Errorfunc::getInstance( void)
{
	static Errorfunc* P;
	if( !P) P = new Errorfunc;
	return P;
}

/**
 *	�G���[����ݒ�
 *
 *	@author	minaka
 *	@param	lineNumber	 �Ăяo����s�ԍ�
 *	@param	fileName	 �Ăяo����t�@�C����
 *	@param	functionName �Ăяo����֐���
 *	@param	errorMessage �\��������������
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
 *	�G���[����\��
 *
 *	@author	minaka
 *	@param	layer �\�����郌�C���[�ւ̃|�C���^
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
 *	�G���[�����Ŏg�p�����������̊J��
 *
 *	@author	minaka
 *	@date	12/28 Ver 1.0
 */
void Errorfunc::releaseMessage( void)
{
	vector<ErrorData*>().swap(errorList);
}

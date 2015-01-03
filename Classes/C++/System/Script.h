
#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <fstream>

namespace TapGun
{

class Script 
{
public:
	Script();
	Script( const Script& p) = delete;	
	Script& operator=( const Script& P) = delete;
	~Script();
	int loadScriptFile( const std::string& fileName);
	int loadCommand( int index);

private:
	struct commandSet 
	{
		std::string name;
		void* data;
	};

	std::ifstream file;
	std::vector<commandSet> scriptList;

};

}

#endif // __SCRIPT_H__

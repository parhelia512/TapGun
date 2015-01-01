
#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <fstream>

namespace TapGun
{

class Script 
{
public:
	int loadSctiptFile( const std::string& fileName);
	int loadCommand( int index);
private:
	struct commandSet {
		std::string name;
		void* data;
	};
	std::vector<commandSet> scriptList;
	std::ifstream file;
};

}

#endif // __SCRIPT_H__

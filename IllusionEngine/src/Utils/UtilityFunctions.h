#pragma once

namespace Illusion
{
	namespace util
	{
		namespace string //string utility functions will reside under this namespace
		{
			std::string getSubStr(const std::string &str, std::string delimiter, int offset);
			std::string getSubStr(const std::string &str, std::string delimiter, int offset, int endposition);
			
			std::size_t getDelimiterPos(const std::string &str ,std::string delimiter);
		} 

		//other....
	}
}
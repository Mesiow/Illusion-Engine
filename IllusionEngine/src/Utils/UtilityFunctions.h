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

		namespace file
		{
			void checkFileStatus(std::ifstream &file);
			std::ifstream &gotoLine(std::ifstream &file, unsigned int line);
			bool isEmpty(std::ifstream &file);
		}

		//other....
	}
}
#include "../pcHeaders.h"
#include "UtilityFunctions.h"

namespace Illusion
{
	namespace util
	{
		namespace string
		{
			std::string getSubStr(const std::string &str, std::string delimiter, int offset)
			{
				std::size_t position = getDelimiterPos(str, delimiter); //get position of delimiter
				std::string sub = str.substr(offset, position);

				return sub;
			}

			std::string getSubStr(const std::string &str, std::string delimiter, int offset, int endposition)
			{
				std::string sub = str.substr(offset, endposition);

				return sub;
			}

			std::size_t getDelimiterPos(const std::string &str, std::string delimiter)
			{
				std::size_t position = str.find(delimiter);
				return position;
			}
		}
	}
}

void Illusion::util::file::checkFileStatus(std::ifstream &file)
{
	if (file.bad())
		std::cout << "File is bad" << std::endl;
	else if (file.fail())
		std::cout << "Filed failed" << std::endl;
	else if (file.eof())
		std::cout << "File is at the end" << std::endl;
}

std::ifstream &Illusion::util::file::gotoLine(std::ifstream &file, unsigned int line)
{
	file.seekg(std::ios::beg); //seek to the beginning of file

	for (int i = 0; i < line - 1; i++)
	{
		//ignore each line up until line - 1
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

bool Illusion::util::file::isEmpty(std::ifstream &file)
{
	return (file.peek() == std::ifstream::traits_type::eof()); //returns true if it is empty
}

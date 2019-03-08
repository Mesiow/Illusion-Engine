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
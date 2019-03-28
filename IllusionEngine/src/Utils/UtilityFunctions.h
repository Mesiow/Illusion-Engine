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


		namespace mouse
		{
			class mousePositions
			{

			public:
				static void update();
				static void updateMouseGridPosition(int gridDimension);
				static void draw();


				static sf::Vector2i mousePosScreen;
				static sf::Vector2f mousePosView;
				static sf::Vector2i mousePosWindow;
				static sf::Vector2u mousePosGrid;
				static sf::Vector2u mousePosTextureBounds;
				static bool enableMousePos;
			};
		}
		//other....
	}
}
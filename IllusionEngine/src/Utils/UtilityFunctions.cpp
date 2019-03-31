#include "../pcHeaders.h"
#include "UtilityFunctions.h"
#include "../Game.h"

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

		namespace mouse
		{
			sf::Vector2i mousePositions::mousePosScreen;
			sf::Vector2f mousePositions::mousePosView;
			sf::Vector2i mousePositions::mousePosWindow;
			sf::Vector2u mousePositions::mousePosGrid;
			sf::Vector2u mousePositions::mousePosTextureBounds;
			bool mousePositions::enableMousePos = true;

			void mousePositions::update()
			{
				mousePosScreen = sf::Mouse::getPosition();
				mousePosWindow = sf::Mouse::getPosition(Game::getWindow());
				mousePosView = Game::getWindow().mapPixelToCoords(mousePosWindow); //map pixel on the window to coordinates
			}

			void mousePositions::updateMouseGridPosition(int gridDimension)
			{
				mousePosGrid.x = (int)mousePosView.x / gridDimension;
				mousePosGrid.y = (int)mousePosView.y / gridDimension;
			}


			void mousePositions::draw()
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && time::keyTime::checkKeyTime())
				{
					if (enableMousePos)
						enableMousePos = false;
					else
						enableMousePos = true;
				}

				if (enableMousePos)
				{
					sf::Text text(std::string(""), ResourceManager::getFont("rubik"), 15);
					text.setPosition(mousePosView.x + 30, mousePosView.y - 50);

					std::stringstream ss;
					ss << "Window Position: " << mousePosWindow.x << ", " << mousePosWindow.y << "\n"
						<< "View Position: " << mousePosView.x << ", " << mousePosView.y << "\n"
						<< "Grid Position: " << mousePosGrid.x << ", " << mousePosGrid.y << "\n";

					text.setString(ss.str());

					Game::getWindow().draw(text);
				}
			}
		}
		void drawToScreen(std::string str, const sf::Vector2f &position)
		{
			sf::Text text(str, ResourceManager::getFont("rubik"), 15);
			text.setPosition(position.x, position.y);

			std::stringstream ss;
			ss << str;

			text.setString(ss.str());

			Game::getWindow().draw(text);
		}


		namespace file
		{
			void checkFileStatus(std::ifstream &file)
			{
				if (file.bad())
					std::cout << "File is bad" << std::endl;
				else if (file.fail())
					std::cout << "Filed failed" << std::endl;
				else if (file.eof())
					std::cout << "File is at the end" << std::endl;
			}

			std::ifstream &gotoLine(std::ifstream &file, unsigned int line)
			{
				file.seekg(std::ios::beg); //seek to the beginning of file

				for (int i = 0; i < line - 1; i++)
				{
					//ignore each line up until line - 1
					file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				return file;
			}

			bool isEmpty(std::ifstream &file)
			{
				return (file.peek() == std::ifstream::traits_type::eof()); //returns true if it is empty
			}

		}

		namespace time
		{
			float keyTime::time = 0.0f;

			bool keyTime::checkKeyTime()
			{
				if (time < maxKeyTime)
				{
					time++;
					return false;
				}
				else
				{
					time = 0.0f;
					return true;
				}
			}
		}
	}

}

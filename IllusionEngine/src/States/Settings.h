#pragma once
#include "State.h"

namespace Illusion
{
	class Game;
	class Settings : public State
	{
	
	public:
		Settings(Game &game);
		~Settings();


	public:
		void initOptions();

		void update(float &dt)override;
		void handleEvents(sf::Event &e)override;
		void draw(sf::RenderTarget &target)override;



		//debug function
		void print()const noexcept
		{
			std::cout << "desktop res: " << desktopRes.width << ", " << desktopRes.height << std::endl;
			for (auto it = modes.begin(); it != modes.end(); it++)
			{
				std::cout << it->width << ", " << it->height << std::endl;
			}
		}

	private:
		void updateGui();

	private:
		std::size_t modeIndex = 1;
		const sf::VideoMode desktopRes = sf::VideoMode::getDesktopMode();
		const std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

		sf::Font *font;
		sf::Text text;
	
	};
}
#pragma once
#include "State.h"
#include "../Gui/DropDownList.h"

namespace Illusion
{
	class Game;
	class Settings : public State
	{
	
	public:
		Settings(Game &game);
		~Settings();


	public:
		void initGui();

		void update(float &dt)override;
		void handleEvents(sf::Event &e)override;
		void draw(sf::RenderTarget &target)override;

	private:
		void updateGui(float &dt);

	private:
		gui::DropDownList *list_;

		std::size_t modeIndex = 1;
		const sf::VideoMode desktopRes = sf::VideoMode::getDesktopMode();
		const std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

		sf::Font *font;
		sf::Text text;
	
	};
}
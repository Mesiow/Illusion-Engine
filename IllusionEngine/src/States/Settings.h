#pragma once
#include "State.h"
#include "../Gui/DropDownList.h"
#include "../Gui/Slider.h"
#include "../Utils/UtilityFunctions.h"

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
		gui::Slider *slider_;
		gui::DropDownList *ResolutionList_;
		gui::Button *back_;
		gui::Button *apply_;

		const std::vector<sf::VideoMode> videoModes_ = sf::VideoMode::getFullscreenModes();

		sf::Text text_;
	
	};
}
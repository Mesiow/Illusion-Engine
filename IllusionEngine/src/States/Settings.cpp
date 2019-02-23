#include "Settings.h"
#include "../Game.h"
#include "MenuState.h"

namespace Illusion
{
	Settings::Settings(Game &game)
		:State(game)
	{
		initGui();
	}

	Settings::~Settings()
	{
		
	}

	void Settings::initGui()
	{
		std::string list[4] = { "1920 x 1080", "1680 x 1050", "1600 x 1024", "1280 x 1024" };
		list_ = new gui::DropDownList(sf::Vector2f(400, 200), list, gui::Size::small, 4, 0);
	}

	void Settings::update(float &dt)
	{
		updateMousePositions();
		updateGui(dt);
	}

	void Settings::handleEvents(sf::Event &e)
	{
		list_->handleEvents(e);
	}

	void Settings::draw(sf::RenderTarget &target)
	{
		list_->draw(target);
	}


	void Settings::updateGui(float &dt)
	{
		list_->update();
	}
}
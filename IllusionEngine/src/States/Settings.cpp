#include "Settings.h"
#include "../Game.h"
#include "MenuState.h"

namespace Illusion
{
	Settings::Settings(Game &game)
		:State(game)
	{
		initOptions();
	}

	Settings::~Settings()
	{
		
	}

	void Settings::initOptions()
	{
		
	}

	void Settings::update(float &dt)
	{
		updateMousePositions();
		updateGui();
	}

	void Settings::handleEvents(sf::Event & e)
	{
		
	}

	void Settings::draw(sf::RenderTarget &target)
	{
	
	}


	void Settings::updateGui()
	{
		
	}
}
#include "Gui.h"
#include "../Game.h"

namespace Illusion
{
	namespace gui
	{
		bool Gui::containsMouse(const sf::FloatRect & rect)
		{
			auto mousePos = sf::Mouse::getPosition(Game::getWindow());
			if (rect.contains((float)mousePos.x, (float)mousePos.y))
				return true;

			return false;
		}

		sf::Vector2i Gui::getMousePosition()
		{
			auto mousepos = sf::Mouse::getPosition(Game::getWindow());
			return mousepos;
		}
	}
}
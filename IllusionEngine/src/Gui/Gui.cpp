#include "../pcHeaders.h"
#include "Gui.h"
#include "../Game.h"

namespace Illusion
{
	namespace gui
	{
		bool Gui::containsMouse(const sf::FloatRect &rect)
		{
			auto mousePos = getMousePositionView();
			if (rect.contains((float)mousePos.x, (float)mousePos.y))
				return true;

			return false;
		}

		sf::Vector2f Gui::getMousePositionView()
		{
			auto windowpos = sf::Mouse::getPosition(Game::getWindow());
			auto mouseposView = Game::getWindow().mapPixelToCoords(windowpos);
			return mouseposView;
		}
	}
}
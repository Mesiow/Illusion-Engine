#include "State.h"
#include "../Game.h"

namespace Illusion
{
	void State::updateMousePositions()noexcept
	{
		this->_mousePosScreen = sf::Mouse::getPosition();
		this->_mousePosWindow = sf::Mouse::getPosition(Game::getWindow());
		this->_mousePosView = Game::getWindow().mapPixelToCoords(_mousePosWindow); //map pixel on the window to coordinates
	}
}
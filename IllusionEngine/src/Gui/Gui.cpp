#include "../pcHeaders.h"
#include "Gui.h"
#include "../States/State.h"

namespace Illusion
{
	namespace gui
	{
		bool Gui::containsMouse(const sf::FloatRect &rect)
		{
			//std::cout << "mouse pos view gui class: " << mousePos.x << ", " << mousePos.y << std::endl;
			if (rect.contains((float)State::_mousePosView.x, (float)State::_mousePosView.y))
				return true;

			return false;
		}
	}
}
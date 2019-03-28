#include "../pcHeaders.h"
#include "Gui.h"
#include "../Utils/UtilityFunctions.h"

namespace Illusion
{
	namespace gui
	{
		bool Gui::containsMouse(const sf::FloatRect &rect)
		{
			//std::cout << "mouse pos view gui class: " << mousePos.x << ", " << mousePos.y << std::endl;
			if (rect.contains(util::mouse::mousePositions::mousePosView.x, util::mouse::mousePositions::mousePosView.y))
				return true;

			return false;
		}
	}
}
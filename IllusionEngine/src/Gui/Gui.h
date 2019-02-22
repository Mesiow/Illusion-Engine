#pragma once
#include <SFML/Graphics.hpp>
#include "../ResourceManagement/ResourceManager.h"

namespace Illusion
{


	namespace gui
	{
		class Gui
		{
		public:
			Gui(){}
			~Gui(){}

			virtual void handleEvents(sf::Event &e) = 0;
		};
	}
}
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

			virtual void update(float &dt){}
			virtual void handleEvents(sf::Event &e){}
			virtual void draw(sf::RenderTarget &target) = 0;
		};
	}
}
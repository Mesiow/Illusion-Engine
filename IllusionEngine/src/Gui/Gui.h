#pragma once
#include "../ResourceManagement/ResourceManager.h"

namespace Illusion
{


	namespace gui
	{
		enum Colors { idleColor = 0, hoverColor = 1, pressColor = 2 };
		enum Flag { idle = 0, hover = 1, pressed = 2 };
		enum class Size { large = 0, medium = 1, Small = 2 };

		using uint = unsigned int;


		class Gui
		{
		public:
			Gui(){}
			virtual ~Gui(){}

			virtual void update(float &dt){}
			virtual void handleEvents(sf::Event &e){}
			virtual void draw(sf::RenderTarget &target) = 0;

		protected:
			bool containsMouse(const sf::FloatRect &rect);
		};
	}
}
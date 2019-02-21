#pragma once
#include "Button.h"
#include <vector>

namespace Illusion
{
	namespace gui
	{
		class StackMenu
		{
		public:
			StackMenu(uint stackSize); //pass in how large we want the stack menu to be in size
			~StackMenu();


			void update();
			void draw(sf::RenderTarget &target);

		private:
			void initStackMenu();

		private:
			std::vector<gui::Button*> buttons;
		};
	}
}
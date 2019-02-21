#include "StackMenu.h"

namespace Illusion
{
	namespace gui
	{
		StackMenu::StackMenu(uint stackSize)
		{

		}

		StackMenu::~StackMenu()
		{
			for (uint i = 0; i < buttons.size(); ++i)
				delete buttons[i];
		}

		void StackMenu::update()
		{

		}

		void StackMenu::draw(sf::RenderTarget & target)
		{

		}

		void StackMenu::initStackMenu()
		{

		}
	}
}
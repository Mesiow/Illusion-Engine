#pragma once
#include <SFML/Graphics.hpp>
#include "../ResourceManagement/ResourceManager.h"
#include "DropDownList.h"
#include "StackMenu.h"

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
			virtual void handleEvents(sf::Event &e) = 0;
			virtual void draw(sf::RenderTarget &target) = 0;

		protected:
			void createDropDownList();
			void createStackMenu();

		private:
			gui::StackMenu *_menu;
			gui::DropDownList *_list;
		};
	}
}
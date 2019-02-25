#pragma once
#include "Button.h"
#include "Gui.h"
#include <vector>
#include <map>

namespace Illusion
{
	namespace gui
	{
		class StackMenu : public Gui
		{
		public:
			StackMenu(sf::Vector2f position, std::string buttonNames[],
				Size sizeofButtons, uint stackSize);
			~StackMenu();


			void handleEvents(sf::Event &e)override;
			void update();
			void update(float &dt){}
			void draw(sf::RenderTarget &target)override;

		public:
			void setButtonFunction(const std::string &str, std::function<void(void)> func);

		private:
			void initialize(sf::Vector2f position, std::string buttonNames[],
				Size sizeofButtons, uint stackSize);

		private:
			std::map<std::string, gui::Button*> buttonMap_;
		
			sf::Vector2f position_;
			uint stackSize_;
		};
	}
}
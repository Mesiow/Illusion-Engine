#pragma once
#include "Gui.h"
#include "Button.h"

namespace Illusion
{
	namespace gui
	{
		class DropDownList : public Gui
		{
		public:
			DropDownList(sf::Vector2f position, std::string list[],
				Size buttonsSize, uint listSize, uint activeIndex);
			~DropDownList();

			void handleEvents(sf::Event &e)override;
			void update();
			void draw(sf::RenderTarget &target)override;

		private:
			void initialize(const sf::Vector2f &position, std::string list[],
				const Size buttonsSize, const uint listSize, const uint activeIndex);

		private:
			gui::Button *activeButton_;
			std::map<std::string, gui::Button*> buttonsList_;

			sf::Vector2f position_;
			bool show;
		};
	}
}
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
			DropDownList(const sf::Vector2f position, std::vector<std::string> &list,
				Size buttonsSize, uint activeIndex);
			~DropDownList();

			void handleEvents(sf::Event &e)override;
			void update();
			void draw(sf::RenderTarget &target)override;

		public:
			void addToList(const std::string &item);
			bool removeFromList(const std::string &item);
			bool removeAllFromList();
			void setButtonFunction(const std::string &id, std::function<void(void)> func);

		public:
			gui::Button *getActiveButton() { return this->activeButton_; }
			void setListPosition(const sf::Vector2f &position);

		private:
			void setButtonListFunctions();
			void initialize(const sf::Vector2f &position,
				const Size buttonsSize, const uint activeIndex);

		private:
			gui::Button *activeButton_;
			std::map<std::string, gui::Button*> buttonsList_;
			std::vector<std::string> itemList;

			sf::Vector2f position_;
			sf::Vector2f size_;
			gui::Size buttonSize_;
			bool show;
		};
	}
}
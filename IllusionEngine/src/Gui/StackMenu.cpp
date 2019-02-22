#include "StackMenu.h"
#include <iostream>
namespace Illusion
{
	namespace gui
	{
		StackMenu::StackMenu(sf::Vector2f position, std::string buttonNames[],
			Size sizeofButtons, uint stackSize)
			:stackSize_(stackSize)
		{
			font_ = &ResourceManager::getFont("rubik");
			this->position_ = position;

			sf::Vector2f size = gui::getButtonSize(sizeofButtons);

			for (uint i = 0; i < stackSize; ++i)
			{
				buttonMap_.emplace(std::make_pair(buttonNames[i],  //add buttons with their respective names
					new gui::Button(
						sf::Vector2f(position.x, (size.y * i + position.y)), sizeofButtons,
						sf::Color(70, 70, 70, 100),
						sf::Color(90, 90, 90, 100),
						sf::Color(110, 110, 110, 150)))
				);

				buttonMap_[buttonNames[i]]->setText(buttonNames[i], *font_, 0,
					sf::Color(75, 75, 75, 100),
					sf::Color(95, 95, 95, 120),
					sf::Color(110, 110, 110, 140));
			}

		}

		StackMenu::~StackMenu()
		{
			for (auto &b : buttonMap_)
				delete b.second;
		}

		void StackMenu::handleEvents(sf::Event &e)
		{
			for (auto &b : buttonMap_)
				b.second->handleEvents(e);
		}

		void StackMenu::update()
		{
			for (auto &b : buttonMap_)
				b.second->update();
		}

		void StackMenu::draw(sf::RenderTarget &target)
		{
			for (auto &b : buttonMap_)
				b.second->draw(target);
		}

		void StackMenu::setFunctionality(const std::string &id, std::function<void(void)> func)
		{
			buttonMap_[id]->setFunction(func);
		}
	}
}
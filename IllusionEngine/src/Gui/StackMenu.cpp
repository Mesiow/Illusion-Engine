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
			initialize(position, buttonNames, sizeofButtons, stackSize);
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

		void StackMenu::setButtonFunction(const std::string &id, std::function<void(void)> func)
		{
			buttonMap_[id]->setFunction(func);
		}

		void StackMenu::initialize(sf::Vector2f position, std::string buttonNames[], Size sizeofButtons, uint stackSize)
		{
			this->position_ = position;
			sf::Vector2f size = gui::getButtonSize(sizeofButtons);

			for (uint i = 0; i < stackSize; ++i)
			{
				buttonMap_.emplace(std::make_pair(buttonNames[i],  //add buttons with their respective names
					new gui::Button(
						sf::Vector2f(position.x, (size.y * i + position.y)), sizeofButtons,
						/*sf::Color(70, 70, 70, 100),
						sf::Color(90, 90, 90, 100),
						sf::Color(110, 110, 110, 150)*/sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent))
				);

				buttonMap_[buttonNames[i]]->setText(buttonNames[i], *font_, 15,
					sf::Color(130, 130, 130, 200),
					sf::Color(195, 195, 195, 210),
					sf::Color(210, 210, 210, 255));
			}
		}
	}
}
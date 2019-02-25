#include "DropDownList.h"
#include <iostream>
#include <string>

namespace Illusion
{
	namespace gui
	{
		DropDownList::DropDownList(sf::Vector2f position, std::vector<std::string> &list,
			Size buttonsSize, uint activeIndex)
			:show(false)
		{
			activeButton_ = nullptr;
			initialize(position, list, buttonsSize, activeIndex);
		}

		DropDownList::~DropDownList()
		{
			for (auto &b : buttonsList_)
				delete b.second;

			delete activeButton_;
		}

		void DropDownList::handleEvents(sf::Event &e)
		{
			activeButton_->handleEvents(e);

			for (auto &b : buttonsList_)
				b.second->handleEvents(e);
		}

		void DropDownList::update()
		{
			activeButton_->update();

			for (auto &b : buttonsList_)
				b.second->update();
		}

		void DropDownList::draw(sf::RenderTarget &target)
		{
			activeButton_->draw(target);

			if (show)
			{
				for (auto &b : buttonsList_)
					b.second->draw(target);
			}
		}

		void DropDownList::initialize(const sf::Vector2f &position, const std::vector<std::string> &list,
			const Size buttonsSize,  const uint activeIndex)
		{
			sf::Vector2f size = gui::getButtonSize(buttonsSize);

			for (int i = 0; i < list.size(); i++)
			{
				buttonsList_.insert(std::make_pair(
					list[i], new gui::Button(sf::Vector2f(position.x, (size.y * i + position.y)), buttonsSize,
						sf::Color(70, 70, 70, 100),
						sf::Color(90, 90, 90, 100),
						sf::Color(110, 110, 110, 150))
				));

				buttonsList_[list[i]]->setText(list[i], ResourceManager::getFont("rubik"),
					15, sf::Color(70, 70, 70, 200), sf::Color(95, 95, 95, 200), sf::Color(130, 130, 130, 255));
			}

			//create a new button based on the active index one
			activeButton_ = new gui::Button(*buttonsList_[list[activeIndex]]);

			activeButton_->setPosition(sf::Vector2f(activeButton_->getPosition().x, activeButton_->getPosition().y - size.y));
			activeButton_->setFunction([&]() {
				show == true ? show = false : show = true; //show all buttons when clicked
			});

			for (int i = 0; i < list.size(); i++) //make sure active button becomes the button clicked
			{
				buttonsList_[list[i]]->setFunction([=]() {
					activeButton_->setStr(list[i]);
				});
			}

		}

		void DropDownList::setButtonFunction(const std::string &id, std::function<void(void)> func)
		{
			buttonsList_[id]->setFunction(func);
		}
	}
}
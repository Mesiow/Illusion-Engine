#include "../pcHeaders.h"
#include "DropDownList.h"

namespace Illusion
{
	namespace gui
	{
		DropDownList::DropDownList(const sf::Vector2f position, const std::vector<std::string> list,
			Size buttonsSize, uint activeIndex)
			:show(false)
		{
			activeButton_ = nullptr;
			itemList = list;

			initialize(position, buttonsSize, activeIndex);
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

			if (show)
			{
				for (auto &b : buttonsList_)
					b.second->handleEvents(e);
			}
		}

		void DropDownList::update()
		{
			activeButton_->update();

			if (show)
			{
				for (auto &b : buttonsList_)
					b.second->update();
			}
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

		void DropDownList::initialize(const sf::Vector2f &position,
			const Size buttonsSize,  const uint activeIndex)
		{
			sf::Vector2f size = gui::getButtonSize(buttonsSize);


			for (int i = 0; i < itemList.size(); i++)
			{
				buttonsList_.insert(std::make_pair(
					itemList[i], new gui::Button(sf::Vector2f(position.x, (size.y * i + position.y)), buttonsSize,
						sf::Color(70, 70, 70, 100),
						sf::Color(90, 90, 90, 100),
						sf::Color(110, 110, 110, 150))
				));

				buttonsList_[itemList[i]]->setText(itemList[i], ResourceManager::getFont("rubik"),
					15, sf::Color(70, 70, 70, 200), sf::Color(95, 95, 95, 200), sf::Color(130, 130, 130, 255));
			}

			//create a new button based on the active index one
			activeButton_ = new gui::Button(*buttonsList_[itemList[activeIndex]]);

			activeButton_->setPosition(sf::Vector2f(activeButton_->getPosition().x, activeButton_->getPosition().y - size.y));
			activeButton_->setFunction([&]() {
				show == true ? show = false : show = true; //show all buttons when clicked
			});

			for (int i = 0; i < itemList.size(); i++) //make sure active button becomes the button clicked
			{
				buttonsList_[itemList[i]]->setFunction([=]() {
					activeButton_->setStr(itemList[i]);
					show = false; //after selecting option, close the list
				});
			}

		}

		void DropDownList::setButtonFunction(const std::string &id, std::function<void(void)> func)
		{
			buttonsList_[id]->setFunction(func);
		}
	}
}
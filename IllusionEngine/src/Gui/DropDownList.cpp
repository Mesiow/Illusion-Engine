#include "../pcHeaders.h"
#include "DropDownList.h"

namespace Illusion
{
	namespace gui
	{
		DropDownList::DropDownList(const sf::Vector2f position, std::vector<std::string> &list,
			Size buttonsSize, uint activeIndex)
			:show(false)
		{
			this->position_ = position;
			this->buttonSize_ = buttonsSize;
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
			size_ = gui::getButtonSize(buttonsSize);


			for (int i = 0; i < itemList.size(); ++i)
			{
				buttonsList_.insert(std::make_pair(
					itemList[i], new gui::Button(sf::Vector2f(position.x, (size_.y * i + position.y)), buttonsSize,
						sf::Color(70, 70, 70, 100),
						sf::Color(90, 90, 90, 100),
						sf::Color(110, 110, 110, 150))
				));

				buttonsList_[itemList[i]]->setText(itemList[i], ResourceManager::getFont("rubik"),
					15, sf::Color(70, 70, 70, 200), sf::Color(95, 95, 95, 200), sf::Color(130, 130, 130, 255));
			}

			//create a new button based on the active index one
			activeButton_ = new gui::Button(*buttonsList_[itemList[activeIndex]]);

			activeButton_->setPosition(sf::Vector2f(activeButton_->getPosition().x, activeButton_->getPosition().y - size_.y));
			activeButton_->setFunction([&]() {
				show == true ? show = false : show = true; //show all buttons when clicked
			});

			setButtonListFunctions();
		}

		void DropDownList::addToList(const std::string & item)
		{
			buttonsList_.insert(std::make_pair(   //add a new button to the list
				item, new gui::Button(sf::Vector2f(this->position_.x, (size_.y * itemList.size() + this->position_.y)), buttonSize_,
				sf::Color(70, 70, 70, 100),
				sf::Color(90, 90, 90, 100),
				sf::Color(110, 110, 110, 150)
				)));

			buttonsList_[item]->setText(item, ResourceManager::getFont("rubik"), 15,
				sf::Color(70, 70, 70, 200), sf::Color(95, 95, 95, 200), sf::Color(130, 130, 130, 255));

			itemList.push_back(item); //push the new item in

			setButtonListFunctions(); //update the function of the new added button to be able to be selected
		}

		bool DropDownList::removeFromList(const std::string &item)
		{
			if (activeButton_->getString() == item) //check if we try to delete the active button, make sure we cant
				return false;

			if (buttonsList_.find(item) != buttonsList_.end()) //if the item was found in the list delete it
			{
				buttonsList_.erase(item);
				itemList.erase(itemList.end() - 1);
			}
			else
				return false;

			return true;
		}

		bool DropDownList::removeAllFromList()
		{
			for (auto &b : buttonsList_)
			{
				delete b.second;
			}

			if (buttonsList_.empty())
				return true;

			return false;
		}

		void DropDownList::setListPosition(const sf::Vector2f &position)
		{
			activeButton_->setPosition(position);
			for (std::size_t i = 0; i < itemList.size(); ++i)
			{
				buttonsList_[itemList[i]]->setPosition(sf::Vector2f(position.x, (size_.y * i + position.y + size_.y)));
			}
		}

		void DropDownList::setButtonListFunctions()
		{
			for (int i = 0; i < itemList.size(); ++i) //make sure active button becomes the button clicked
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
#include "../pcHeaders.h"
#include "PopUpContainer.h"
#include "../Game.h"

namespace Illusion
{
	namespace gui
	{
		PopUpContainer::PopUpContainer(sf::Vector2f position, sf::Vector2f size,
			sf::Color color, sf::Color outlineColor)
		{
			container_.setSize(size);
			container_.setOrigin(sf::Vector2f(container_.getGlobalBounds().left + container_.getGlobalBounds().width / 2.0f,
				container_.getGlobalBounds().top + container_.getGlobalBounds().height / 2.0f));

			container_.setPosition(position);

			hiddenContainerRect_ = container_;
			hiddenContainerRect_.setFillColor(sf::Color::Red);

			container_.setOutlineThickness(5.0f);
			container_.setFillColor(color);
			container_.setOutlineColor(outlineColor);
		}

		PopUpContainer::~PopUpContainer()
		{

		}

		void PopUpContainer::update()
		{
			showPosition_ = sf::Vector2f(Game::getWindow().getView().getCenter().x + Game::getWindow().getView().getSize().x / 2.1,
				Game::getWindow().getView().getCenter().y - Game::getWindow().getView().getSize().y / 6.0f + 100);

			container_.setPosition(showPosition_);

			for (int i = 0; i < items.size(); i++)
			{
				items[i].setPosition(sf::Vector2f(container_.getPosition().x - container_.getGlobalBounds().width / 2.7,
					container_.getPosition().y - container_.getGlobalBounds().height/2.5 * i));
			}
		}

		void PopUpContainer::handleEvents(sf::Event &e)
		{
			switch (e.type)
			{

			}
		}

		void PopUpContainer::draw(sf::RenderTarget &target)
		{
			target.draw(container_);

			for (auto &i : items)
				target.draw(i);
		}

		void PopUpContainer::addItem(sf::Sprite item)
		{
			items.push_back(item);
		}

		void PopUpContainer::showContainer()
		{
			container_.setPosition(sf::Vector2f(hiddenContainerRect_.getPosition()));
		}

	}
}
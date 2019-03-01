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

		void PopUpContainer::update(float &dt)
		{/*
			showPosition_ = sf::Vector2f(Game::getWindow().getView().getCenter().x + Game::getWindow().getView().getSize().x / 2.1,
				Game::getWindow().getView().getCenter().y - Game::getWindow().getView().getSize().y / 6.0f + 100);*/

			hiddenContainerRect_.setPosition(sf::Vector2f(Game::getWindow().getView().getCenter().x + Game::getWindow().getView().getSize().x / 2.1,
				Game::getWindow().getView().getCenter().y - Game::getWindow().getView().getSize().y / 6.0f + 100));
			
			//if (hidden)
			{
				/*hiddenPosition_ = sf::Vector2f(hiddenContainerRect_.getPosition().x + container_.getGlobalBounds().width,
					hiddenContainerRect_.getPosition().y);

				container_.setPosition(hiddenPosition_);*/
			}
		}

		void PopUpContainer::handleEvents(sf::Event &e)
		{
			if (containsMouse(hiddenContainerRect_.getGlobalBounds()))
			{
				std::cout << "Show container" << std::endl;
				//hidden = false;
				showContainer();
			}

			//if()


			switch (e.type)
			{

			}
		}

		void PopUpContainer::draw(sf::RenderTarget &target)
		{
			target.draw(hiddenContainerRect_);
			target.draw(container_);
		}

		void PopUpContainer::showContainer()
		{
			container_.setPosition(sf::Vector2f(hiddenContainerRect_.getPosition()));
		}

	}
}
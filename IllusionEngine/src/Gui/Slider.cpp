#include "Slider.h"
#include <iostream>

namespace Illusion
{
	namespace gui
	{
		Slider::Slider(sf::Vector2f position)
		{
			this->position_ = position;

			slider_.setSize(sf::Vector2f(20, 30));
			slider_.setOrigin(sf::Vector2f(slider_.getGlobalBounds().left + slider_.getGlobalBounds().width / 2.0f,
				slider_.getGlobalBounds().top + slider_.getGlobalBounds().height / 2.0f));

			slider_.setPosition(position);
			slider_.setFillColor(sf::Color::Green);
			initialize();
		}

		Slider::~Slider()
		{

		}

		void Slider::handleEvents(sf::Event &e)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (containsMouse(slider_.getGlobalBounds()))
				{
					if(onLine())
						moveSlider();
				}
			}

			switch (e.type)
			{
			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					
				}
			}
			break;
			}
		}

		void Slider::update(float &dt)
		{

		}

		void Slider::draw(sf::RenderTarget &target)
		{
			target.draw(line_, 2, sf::Lines); //draw primitives defined by the array of vertices
			target.draw(slider_);
		}

		void Slider::moveSlider()
		{
			slider_.setPosition(sf::Vector2f(getMousePosition().x, line_[0].position.y));
		}

		void Slider::initialize()
		{
			line_[0].position = sf::Vector2f(
				slider_.getPosition().x - slider_.getSize().x * 10, position_.y - slider_.getGlobalBounds().height / slider_.getSize().y/2
			);
			line_[0].color = sf::Color::White;

			line_[1].position = sf::Vector2f(
				slider_.getPosition().x + slider_.getSize().x * 10, position_.y - slider_.getGlobalBounds().height / slider_.getSize().y/2
			);
			line_[1].color = sf::Color::White;
		}

		bool Slider::onLine()
		{
			if (slider_.getPosition().x < line_[0].position.x)  //left vertex point of line
			{
				slider_.setPosition(sf::Vector2f(slider_.getPosition().x + 1, slider_.getPosition().y));
				return false;
			}
			else if (slider_.getPosition().x > line_[1].position.x)//right vertex point of the line
			{
				slider_.setPosition(sf::Vector2f(slider_.getPosition().x - 1, slider_.getPosition().y));
				return false;
			}

			return true;
		}
	}
}
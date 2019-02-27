#include "../pcHeaders.h"
#include "Slider.h"

namespace Illusion
{
	namespace gui
	{
		Slider::Slider(sf::Vector2f position, sf::Vector2f size,
			sf::Color idle, sf::Color hover, sf::Color pressed)
		{
			this->position_ = position;
			colors_[Colors::idleColor] = idle;
			colors_[Colors::hoverColor] = hover;
			colors_[Colors::pressColor] = pressed;
			this->sliderClicked_ = false;


			slider_.setSize(size);
			slider_.setOrigin(sf::Vector2f(slider_.getGlobalBounds().left + slider_.getGlobalBounds().width / 2.0f,
				slider_.getGlobalBounds().top + slider_.getGlobalBounds().height / 2.0f));

			slider_.setPosition(position);
			slider_.setFillColor(colors_[Colors::idleColor]);
			initialize();
		}

		Slider::~Slider()
		{

		}

		void Slider::handleEvents(sf::Event &e)
		{
			flag_ = Flag::idle;

			if (containsMouse(slider_.getGlobalBounds()))
				flag_ = Flag::hover;


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (containsMouse(slider_.getGlobalBounds()))
				{
					sliderClicked_ = true;
					flag_ = Flag::pressed;
					if (onLine())
						moveSlider();
				}
			}
		}

		void Slider::update()
		{
			switch (flag_)
			{
			case Flag::idle:
				slider_.setFillColor(colors_[Colors::idleColor]);
				break;
			case Flag::hover:
				slider_.setFillColor(colors_[Colors::hoverColor]);
				break;

			case Flag::pressed:
				slider_.setFillColor(colors_[Colors::pressColor]);
				break;
			}
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
				slider_.setPosition(sf::Vector2f(slider_.getPosition().x + 5, slider_.getPosition().y));
				return false;
			}
			else if (slider_.getPosition().x > line_[1].position.x)//right vertex point of the line
			{
				slider_.setPosition(sf::Vector2f(slider_.getPosition().x - 5, slider_.getPosition().y));
				return false;
			}

			return true;
		}
	}
}
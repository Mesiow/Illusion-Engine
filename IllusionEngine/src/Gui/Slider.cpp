#include "Slider.h"

namespace Illusion
{
	namespace gui
	{
		Slider::Slider(sf::Vector2f position)
		{
			this->position_ = position;

			slider_.setPosition(position);
			slider_.setFillColor(sf::Color::Green);
			slider_.setSize(sf::Vector2f(5, 30));
			slider_.rotate(180);
			initialize();
		}

		Slider::~Slider()
		{

		}

		void Slider::draw(sf::RenderTarget &target)
		{
			target.draw(line_, 2, sf::Lines); //draw primitives defined by an array of vertices
			target.draw(slider_);
		}

		void Slider::initialize()
		{
			line_[0].position = sf::Vector2f(
				slider_.getPosition().x - slider_.getSize().x * 10, position_.y - slider_.getGlobalBounds().height/2.0f
			);
			line_[0].color = sf::Color::White;

			line_[1].position = sf::Vector2f(
				slider_.getPosition().x + slider_.getSize().x * 10, position_.y - slider_.getGlobalBounds().height/2.0f
			);
			line_[1].color = sf::Color::White;
		}
	}
}
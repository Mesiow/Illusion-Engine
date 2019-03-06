#pragma once

namespace Illusion
{

	class Tile
	{
	public:
		Tile(sf::Vector2f position, sf::Vector2f size, sf::Color color)
		{
			this->tile_.setSize(size);
			this->tile_.setPosition(position);
			this->tile_.setFillColor(color);
			this->position_ = position;
			this->color_ = color;
		}

		void draw(sf::RenderTarget &target)
		{
			target.draw(tile_);
		}

	private:
		sf::RectangleShape tile_;
		sf::Vector2f position_;
		sf::Color color_;
	};
}
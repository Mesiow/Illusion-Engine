#pragma once

namespace Illusion
{

	class Tile
	{
	public:
		Tile(sf::Vector2f position, sf::Vector2f size,
			const sf::Texture &texture, const sf::IntRect &textureRect, sf::Color color,
			unsigned int layerNumber)
			:layerNumber_(layerNumber)
		{
			this->tile_.setTexture(&texture);
			this->tile_.setTextureRect(textureRect);

			this->tile_.setSize(size);
			this->tile_.setPosition(position);
			this->tile_.setFillColor(color);
			this->position_ = position;
			this->color_ = color;
		}

		void draw(sf::RenderTarget &target) { target.draw(tile_); }


		unsigned int getLayerNumber()const { return this->layerNumber_; }


	private:
		sf::RectangleShape tile_;
		sf::Vector2f position_;
		sf::Color color_;

		unsigned int layerNumber_;
	};
}
#include "../pcHeaders.h"
#include "Tile.h"
#include "../Game.h"

namespace Illusion
{
	Tile::Tile(const sf::Vector2f position, const sf::Vector2f size,
		const sf::Texture &texture, const sf::IntRect &textureRect, sf::Color color,
		unsigned short layerNumber)
		:tileRect_(textureRect), layerNumber_(layerNumber)
	{
		this->tile_.setTexture(&texture);
		this->tile_.setTextureRect(textureRect);

		this->tile_.setSize(size);
		this->tile_.setPosition(position);
		this->tile_.setFillColor(color);
		this->position_ = position;
		this->color_ = color;
	}

	Tile::~Tile()
	{

	}

	void Tile::draw(sf::RenderTarget & target)
	{
		target.draw(tile_);
	}
}

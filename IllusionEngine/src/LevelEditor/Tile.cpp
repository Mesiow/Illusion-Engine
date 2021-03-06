#include "../pcHeaders.h"
#include "Tile.h"
#include "../Engine.h"

namespace Illusion
{
	Tile::Tile(const sf::Vector2f position, const sf::Vector2f size,
		const sf::Texture &texture, const sf::IntRect &textureRect, unsigned short layerNumber, bool collider)
		:position_(position), tileRect_(textureRect), layerNumber_(layerNumber), collider_(collider)
	{
		this->tile_.setTexture(&texture);
		this->tile_.setTextureRect(textureRect);

		this->tile_.setSize(size);
		this->tile_.setPosition(position);
		this->tile_.setFillColor(sf::Color::White);
	}

	Tile::~Tile()
	{

	}

	void Tile::draw(sf::RenderTarget & target)
	{
		target.draw(tile_);
	}

	std::string Tile::getTextureRectAsString()
	{
		std::stringstream ss;
		ss << tile_.getTextureRect().left << " " << tile_.getTextureRect().top << " "
			<< tile_.getTextureRect().width << " " << tile_.getTextureRect().height;

		return ss.str();
	}
}

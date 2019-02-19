#include "Tile.h"
#include "../Game.h"

namespace Illusion
{
	Tile::Tile(sf::Texture &texture, const sf::IntRect &textureRect,
		const sf::Vector2f & position, bool scale)
	{
		tile.setTexture(texture);
		setTextureRect(textureRect);

		tile.setPosition(position);

		this->position = position;

		if (scale)
			scaleTexture(texture);
	}
	void Tile::draw(sf::RenderTarget & target)
	{
		target.draw(tile);
	}

	void Tile::scaleTexture(sf::Texture & texture)
	{
		auto texSize = texture.getSize();
		auto windowSize = Game::getWindow().getSize();

		float scaleX = (float)windowSize.x / texSize.x;
		float scaleY = (float)windowSize.y / texSize.y;

		tile.setScale(scaleX, scaleY);
	}

	void Tile::setTextureRect(const sf::IntRect &rect)
	{
		tile.setTextureRect(rect);
	}
}

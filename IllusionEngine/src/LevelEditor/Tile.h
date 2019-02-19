#pragma once
#include <SFML/Graphics.hpp>

namespace Illusion
{
	class Tile
	{
	public:
		Tile(sf::Texture &texture, const sf::IntRect &textureRect,
			const sf::Vector2f &position, bool scale = false);

		void draw(sf::RenderTarget &target);
		

	public:
		sf::Vector2f getPosition()const { return position; }

	private:
		void scaleTexture(sf::Texture &texture);
		void setTextureRect(const sf::IntRect &rect);

	private:
		sf::Sprite tile;
		sf::Vector2f position;
	};
}
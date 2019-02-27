#pragma once

namespace Illusion
{
	class Tile
	{
	public:
		Tile(){}
		Tile(const sf::Texture &texture, const sf::IntRect &textureRect,
			const sf::Vector2f &position, bool scale = false);

		void draw(sf::RenderTarget &target);
		
	public:
		void setPosition(const sf::Vector2f pos) { tile.setPosition(pos); }

	public:
		sf::Vector2f getPosition()const { return position; }

	private:
		void scaleTexture(const sf::Texture &texture);
		void setTextureRect(const sf::IntRect &rect);

	private:
		sf::Sprite tile;
		sf::Vector2f position;
	};
}
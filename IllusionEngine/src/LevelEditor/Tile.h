#pragma once

namespace Illusion
{

	class Tile
	{
	public:
		Tile(const sf::Vector2f position, const sf::Vector2f size,
			const sf::Texture &texture, const sf::IntRect &textureRect, unsigned short layerNumber);
		~Tile();


	public:
		void draw(sf::RenderTarget &target);


	public:
		sf::Vector2f getPosition()const { return this->position_; }
		unsigned short getLayerNumber()const { return this->layerNumber_; }
		const sf::IntRect &getTileRect()const { return this->tileRect_; }

	private:
		sf::RectangleShape tile_;
		const sf::IntRect tileRect_;

		sf::Vector2f position_;

		unsigned short layerNumber_;
	};
}
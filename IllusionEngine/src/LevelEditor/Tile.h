#pragma once

namespace Illusion
{
	class Tile
	{
	public:
		Tile(const sf::Vector2f position, const sf::Vector2f size,
			const sf::Texture &texture, const sf::IntRect &textureRect,
			unsigned short layerNumber, bool collider = false);
		~Tile();

		void draw(sf::RenderTarget &target);

	public://getters
		unsigned short getLayerNumber()const { return this->layerNumber_; }
		bool isCollider()const { return this->collider_; }

		const sf::IntRect &getTileRect()const { return this->tileRect_; }
		sf::Vector2f getPosition()const { return this->position_; }
		sf::FloatRect getGlobalBounds()const { return this->tile_.getGlobalBounds(); }
		std::string getTextureRectAsString();

	private:
		const sf::IntRect tileRect_;
		sf::RectangleShape tile_;
		sf::Vector2f position_;

		unsigned short layerNumber_;
		bool collider_;


	};
}
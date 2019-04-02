#pragma once

namespace Illusion
{
	class TextureSelector
	{
	public:
		TextureSelector(const sf::Texture &sheet, const sf::Vector2f &sheetPos, int textureGridSize);
		~TextureSelector();


		void handleInput(const sf::Vector2f &mouseViewPos);
		void update(const sf::Vector2f &mouseViewPos, const sf::Vector2f &viewPosition);
		void draw(sf::RenderTarget &target, const sf::Vector2f &mouseViewPos);

		void toggle() { active_ == true ? active_ = false : active_ = true; }

	public:
		bool isOverLapping(const sf::FloatRect &otherBounds);
		bool isActive()const { return this->active_; }
		const sf::IntRect &getSelectedRect()const;

	private:
		bool isInTextureBounds(const sf::Vector2f &mouseViewPos);
		
	private:
		sf::Sprite sheet_;
		sf::RectangleShape textureBounds_;
		sf::RectangleShape selector_;

		sf::Vector2u mousePosTextureGrid_;
		sf::IntRect selectedTexture_;

		sf::Text textureRectPos_;

		int textureGridSize_;
		bool active_;
	};
}
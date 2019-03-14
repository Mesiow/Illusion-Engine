#pragma once

namespace Illusion
{
	class TextureSelector
	{
	public:
		TextureSelector(const sf::Texture &sheet, sf::Vector2f sheetPos, int textureGridSize);
		~TextureSelector();


		void handleInput();
		void update(const sf::Vector2f &mouseViewPos);
		void draw(sf::RenderTarget &target);

	public:
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

		int textureGridSize_;
		bool active_;

		sf::Text textureRectPos_;
	};
}
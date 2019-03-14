#pragma once

namespace Illusion
{
	class TextureSelector
	{
	public:
		TextureSelector(const sf::Texture &sheet, sf::Vector2f sheetPos, int textureGridSize);
		~TextureSelector();


		void update(const sf::Vector2f &mouseViewPos);
		void draw(sf::RenderTarget &target);

	public:
		bool isActive()const { return this->active_; }
		
	private:
		sf::Sprite sheet_;
		sf::RectangleShape textureBounds_;
		sf::RectangleShape selector_;
		sf::Vector2u mousePosTextureGrid_;

		int textureGridSize_;
		bool active_;
	};
}
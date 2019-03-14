#pragma once

namespace Illusion
{
	class TextureSelector
	{
	public:
		TextureSelector(const sf::Texture &sheet, sf::Vector2f sheetPos, int textureGridSize);
		~TextureSelector();


		void update(const sf::Vector2f &viewPos);
		void draw(sf::RenderTarget &target);

	public:
		bool isActive()const { return this->active_; }

	private:
		sf::RectangleShape sheet_;
		sf::RectangleShape textureBounds_;
		sf::RectangleShape selector_;

		int textureGridSize_;
		bool active_;
	};
}
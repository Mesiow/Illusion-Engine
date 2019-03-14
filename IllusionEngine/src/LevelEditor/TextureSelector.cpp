#include "../pcHeaders.h"
#include "TextureSelector.h"

namespace Illusion
{
	TextureSelector::TextureSelector(const sf::Texture &sheet, sf::Vector2f sheetPos, int textureGridSize)
	{
		this->textureGridSize_ = textureGridSize;
		this->active_ = false;

		sheet_.setTexture(&sheet);
		sheet_.setPosition(sheetPos);

		textureBounds_.setSize(sf::Vector2f((float)sheet.getSize().x, (float)sheet.getSize().y));
		textureBounds_.setFillColor(sf::Color::Transparent);
		textureBounds_.setOutlineThickness(1.0f);
		textureBounds_.setOutlineColor(sf::Color::Green);
		textureBounds_.setPosition(sheet_.getPosition());

		selector_.setSize(sf::Vector2f((float)textureGridSize, (float)textureGridSize));
		selector_.setFillColor(sf::Color::Transparent);
		selector_.setOutlineThickness(1.0f);
		selector_.setOutlineColor(sf::Color::Red);
	}

	TextureSelector::~TextureSelector()
	{

	}

	void TextureSelector::update(const sf::Vector2f &viewPos)
	{
		if (textureBounds_.getGlobalBounds().contains(static_cast<sf::Vector2f>(viewPos))) //if the mouse is in the bounds of the texture sheet
		{
			selector_.setPosition(sf::Vector2f(float(viewPos.x * textureGridSize_), float(viewPos.y * textureGridSize_)));
			active_ = true;
		}
		active_ = false;
	}

	void TextureSelector::draw(sf::RenderTarget &target)
	{
		target.draw(textureBounds_);
		target.draw(selector_);
		target.draw(sheet_);
	}
}
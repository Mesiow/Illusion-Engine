#include "../pcHeaders.h"
#include "TextureSelector.h"

namespace Illusion
{
	TextureSelector::TextureSelector(const sf::Texture &sheet, sf::Vector2f sheetPos, int textureGridSize)
	{
		this->textureGridSize_ = textureGridSize;
		this->active_ = false;

		sheet_.setTexture(sheet);
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

	void TextureSelector::update(const sf::Vector2f &mouseViewPos)
	{
		if (textureBounds_.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouseViewPos)))
			active_ = true;
		else
			active_ = false;

		if (active_) //if the mouse is in the bounds of the texture sheet
		{
			mousePosTextureGrid_.x = (mouseViewPos.x - textureBounds_.getPosition().x) / textureGridSize_;
			mousePosTextureGrid_.y = (mouseViewPos.y - textureBounds_.getPosition().y) / textureGridSize_;

			selector_.setPosition(sf::Vector2f(textureBounds_.getPosition().x + mousePosTextureGrid_.x * textureGridSize_,
				textureBounds_.getPosition().y + mousePosTextureGrid_.y * textureGridSize_));
		}
	}

	void TextureSelector::draw(sf::RenderTarget &target)
	{
		target.draw(sheet_);
		target.draw(textureBounds_);

		if(active_)
			target.draw(selector_);
	}
}
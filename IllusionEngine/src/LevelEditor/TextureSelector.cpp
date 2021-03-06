#include "../pcHeaders.h"
#include "TextureSelector.h"
#include "../ResourceManagement/ResourceManager.h"

namespace Illusion
{
	TextureSelector::TextureSelector(const sf::Texture &sheet, const sf::Vector2f &sheetPos, int textureGridSize)
	{
		this->textureGridSize_ = textureGridSize;
		this->active_ = false;

		sheet_.setTexture(sheet);
		sheet_.setPosition(sheetPos);

		textureBounds_.setSize(sf::Vector2f((float)sheet.getSize().x, (float)sheet.getSize().y));
		textureBounds_.setFillColor(sf::Color(90, 90, 90, 40));
		textureBounds_.setOutlineThickness(1.0f);
		textureBounds_.setOutlineColor(sf::Color(80, 80, 80, 255));
		textureBounds_.setPosition(sheet_.getPosition());

		selector_.setSize(sf::Vector2f((float)textureGridSize, (float)textureGridSize));
		selector_.setFillColor(sf::Color::Transparent);
		selector_.setOutlineThickness(1.0f);
		selector_.setOutlineColor(sf::Color::Red);

		textureRectPos_.setFont(ResourceManager::getFont("rubik"));
		textureRectPos_.setCharacterSize(15);
		textureRectPos_.setFillColor(sf::Color::White);

		selectedTexture_ = sf::IntRect(0, 0, 0, 0); //no rect selected

	}

	TextureSelector::~TextureSelector()
	{

	}

	void TextureSelector::handleInput(const sf::Vector2f &mouseViewPos)
	{
		if (active_) //if texture selector is active
		{
			if (isInTextureBounds(mouseViewPos)) //if we are in the textures bounds
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //then we can select tiles
				{
					selectedTexture_ = sf::IntRect(mousePosTextureGrid_.x * textureGridSize_,
						mousePosTextureGrid_.y * textureGridSize_,
						textureGridSize_, textureGridSize_); //choose the texture we clicked
				}
			}

		}
	}

	void TextureSelector::update(const sf::Vector2f &mouseViewPos, const sf::Vector2f &viewPosition) //takes view pos to update the position of the sheet
	{
		//if the mouse position is within the texture bounds set true else false
		
		if (active_) //if the selector is active
		{
			textureBounds_.setPosition(viewPosition);
			sheet_.setPosition(textureBounds_.getPosition());
			if (isInTextureBounds(mouseViewPos)) //if the mouse position is within the texture bounds
			{
				mousePosTextureGrid_.x = (mouseViewPos.x - textureBounds_.getPosition().x) / textureGridSize_;
				mousePosTextureGrid_.y = (mouseViewPos.y - textureBounds_.getPosition().y) / textureGridSize_;

				selector_.setPosition(sf::Vector2f(textureBounds_.getPosition().x + mousePosTextureGrid_.x * textureGridSize_,
					textureBounds_.getPosition().y + mousePosTextureGrid_.y * textureGridSize_));

				std::stringstream ss;
				ss << "Texture Rect Position: " << mousePosTextureGrid_.x * textureGridSize_ << ", " << mousePosTextureGrid_.y * textureGridSize_;
				textureRectPos_.setString(ss.str());
				textureRectPos_.setPosition(mouseViewPos.x + 20, mouseViewPos.y + 50);
			}
		}
	}

	void TextureSelector::draw(sf::RenderTarget &target, const sf::Vector2f &mouseViewPos)
	{
		if (active_)
		{
			target.draw(sheet_);
			target.draw(textureBounds_);

			if (isInTextureBounds(mouseViewPos))
			{
				target.draw(selector_);
				target.draw(textureRectPos_);
			}
		}
	}

    bool TextureSelector::isOverLapping(const sf::FloatRect &otherBounds) //check if texture sheet is overlapping tiles or something else
	{
		if (active_)
		{
			if (textureBounds_.getGlobalBounds().intersects(otherBounds)) //if we overlapping something else
				return true;
		}
		return false;
	}

	bool TextureSelector::isInTextureBounds(const sf::Vector2f &mouseViewPos)
	{
		return (textureBounds_.getGlobalBounds().contains(mouseViewPos));
	}

	const sf::IntRect &TextureSelector::getSelectedRect() const
	{
		return this->selectedTexture_;
	}
}
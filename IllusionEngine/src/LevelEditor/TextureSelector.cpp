#include "../pcHeaders.h"
#include "TextureSelector.h"
#include "../ResourceManagement/ResourceManager.h"

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

		textureRectPos_.setFont(ResourceManager::getFont("rubik"));
		textureRectPos_.setCharacterSize(15);
		textureRectPos_.setFillColor(sf::Color::White);

	}

	TextureSelector::~TextureSelector()
	{

	}

	void TextureSelector::handleInput()
	{
		if (active_) //if texture selector is active
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "Selected texture" << std::endl;
				selectedTexture_ = sf::IntRect(mousePosTextureGrid_.x * textureGridSize_, mousePosTextureGrid_.y * textureGridSize_,
					textureGridSize_, textureGridSize_); //choose texture we clicked
			}

		}
	}

	void TextureSelector::update(const sf::Vector2f &mouseViewPos)
	{
		//if the mouse position is within the texture bounds set true else false
		isInTextureBounds(mouseViewPos) ? active_ = true : active_ = false;
		
		if (active_) //if the selector is active
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

	void TextureSelector::draw(sf::RenderTarget &target)
	{
		target.draw(sheet_);
		target.draw(textureBounds_);

		if(active_)
			target.draw(selector_);

		if(active_)
			target.draw(textureRectPos_);
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
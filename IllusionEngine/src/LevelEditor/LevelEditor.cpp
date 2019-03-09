#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Game.h"

namespace Illusion
{
	LevelEditor::LevelEditor(sf::Texture &textureSheet, int gridWidth, int gridHeight, int tileWorldDim)
		:textureSheet_(textureSheet)
	{
		view.reset(sf::FloatRect(0.0f, 0.0f, 
			(float)Game::getWindow().getSize().x, 
			(float)Game::getWindow().getSize().y));
		//view.setCenter(sf::Vector2f(Game::getWindow().getPosition().x, Game::getWindow().getPosition().y));

		map_ = new TileMap(textureSheet, gridWidth, gridHeight, tileWorldDim);

		selector_.setSize(sf::Vector2f(map_->getTileDimension(), map_->getTileDimension()));
		selector_.setFillColor(sf::Color::Transparent);
		selector_.setOutlineThickness(1.0f);
		selector_.setOutlineColor(sf::Color::Green);

		sheetRect_.setSize(sf::Vector2f(textureSheet.getSize().x, textureSheet.getSize().y));
		sheetRect_.setTexture(&textureSheet);
		sheetRect_.setPosition(map_->getBorderPosition().x + map_->getBorderBounds().width + 50,
			map_->getBorderPosition().y / 4.0f);
		sheetRect_.setOutlineThickness(1.0f);
		sheetRect_.setOutlineColor(sf::Color::Green);

	}

	LevelEditor::~LevelEditor()
	{
		delete map_;
	}

	void LevelEditor::moveView(const float x, const float y, const float &dt)
	{
		view.move(x * dt, y * dt);
	}

	void LevelEditor::addTile(const sf::Vector2u &position, const sf::IntRect &rect)
	{
		map_->addTile(position);
	}

	void LevelEditor::deleteTile(const sf::Vector2u &position)
	{
		map_->removeTile(position);
	}

	void LevelEditor::update(sf::RenderTarget &target, sf::Vector2u gridPosition)
	{
		target.setView(view);
		
		updateSelectorRect(gridPosition);
	}

	void LevelEditor::updateSelectorRect(const sf::Vector2u &gridPosition)
	{
		//if we are in tilemap editing bounds
		if(isInLevelBounds(gridPosition))
		{
			selector_.setPosition(sf::Vector2f(gridPosition.x * map_->getTileDimension(),
				gridPosition.y * map_->getTileDimension()));
		}

		auto mousepos = sf::Mouse::getPosition(Game::getWindow());
		auto mouseView = Game::getWindow().mapPixelToCoords(mousepos);

		if (sheetRect_.getGlobalBounds().contains(mouseView)) //if the texture sheet contains the mouse, the selector can go there
		{
			selector_.setPosition(sf::Vector2f(gridPosition.x * map_->getTileDimension(),
				gridPosition.y * map_->getTileDimension()));
		}
		
	}


	void LevelEditor::draw(sf::RenderTarget &target)
	{
		target.draw(sheetRect_);

		map_->draw(target);

		target.draw(selector_);
	}

	bool LevelEditor::isInLevelBounds(const sf::Vector2u & position)
	{
		return (position.x >= 0 && position.x < map_->getWidth()
			&& position.y >= 0 && position.y < map_->getHeight());
	}

}
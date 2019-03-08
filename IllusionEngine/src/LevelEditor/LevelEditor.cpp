#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Game.h"

//TODO: add working view for editor

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


		//if we are in tilemap editing bounds
		if (gridPosition.x >= 0 && gridPosition.x < map_->getWidth()
			&& gridPosition.y >= 0 && gridPosition.y < map_->getHeight())
		{
			selector_.setPosition(sf::Vector2f(gridPosition.x * map_->getTileDimension(),
				gridPosition.y * map_->getTileDimension()));
		}	
	}


	void LevelEditor::drawMap(sf::RenderTarget &target)
	{
		map_->draw(target);

		target.draw(selector_);
	}
}
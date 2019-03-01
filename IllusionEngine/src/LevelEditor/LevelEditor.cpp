#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Game.h"

//TODO: add working view for editor

namespace Illusion
{
	LevelEditor::LevelEditor(const sf::Texture &textureSheet, const int levelGridSize)
		:textureSheet_(textureSheet), gridSize(levelGridSize)
	{
		view.reset(sf::FloatRect(0, 0, Game::getWindow().getSize().x, Game::getWindow().getSize().y));
		//view.setCenter(sf::Vector2f(Game::getWindow().getPosition().x, Game::getWindow().getPosition().y));

		map_ = new TileMap(textureSheet, 40, 40, levelGridSize);
		
	}

	LevelEditor::~LevelEditor()
	{
		delete map_;
	}

	void LevelEditor::moveView(const float x, const float y, const float &dt)
	{
		view.move(x * dt, y * dt);
	}

	void LevelEditor::addTile(const sf::Vector2f &position, const sf::IntRect &rect)
	{
		auto x = position.x / gridSize; //get grid position
		auto y = position.y / gridSize;

		map_->addTile(position, rect, (int)x, (int)y);
	}

	void LevelEditor::deleteTile(const sf::Vector2f &position)
	{
		auto x = position.x / gridSize;
		auto y = position.y / gridSize;

		map_->deleteTile((int)x, (int)y);
	}

	void LevelEditor::update(sf::RenderTarget &target)
	{
		target.setView(view);
	}


	void LevelEditor::drawMap(sf::RenderTarget &target)
	{
		map_->drawGrid(target);
		map_->draw(target);
	}
}
#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Game.h"

//TODO: add working view for editor

namespace Illusion
{
	LevelEditor::LevelEditor(sf::Texture &textureSheet)
		:textureSheet_(textureSheet)
	{
		view.reset(sf::FloatRect(0, 0, Game::getWindow().getSize().x, Game::getWindow().getSize().y));
		//view.setCenter(sf::Vector2f(Game::getWindow().getPosition().x, Game::getWindow().getPosition().y));

		map_ = new TileMap(textureSheet, 20, 20, 32.0f, 32.0f);
		
	}

	LevelEditor::~LevelEditor()
	{
		delete map_;
	}

	void LevelEditor::moveView(const float x, const float y, const float &dt)
	{
		view.move(x * dt, y * dt);
	}

	void LevelEditor::addTile(const sf::Vector2i &position, const sf::IntRect &rect)
	{
		map_->addTile(Tile(sf::Vector2f(8, 8), sf::Color::White), position);
	}

	void LevelEditor::deleteTile(const sf::Vector2f &position)
	{
		map_->deleteTile();
	}

	void LevelEditor::update(sf::RenderTarget &target)
	{
		target.setView(view);
	}


	void LevelEditor::drawMap(sf::RenderTarget &target)
	{
		map_->drawGrid(target);
		target.draw(*map_);
	}
	int LevelEditor::getCellIndex(int x, int y)
	{
		return (y * 32) + x;
	}
}
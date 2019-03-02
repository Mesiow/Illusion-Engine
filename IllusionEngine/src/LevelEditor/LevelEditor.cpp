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

		map_ = new TileMap(textureSheet, 10, 10, 32.0f, 32.0f);
		
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

	}

	void LevelEditor::deleteTile(const sf::Vector2f &position)
	{
		
	}

	void LevelEditor::update(sf::RenderTarget &target)
	{
		target.setView(view);
	}


	void LevelEditor::drawMap(sf::RenderTarget &target)
	{
		target.draw(*map_);
	}
}
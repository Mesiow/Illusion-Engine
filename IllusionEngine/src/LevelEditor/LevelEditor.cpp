#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Game.h"

//TODO: add working view for editor

namespace Illusion
{
	LevelEditor::LevelEditor(sf::Texture &textureSheet, const float levelGridSize)
		:textureSheet_(textureSheet), gridSize(levelGridSize)
	{
		view.reset(sf::FloatRect(0, 0, Game::getWindow().getSize().x, Game::getWindow().getSize().y));
		//view.setCenter(sf::Vector2f(Game::getWindow().getPosition().x, Game::getWindow().getPosition().y));
		
	}

	LevelEditor::~LevelEditor()
	{
		for (std::size_t i = 0; i < tiles.size(); ++i)
			delete tiles[i];
	}

	void LevelEditor::moveView(const float x, const float y, const float &dt)
	{
		view.move(x * dt, y * dt);
	}

	void LevelEditor::addTile(const sf::Vector2f &position, const sf::IntRect &rect)
	{
		//pass in the entire texture sheet by reference and assign the element sprite to a part of the sheet with the wall
		bool add = true;
		if (tiles.size() > 0)
		{
			/*for (std::size_t i = 0; i < tiles.size(); ++i)
			{
				if (tiles[i]->getPosition() == position)
					add = false;
			}*/
		}
		if (add)
			tiles.push_back(new Tile(textureSheet_, sf::IntRect(rect.left * rect.width, rect.top * rect.height, rect.width, rect.height), position)); //add new tile
	}

	void LevelEditor::deleteTile(const sf::Vector2f &position)
	{
		//if (map_[name].empty()) //if there are no elements at the specified level
		//	return;

		//for (std::size_t i = 0; i < map_[name].size(); ++i)
		//{
		//	if (map_[name][i]->getGridPosition(position) == position) //if an element exists at the same position as the mouse in grid space, delete it
		//		map_[name].erase(map_[name].begin() + i); //delete element at position i
		//}
	}

	void LevelEditor::update(sf::RenderTarget &target)
	{
		target.setView(view);
	}


	void LevelEditor::drawTiles(sf::RenderTarget & target)
	{
		for (std::size_t i = 0; i < tiles.size(); ++i)
			tiles[i]->draw(target);
	}
}
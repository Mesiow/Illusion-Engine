#pragma once
#include <SFML/Graphics.hpp>
#include "../ResourceManagement/ResourceManager.h"
#include "Tile.h"
#include <map>
#include <vector>


namespace Illusion
{
	class Game;
	class LevelEditor
	{
	public:
		LevelEditor(sf::Texture &textureSheet, const float levelGridSize);
		~LevelEditor();


	public:
		void moveView(const float x, const float y, const float &dt);
		void addTile(const sf::Vector2f &position, const sf::IntRect &rect = sf::IntRect(0, 0, 32, 32));
		void deleteTile(const sf::Vector2f &position);
		void update(sf::RenderTarget &target);
		void drawTiles(sf::RenderTarget &target);

	public:
		inline const float getGridSize()const { return gridSize; }
		sf::View &getView() { return view; }

	private:
		sf::Texture &textureSheet_;
		std::vector<Tile*> tiles;

		const float gridSize;

		sf::View view;
	};
}
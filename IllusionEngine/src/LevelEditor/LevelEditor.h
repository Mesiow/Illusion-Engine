#pragma once
#include "../ResourceManagement/ResourceManager.h"
#include "TileMap.h"


//TODO: add tilemap

namespace Illusion
{
	class Game;
	class LevelEditor
	{
	public:
		LevelEditor(const sf::Texture &textureSheet, const int levelGridSize);
		~LevelEditor();


	public:
		void moveView(const float x, const float y, const float &dt);
		void addTile(const sf::Vector2f &position, const sf::IntRect &rect = sf::IntRect(0, 0, 32, 32));
		void deleteTile(const sf::Vector2f &position);
		void update(sf::RenderTarget &target);
		void drawMap(sf::RenderTarget &target);

	public:
		inline const float getGridSize()const { return gridSize; }
		sf::View &getView() { return view; }

	private:
		const sf::Texture &textureSheet_;
		TileMap *map_;

		const int gridSize;
		sf::View view;
	};
}
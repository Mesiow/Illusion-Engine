#pragma once
#include "Tile.h"

//load tilemap with tiles once we are done editing

namespace Illusion
{
	class TileMap
	{
	public:
		TileMap(const sf::Texture &sheet, int width, int height, float gridSize);
		~TileMap();

		void addTile(const sf::Vector2f position, const sf::IntRect &rect, int x, int y);
		void deleteTile(int x, int y);

		void draw(sf::RenderTarget &target);
		void drawGrid(sf::RenderTarget &target);


	public:
		int getCellIndex(int x, int y);
		sf::Vector2f getGridPos(float x, float y);

	private:
		const sf::Texture &sheet;
		
		std::vector<sf::RectangleShape> grid_;
		std::vector<Tile> tiles_;
		
		int width_;
		int height_;
		unsigned int layers_;
	};
}
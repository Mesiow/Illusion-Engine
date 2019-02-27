#pragma once
#include "Tile.h"

namespace Illusion
{
	class TileMap
	{
	public:
		TileMap(const sf::Texture &sheet, int width, int height, float gridSize);
		~TileMap();

		void draw(sf::RenderTarget &target);

	private:
		Tile **tiles_;
		int width_;
		int height_;
	};
}
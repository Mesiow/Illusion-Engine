#pragma once
#include "Tile.h"

namespace Illusion
{
	class TileMap : public sf::Drawable
	{
	public:
		TileMap(sf::Texture &sheet, int width, int height,
			float tileTextureDim, float tileWorldDim);
		~TileMap();

		void draw(sf::RenderTarget &target, sf::RenderStates states)const override;

		void drawGrid(sf::RenderTarget &target);

	public:
		void addTile(Tile tile, sf::Vector2i pos);
		void deleteTile();

	private:
		void addTileVertices(Tile &tile, sf::Vector2f pos);

		int getCellIndex(int x, int y)
		{
			return (y * width_) + x;
		}

	private:
		std::vector<sf::RectangleShape> grid_;
		const sf::Texture &sheet_;
		sf::VertexArray *array_; //used to generate vertices of the map

		int width_;
		int height_;

		float tileTextureDim_; //how big a tile is in the texture sheet, 32 pixels by 32 pixels
		float tileWorldDim_; //how big we want to draw our tiles to the screen
	};
}
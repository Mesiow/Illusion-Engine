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

	private:
		void addTileVertices(Tile tile, sf::Vector2f pos);

	private:
		const sf::Texture &sheet_;
		sf::VertexArray *array_; //used to generate vertices of the map

		int width_;
		int height_;

		float tileTextureDim_; //how big a tile is in the texture sheet, 32 pixels by 32 pixels
		float tileWorldDim_; //how big we want to draw our tiles to the screen
	};
}
#pragma once
#include "Tile.h"

namespace Illusion
{
	class TileMap
	{
		
		public:
			TileMap(const std::string &path, sf::Texture &sheet, int width, int height,
				int tileTextureDim, int tileWorldDim);
			~TileMap();

		public:
			void draw(sf::RenderTarget &target);

			void initTiles(int width, int height);
			void addTile(sf::Vector2u position);
			void removeTile(sf::Vector2u position);

    	public:
			bool loadMap(const std::string &path);
			bool saveMap();

	    public:
			Tile &getTileAtIndex(int index);
			int getTileIndex(int x, int y);
			int getTileDimension()const { return tileWorldDim_; }
			bool isInGrid(const sf::Vector2u &position);

    	public:
			int getWidth()const { return width_; }
			int getHeight()const { return height_; }
		    sf::Vector2f getBorderPosition()const { return border_.getPosition(); }
			sf::FloatRect getBorderBounds()const { return border_.getGlobalBounds(); }

		private:
			std::vector<Tile*> tiles_;
			sf::RectangleShape border_;

			sf::Texture &sheet_;

			int mapSize_;
			int width_;
			int height_;

			int tileWorldDim_;
			int tileTextureDim_;

		};
}
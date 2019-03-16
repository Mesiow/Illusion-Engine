#pragma once
#include "Tile.h"

#define MAX_LAYERS 32

namespace Illusion
{
	class TileMap
	{
		public:
			TileMap(sf::Texture &sheet, unsigned int width, unsigned int height, int tileWorldDim);
			~TileMap();

		public:
			void draw(sf::RenderTarget &target);

			void initTiles(unsigned int width, unsigned int height);
			void addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned int layer);
			void removeTile(const sf::Vector2u &position);

			void addLayer(unsigned int layer);
			void removeLayer(unsigned int layer);

    	public:
			bool loadMap(const std::string &path);
			bool saveMap();


	    public: //setters
			void setCurrentLayer(unsigned int layer);

	    public://getters
			Tile &getTileAtIndex(int index);
			int getTileIndex(int x, int y);
			int getTileDimension()const { return tileWorldDim_; }

			bool isInGrid(const sf::Vector2u &position);
			bool doesLayerExist(unsigned int layer);


    	public:
			unsigned int getWidth()const { return width_; }
			unsigned int getHeight()const { return height_; }

		    sf::Vector2f getBorderPosition()const { return border_.getPosition(); }
			sf::FloatRect getBorderBounds()const { return border_.getGlobalBounds(); }
			//////////////

		private:
			std::vector<Tile*> tiles_;
			sf::RectangleShape border_;
			sf::Texture &sheet_;


			std::bitset<MAX_LAYERS> layerBitMask_;

			unsigned int mapSize_;
			unsigned int width_;
			unsigned int height_;
			unsigned int layerIndex_;

			int tileWorldDim_;
			int tileTextureDim_;

		};
}
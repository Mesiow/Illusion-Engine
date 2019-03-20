#pragma once
#include "Tile.h"

#define MAX_LAYERS 10

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
			void addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned short layer);
			void removeTile(const sf::Vector2u &position);

			void addLayer();
			void removeLayer();

    	public:
			bool loadMap(const std::string &path);
			bool saveMap(const std::string &name);


	    public: //setters
			void setCurrentLayer(unsigned int layer);
			void setLayerCount(unsigned int count);

	    public://getters
			Tile &getTileAtIndex(int index);
			int getTileIndex(int x, int y);
			int getTileDimension()const { return tileWorldDim_; }
			unsigned int getLayerCount()const { return layerCount_; }

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
			std::vector<Tile*> switchtiles_;
			sf::RectangleShape border_;
			sf::Texture &sheet_;


			//std::bitset<MAX_LAYERS> layerBitMask_;
			std::vector<std::bitset<MAX_LAYERS>> layerBitMask_; //00000000  layer 1
			                                                    //00000000  layer 2
			                                                    //00000000  layer 3

			unsigned int mapSize_;
			unsigned int width_;
			unsigned int height_;
			unsigned short layerIndex_;
			unsigned short layerCount_;

			int tileWorldDim_;
			int tileTextureDim_;

		};
}
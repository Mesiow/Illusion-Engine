#pragma once
#include "Layer.h"

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
			void initTilesAndLayers(unsigned int width, unsigned int height);

			void addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned short layer);
			void removeTile(const sf::Vector2u &position, unsigned short currentLayer);

			void addLayer();
			void removeLayer();

    	public:
			bool loadMap(const std::string &path);
			bool saveMap(const std::string &name);


	    public://getters
			//Tile &getTileAtIndex(int index);
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
			std::vector<Layer*> layers_; //layers that hold tiles to render other tiles on top of other layers
			//std::vector<Tile*> tiles_;
			sf::RectangleShape border_;
			sf::Texture &sheet_;
			

			unsigned int mapSize_;
			unsigned int width_;
			unsigned int height_;
			unsigned short layerCount_;

			int tileWorldDim_;
			int tileTextureDim_;

		};
}
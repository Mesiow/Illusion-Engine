#pragma once
#include "Layer.h"
#include "../Utils/UtilityFunctions.h"

#define MAX_LAYERS 10

namespace Illusion
{
	struct MapData
	{
		std::string sheetPath;
		sf::Vector2f tileGridPosition;
		sf::IntRect tileRect;

		unsigned int width;
		unsigned int height;
		unsigned int tileDim;
		unsigned int tilesInMap;
		unsigned short layerCount;
		unsigned short tileLayerNumber;
		bool collider;
	};

	class TileMap
	{
	public:
		TileMap(){} //default constructor if client just wants to create a tilemap obj and load an already existing map
		TileMap(sf::Texture &sheet, unsigned int width, unsigned int height, int tileWorldDim);
		~TileMap();

		public:
			void draw(sf::RenderTarget &target);

			void addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned short layer, bool collider);
			void removeTile(const sf::Vector2u &position, unsigned short currentLayer);

			void addLayer();
			void addLayer(int index);
			void removeLayer();

    	public:
			//2nd parameter is used for if we are loading without passing the texture into the constructor that takes one such as in gamestate
			bool loadMap(const std::string &mapPath, sf::Texture *mapTextureSheet = nullptr);
			bool saveMap(const std::string &mapPath, const std::string &textureSheetPath);

	   private:
		   void initLayersAndTiles(unsigned int width, unsigned int height);
		   void parseMap(std::ifstream &file, MapData &data, const std::string &path);
		   void freeLayersAndTiles()const;
		   void clearMapVariables();


	    public://getters
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
			sf::RectangleShape border_;
			sf::Texture *sheet_;
			

			unsigned int mapSize_;
			unsigned int width_;
			unsigned int height_;
			unsigned int tileCount_;
			unsigned short layerCount_;

			int tileWorldDim_;
			int tileTextureDim_;

		};
}
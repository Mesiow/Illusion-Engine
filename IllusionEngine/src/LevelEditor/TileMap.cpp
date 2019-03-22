#include "../pcHeaders.h"
#include "TileMap.h"
namespace Illusion
{


	TileMap::TileMap(sf::Texture &sheet, unsigned int width, unsigned int height, int tileWorldDim)
		:sheet_(sheet)
	{
		this->tileWorldDim_ = tileWorldDim;
		this->width_ = width;
		this->height_ = height;
		this->layerCount_ = 0;

		//initTiles(width, height);
		initTilesAndLayers(width, height);

		border_.setSize(sf::Vector2f(float(width * tileWorldDim), float(height * tileWorldDim))); //calculate size of entire map/level
		border_.setPosition(0, 0);
		border_.setFillColor(sf::Color::Transparent);
		border_.setOutlineThickness(1.0f);
		border_.setOutlineColor(sf::Color::Green);
	}

	TileMap::~TileMap()
	{
		for (std::size_t i = 0; i < layers_.size(); i++)
		{
			if (layers_[i] != nullptr) //delete if not already null
				delete layers_[i];
		}
	}


	void TileMap::draw(sf::RenderTarget &target)
	{
		target.draw(border_);
		for (std::size_t i = 0; i < layers_.size(); ++i)
		{
			if(layers_[i]!=nullptr)
				layers_[i]->drawTiles(target);
		}
	}


	void TileMap::initTiles(unsigned int width, unsigned int height)
	{
		//tiles_.resize(width * height, nullptr); //resize grid with nullptrs
	}

	void TileMap::initTilesAndLayers(unsigned int width, unsigned int height)
	{
		layers_.resize(MAX_LAYERS, nullptr);
		
		//init tiles for the first layer
		layers_[0] = new Layer();
		layers_[0]->initTiles(width, height, 1); //pass in width and height to get the number of tiles for the entire map
		layerCount_++;
	}

	void TileMap::addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned short layer)
	{
		if (isInGrid(position))
		{
			int index = getTileIndex(position.x, position.y);
			int layerIndex = layer - 1;

			if (doesLayerExist(layerIndex)) //-1 because it starts at one and we check the index
			{
				if (layers_[layerIndex]->getTiles()[index] == nullptr) //if at a certain layer the tile there is null we can add
				{
					std::cout << "Adding tile to layer: " << layer << std::endl; //add a tile at the specified index according to the grid position passed in
					layers_[layerIndex]->getTiles()[index] = new Tile(sf::Vector2f(float(position.x * tileWorldDim_), float(position.y * tileWorldDim_)),
						sf::Vector2f((float)tileWorldDim_, (float)tileWorldDim_),
						sheet_, rect, sf::Color::White, layer);
				}
			}

		}
	}

	void TileMap::removeTile(const sf::Vector2u &position, unsigned short currentLayer) //remove tile at the current layer we are on
	{	
		if (isInGrid(position))
		{
			//index of tile to delete
			int index = getTileIndex(position.x, position.y);
			int layerIndex = currentLayer - 1; //index of layer
			
			if (layers_[layerIndex]->getTiles()[index] != nullptr)
			{
				std::cout << "removing tile" << std::endl;
				delete layers_[layerIndex]->getTiles()[index];
				layers_[layerIndex]->getTiles()[index] = nullptr;
			}
		}
	}

	void TileMap::addLayer()
	{
		layers_[layerCount_] = new Layer();
		layers_[layerCount_]->initTiles(this->width_, this->height_, layerCount_);
		layerCount_++;
	}

	void TileMap::removeLayer()
	{
		delete layers_[layerCount_ - 1]; //free the layer
		layerCount_--;
	}

	bool TileMap::loadMap(const std::string &path)
	{
		return false;
	}

	bool TileMap::saveMap(const std::string &name)
	{
		/*
		Saving Format:

		texture sheet,
		width, height,
		tileDimension
		
		*/

		std::ofstream outFile(name);

		if (!outFile.is_open())
		{
			throw(name + "failed to open");
			return false;
		}

		std::string sheetPath = "test";
		unsigned int width = this->width_;
		unsigned int height = this->height_;
		unsigned int tileDim = this->tileWorldDim_;

		if (outFile)
			outFile << sheetPath << width << height << tileDim; //write data into file

		outFile.close();
		return true;
	}


	int TileMap::getTileIndex(int x, int y)
	{
		return (y * width_) + x;
	}

	bool TileMap::isInGrid(const sf::Vector2u & position)
	{
		return (position.x >= 0 && position.x < width_
			&& position.y >= 0 && position.y < height_);
	}

	bool TileMap::doesLayerExist(unsigned int layer)
	{
		return layers_[layer] != nullptr ? true : false;
	}
}

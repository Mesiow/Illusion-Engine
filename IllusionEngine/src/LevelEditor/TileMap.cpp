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
		this->layerIndex_ = 0;
		this->layerCount_ = 0;

		addLayer();

		initTiles(width, height);
		border_.setSize(sf::Vector2f(float(width * tileWorldDim), float(height * tileWorldDim))); //calculate size of entire map/level
		border_.setPosition(0, 0);
		border_.setFillColor(sf::Color::Transparent);
		border_.setOutlineThickness(1.0f);
		border_.setOutlineColor(sf::Color::Green);
	}

	TileMap::~TileMap()
	{
		for (std::size_t i = 0; i < tiles_.size(); i++)
		{
			if (tiles_[i] != nullptr) //delete if not already null
				delete tiles_[i];
		}
	}


	void TileMap::draw(sf::RenderTarget &target)
	{
		target.draw(border_);
		if (tiles_.size() > 0)
		{
			for (std::size_t i = 0; i < tiles_.size(); ++i)
			{
				if (tiles_[i] != nullptr) //draw if there is a tile
					tiles_[i]->draw(target);
			}
		}
	}

	void TileMap::initTiles(unsigned int width, unsigned int height)
	{
		tiles_.resize(width * height, nullptr); //resize grid with nullptrs
	}

	void TileMap::addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned int layer)
	{
		if (isInGrid(position))
		{
			int index = getTileIndex(position.x, position.y);

			if (tiles_[index] == nullptr) //if there is space to add a tile
			{
				if (doesLayerExist(layer))
				{
					std::cout << "Adding tile to layer: "<<layer<< std::endl; //add a tile at the specified index according to the grid position passed in
					tiles_[index] = new Tile(sf::Vector2f(float(position.x * tileWorldDim_), float(position.y * tileWorldDim_)),
						sf::Vector2f((float)tileWorldDim_, (float)tileWorldDim_),
						sheet_, rect, sf::Color::White, layer);
				}
			}
		}
	}

	void TileMap::removeTile(const sf::Vector2u &position)
	{	
		//if we are trying to remove a tile within map space
		if (isInGrid(position))
		{
			//index of tile to delete
			int index = getTileIndex(position.x, position.y);

			if (tiles_[index] != nullptr)
			{
				std::cout << "Deleting tile from layer "<<layerCount_<< std::endl;
				delete tiles_[index]; //free tile
				tiles_[index] = nullptr; //set tile at index to null
			}
		}
	}

	void TileMap::addLayer()
	{
		//if(layerIndex_ == 0)
		if (layerBitMask_[layerIndex_] == 0)
		{
			layerBitMask_.set(layerIndex_, 1); //turn layer on
			layerIndex_++;
			std::cout << "Layer index: " << layerIndex_ << std::endl;
		}

		if (layerCount_ >= MAX_LAYERS)
			return;

		layerCount_++;
	}

	void TileMap::removeLayer()
	{
		//layerIndex - 1 because we will never remove layer 1 and the index is one less than the size
		if (layerBitMask_[layerIndex_ - 1] == 1) //if there is an active layer
		{
			layerBitMask_.set(layerIndex_ - 1, 0); //turn it off
			std::cout << "Layer index: " << layerIndex_ - 1 << std::endl;
			layerIndex_--;
		}
		else
		{
			std::cout << "Remove layer error, index: " << layerIndex_ - 1 << std::endl;
		}

		if (layerCount_ <= 1) 
			return;

		layerCount_--;
		
	}

	bool TileMap::loadMap(const std::string &path)
	{
		return false;
	}

	bool TileMap::saveMap()
	{
		return false;
	}

	void TileMap::setCurrentLayer(unsigned int layer)
	{
		layerIndex_ = layer;
	}

	void TileMap::setLayerCount(unsigned int count)
	{
		//if(isInLayerRange(count))
			layerCount_ = count;
	}

	Tile &TileMap::getTileAtIndex(int index)
	{
		return *tiles_[index];
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
		//minus 1 for index
		return layerBitMask_[layer - 1] == 1 ? true : false; //if layer is 0 it does not exist else it does
	}
}

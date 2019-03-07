#include "../pcHeaders.h"
#include "TileMap.h"
namespace Illusion
{


	TileMap::TileMap(const std::string &path, sf::Texture &sheet, int width, int height, 
		int tileTextureDim, int tileWorldDim)
		:sheet_(sheet)
	{
		this->tileWorldDim_ = tileWorldDim;
		this->tileTextureDim_ = tileTextureDim;
		this->width_ = width;
		this->height_ = height;
		this->mapSize_ = width * height;
		initTiles(width, height);
		border_.setSize(sf::Vector2f(mapSize_, mapSize_));
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

	void TileMap::initTiles(int width, int height)
	{
		tiles_.resize(width * height, nullptr); //resize grid with nullptrs
	}

	void TileMap::addTile(sf::Vector2u position)
	{
		if (isInGrid(position))
		{
			int index = getTileIndex(position.x, position.y);

			tiles_[index] = new Tile(sf::Vector2f(position.x * tileWorldDim_, position.y * tileWorldDim_),
				sf::Vector2f(tileWorldDim_, tileWorldDim_),
				sf::Color::White); //add a tile at the specified index according to the grid position passed in
		}
	}

	void TileMap::removeTile(sf::Vector2u position)
	{
		if (tiles_.size() > 0)
		{
			//if we are trying to place a tile within map space
			if (isInGrid(position))
			{
				int index = getTileIndex(position.x, position.y);

				if (tiles_[index] != nullptr)
				{
					delete tiles_[index]; //free tile
					tiles_[index] = nullptr; //set tile at index to null
				}
			}
		}
	}

	bool TileMap::loadMap(const std::string & path)
	{
		return false;
	}

	bool TileMap::saveMap()
	{
		return false;
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




	//void TileMap::addTileVertices(Tile &tile, sf::Vector2f pos)
	//{
	//	//first parameter is the position of the vertex and the second is the texture coordinates

	//	//first vertex at 0,0 , top left
	//	//vertex added to position to give us an offset
	//	//vertex multiplied by tileWorldDim determines how big the tile will draw on screen

	//	array_->append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + pos) * tileWorldDim_,
	//		sf::Vector2f(tileTextureDim_ * tile.position.x, tileTextureDim_ * tile.position.y))); //32 times position which is 0 so the top left, 32 times 1 for the y

	//	//second vertex at top right 1,0
	//	array_->append(sf::Vertex((sf::Vector2f(1.0f, 0.0f) + pos) * tileWorldDim_,
	//		sf::Vector2f(tileTextureDim_ * tile.position.x + tileTextureDim_, tileTextureDim_ * tile.position.y)));

	//	//third vertex at bottom right, 1,1
	//	array_->append(sf::Vertex((sf::Vector2f(1.0f, 1.0f) + pos) * tileWorldDim_, 
	//		sf::Vector2f(tileTextureDim_ * tile.position.x + tileTextureDim_, tileTextureDim_ * tile.position.y + tileTextureDim_)));

	//	//fourth vertex at bottom left, 0,1
	//	array_->append(sf::Vertex((sf::Vector2f(0.0f, 1.0f) + pos) * tileWorldDim_,
	//		sf::Vector2f(tileTextureDim_ * tile.position.x, tileTextureDim_ * tile.position.y + tileTextureDim_)));
	//}
}

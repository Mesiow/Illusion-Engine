#include "../pcHeaders.h"
#include "TileMap.h"
namespace Illusion
{


	TileMap::TileMap(const std::string &path, sf::Texture &sheet, int width, int height, 
		int tileTextureDim, int tileWorldDim)
		:sheet_(sheet), tileWorldDim_(tileWorldDim)
	{
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
		
	}


	void TileMap::draw(sf::RenderTarget &target)
	{
		target.draw(border_);
		if (tiles_.size() > 0)
		{
			for (std::size_t i = 0; i < tiles_.size(); ++i)
				tiles_[i].draw(target);
		}
	}

	void TileMap::initTiles(int width, int height)
	{
		tiles_.reserve(width * height);
	}

	void TileMap::addTile(sf::Vector2u position)
	{
		tiles_.push_back(
			Tile(
			sf::Vector2f(position.x * tileWorldDim_, position.y * tileWorldDim_),
			sf::Vector2f(tileWorldDim_, tileWorldDim_),
			sf::Color::White)
		);
	}

	void TileMap::removeTile(sf::Vector2u position)
	{
		if (tiles_.size() > 0)
		{
			int index = getTileIndex(position.x / tileWorldDim_, position.y / tileWorldDim_);
			tiles_.erase(tiles_.begin() + index);
		}
	}

	Tile &TileMap::getTileAtIndex(int index)
	{
		return tiles_[index];
	}

	int TileMap::getTileIndex(int x, int y)
	{
		return (y * width_) + x;
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

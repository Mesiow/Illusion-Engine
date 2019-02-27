#include "../pcHeaders.h"
#include "TileMap.h"

namespace Illusion
{
	TileMap::TileMap(const sf::Texture &sheet, int width, int height, float gridSize)
	{
		this->width_ = width;
		this->height_ = height;

		//size of each tile in pixels
		auto sizeX = sheet.getSize().x / 16; //32
		auto sizeY = sheet.getSize().y / 16; //32 - size of each tile

		tiles_ = new Tile*[width];

		for (int x = 0; x < width; x++)
		{
			tiles_[x] = new Tile[height];
			for (int y = 0; y < height; y++)
			{
				tiles_[x][y] = Tile(sheet, sf::IntRect(sizeX * 5, sizeY * 7, sizeX, sizeY), 
					sf::Vector2f(x * (int)gridSize, y * (int)gridSize));
			}
		}
			

	}

	TileMap::~TileMap()
	{
		for (int x = 0; x < width_; x++)
			delete[] tiles_[x];  //delete array and pointers to tiles

		delete tiles_; //delete pointer that points to the array of pointer tiles
	}

	void TileMap::draw(sf::RenderTarget & target)
	{
		for (int x = 0; x < width_; ++x)
		{
			for (int y = 0; y < height_; ++y)
			{
				tiles_[x][y].draw(target);
			}
		}
	}
}
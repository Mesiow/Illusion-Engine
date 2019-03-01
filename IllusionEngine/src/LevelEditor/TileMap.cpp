#include "../pcHeaders.h"
#include "TileMap.h"

namespace Illusion
{
	TileMap::TileMap(const sf::Texture &sheet, int width, int height, float gridSize)
		:sheet(sheet)
	{
		this->width_ = width;
		this->height_ = height;

		//size of each tile in pixels
		auto sizeX = sheet.getSize().x / 16; //32
		auto sizeY = sheet.getSize().y / 16; //32 - size of each tile

		tiles_.resize(width * height);
		grid_.resize(width * height);

		//visible grid
		for (int x = 0; x < width; x++)
		{
			//grid_.push_back(sf::RectangleShape(sf::Vector2f(gridSize, gridSize)));
			for (int y = 0; y < height; y++)
			{
				//grid_.push_back(sf::RectangleShape(sf::Vector2f(gridSize, gridSize)));
				grid_[getCellIndex(x, y)] = sf::RectangleShape(sf::Vector2f(gridSize, gridSize));
				grid_[getCellIndex(x, y)].setFillColor(sf::Color::Transparent);
				grid_[getCellIndex(x, y)].setOutlineThickness(1.f);
				grid_[getCellIndex(x, y)].setOutlineColor(sf::Color::Green);
				grid_[getCellIndex(x, y)].setPosition(sf::Vector2f(x * (int)gridSize, y * (int)gridSize));
			}
		}
			
	}

	TileMap::~TileMap()
	{
		
	}

	void TileMap::addTile(const sf::Vector2f position, const sf::IntRect & rect, int x, int y)
	{
		if (x < 0 || x >= width_ || y < 0 || y >= height_) //check out of bounds in grid space
		{
			std::cout << "outside of grid" << std::endl;
			return;
		}

		tiles_[getCellIndex(x,y)] = Tile(this->sheet, rect, getGridPos(x,y));
	}

	void TileMap::deleteTile(int x, int y)
	{
		int index = getCellIndex(x, y);
		std::cout << "Cell index: " << index << std::endl;

		if (index < 0 || index > tiles_.size())
			return;

		auto it = tiles_.begin() + index;
		std::cout << "Erasing tile at: " << it->getPosition().x << ", " << it->getPosition().y << std::endl;
		tiles_.erase(tiles_.begin() + index); //erase tile at index
	}

	void TileMap::draw(sf::RenderTarget & target)
	{
		for (int i = 0; i < tiles_.size(); ++i)
		{
			tiles_[i].draw(target);
		}
	}

	void TileMap::drawGrid(sf::RenderTarget & target)
	{
		for (int i = 0; i < grid_.size(); ++i)
		{
			target.draw(grid_[i]);	
		}
	}

	int TileMap::getCellIndex(int x, int y)
	{
		return (y * width_) + x;
	}

	sf::Vector2f TileMap::getGridPos(float x, float y)
	{
		auto xpos = x * 32; //get size of one tile and multiply it by grid position x
		auto ypos = y * 32;

		return sf::Vector2f(xpos, ypos);
	}
}
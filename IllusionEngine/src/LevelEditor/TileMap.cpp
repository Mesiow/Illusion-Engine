#include "../pcHeaders.h"
#include "TileMap.h"

namespace Illusion
{
	TileMap::TileMap(sf::Texture &sheet, int width, int height, float tileTextureDim, float tileWorldDim)
		:sheet_(sheet)
	{
		this->width_ = width;
		this->height_ = height;
		this->tileTextureDim_ = tileTextureDim;
		this->tileWorldDim_ = tileWorldDim;

		//width * height = how many tiles we have in our tile map and times 4 because 
		//we have 4 vertices per tile because each tile is a quad
		array_ = new sf::VertexArray(sf::Quads, (std::size_t)width * height * 4);

		Tile tile(sf::Vector2f(0, 1), sf::Color::White);

		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				addTileVertices(tile, sf::Vector2f((float)x, float(y)));
			}
		}
	}

	TileMap::~TileMap()
	{

	}

	void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states)const
	{
		states.texture = &sheet_; //give the render state our texture
		target.draw(*array_, states); //draw the vertex array
	}

	void TileMap::addTileVertices(Tile tile, sf::Vector2f pos)
	{
		//first parameter is the position of the vertex and the second is the texture coordinates

		//first vertex at 0,0 , top left
		//vertex added to position to give us an offset
		//vertex multiplied by tileWorldDim determines how big the tile will draw on screen
		array_->append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + pos) * tileWorldDim_, 
			sf::Vector2f(tileTextureDim_ * tile.position.x, tileTextureDim_ * tile.position.y))); //32 times position which is 0 so the top left, 32 times 1 for the y

		//second vertex at top right 1,0
		array_->append(sf::Vertex((sf::Vector2f(1.0f, 0.0f) + pos) * tileWorldDim_,
			sf::Vector2f(tileTextureDim_ * tile.position.x + tileTextureDim_, tileTextureDim_ * tile.position.y)));

		//third vertex at bottom right, 1,1
		array_->append(sf::Vertex((sf::Vector2f(1.0f, 1.0f) + pos) * tileWorldDim_, 
			sf::Vector2f(tileTextureDim_ * tile.position.x + tileTextureDim_, tileTextureDim_ * tile.position.y + tileTextureDim_)));

		//fourth vertex at bottom left, 0,1
		array_->append(sf::Vertex((sf::Vector2f(0.0f, 1.0f) + pos) * tileWorldDim_,
			sf::Vector2f(tileTextureDim_ * tile.position.x, tileTextureDim_ * tile.position.y + tileTextureDim_)));
	}
}
#pragma once

#include "Tile.h"
namespace Illusion
{
	class Layer
	{
	public:
		Layer() 
		{

		}
		~Layer()
		{
			for (std::size_t i = 0; i < tiles_.size(); i++)
			{
				if (tiles_[i] != nullptr) //delete if not already null
					delete tiles_[i];
			}
		}

		void initTiles(unsigned int width, unsigned int height, int layer)
		{
			this->layerNmber_ = layer;
			tiles_.resize(width * height, nullptr);
		}

		void drawTiles(sf::RenderTarget &target)
		{
			for (std::size_t i = 0; i < tiles_.size(); ++i)
			{
				if (tiles_[i] != nullptr)
					tiles_[i]->draw(target);
			}
		}


	public:
		std::vector<Tile*> &getTiles() { return tiles_; }
		int getLayerNumber()const { return layerNmber_; }

	private:
		std::vector<Tile*> tiles_;
		int layerNmber_;
	};
}
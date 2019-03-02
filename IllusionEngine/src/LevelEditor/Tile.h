#pragma once

namespace Illusion
{

	class Tile
	{
	public:
		Tile(sf::Vector2f position, sf::Color color)
		{
			this->position = position;
			this->color = color;
		}

		sf::Vector2f position;
		sf::Color color;
	};
}
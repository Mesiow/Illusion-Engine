#pragma once
#include "../ResourceManagement/ResourceManager.h"
#include "TileMap.h"
#include "../Gui/PopUpContainer.h"

namespace Illusion
{
	class Game;
	class LevelEditor
	{
	public:
		LevelEditor(sf::Texture &textureSheet, int gridWidth, int gridHeight, int tileWorldDim);
		~LevelEditor();

	public:
		void moveView(const float x, const float y, const float &dt);
		void addTile(const sf::Vector2u &position, const sf::IntRect &rect = sf::IntRect(0, 0, 32, 32));
		void deleteTile(const sf::Vector2u &position);
		void update(sf::RenderTarget &target, sf::Vector2u gridPosition=sf::Vector2u(0,0));
		void drawMap(sf::RenderTarget &target);

	public:
		int getGridDimension()const { return map_->getTileDimension(); }
		sf::View &getView() { return view; }

	private:
		sf::Texture &textureSheet_;
		TileMap *map_;

		gui::PopUpContainer *tileSelectionContainer_;
		sf::RectangleShape selector_;

		sf::View view;
	};
}
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
		void zoomView(float z);
		void addTile(const sf::Vector2u &position, const sf::IntRect &rect = sf::IntRect(0, 0, 32, 32));
		void deleteTile(const sf::Vector2u &position);
		void update(sf::RenderTarget &target, sf::Vector2u gridPosition=sf::Vector2u(0,0));
		void updateSelectorRect(const sf::Vector2u &gridPosition);
		void updateText();
		void draw(sf::RenderTarget &target);


		void initTextureSheetRect();
		void initText(const int gridWidth, const int gridHeight, const int tileWorldDim);


	public:
		bool isInLevelBounds(const sf::Vector2u &position);
		bool isInTextureSheetBounds(const sf::Vector2u &position);

		int getMapTileDimension()const { return map_->getTileDimension(); }
		sf::View &getView() { return view; }

	private:
		sf::RectangleShape sheetRect_; //shows all the tiles in the texture we can use
		sf::RectangleShape sheetBorderRect_;
		gui::PopUpContainer *tileSelectionContainer_;
		sf::RectangleShape selector_;


		sf::Texture &textureSheet_; //actual texture sheet
		TileMap *map_;

		sf::View view;

		sf::Text mapSizeText_;
		sf::Text tileDimText_;


	};
}
#pragma once
#include "../ResourceManagement/ResourceManager.h"
#include "TileMap.h"
#include "TextureSelector.h"
#include "../Gui/Button.h"
#include "../Gui/DropDownList.h"
#include "../Utils/UtilityFunctions.h"

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

		void handleEvents(sf::Event &e);
		void handleInput(const sf::Vector2u &mousePosGrid, const float &dt);
		void update(sf::RenderTarget &target, const sf::Vector2u &gridPosition=sf::Vector2u(0,0),
			const sf::Vector2f &mouseViewPos=sf::Vector2f(0,0));
		void draw(sf::RenderTarget &target);

		//Gui
		void updateGui();
		void drawGui(sf::RenderTarget &target);

	public:
		const sf::IntRect &getCurrentSelectedTexture()const;
		bool isInLevelBounds(const sf::Vector2u &position);
		int getMapTileDimension()const { return map_->getTileDimension(); }
		sf::View &getView() { return view; }

	private:
		void initGui();
		void initText(const int gridWidth, const int gridHeight, const int tileWorldDim);
		void updateText();
		void drawText(sf::RenderTarget &target);

		void initTextureSelector();
		void updateSelectorRect(const sf::Vector2u &gridPosition);
		void setSelectorTexture();



	private:
		//Gui
		gui::DropDownList *listOfLayers_;
		gui::Button *addLayerButton_;
		gui::Button *removeLayerButton_;
		////
		
		TextureSelector *textureSelector_;
		sf::RectangleShape selector_;

		TileMap *map_;
		sf::Texture &textureSheet_; //actual texture sheet
		sf::View view;

		//Text
		sf::Text mapSizeText_;
		sf::Text tileDimText_;
		sf::Text layerCountText_;
		////


		sf::Clock loadClock_;
		float loadTime_ = 0.2f; //1 second
		bool begin_ = false;
	};
}
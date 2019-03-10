#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Game.h"

namespace Illusion
{
	LevelEditor::LevelEditor(sf::Texture &textureSheet, int gridWidth, int gridHeight, int tileWorldDim)
		:textureSheet_(textureSheet)
	{
		view.reset(sf::FloatRect(0.0f, 0.0f,
			(float)Game::getWindow().getSize().x,
			(float)Game::getWindow().getSize().y));
		//view.setCenter(sf::Vector2f(Game::getWindow().getPosition().x, Game::getWindow().getPosition().y));

		map_ = new TileMap(textureSheet, gridWidth, gridHeight, tileWorldDim);

		selector_.setSize(sf::Vector2f((float)map_->getTileDimension(), (float)map_->getTileDimension()));
		selector_.setFillColor(sf::Color(100, 100, 100, 220));
		selector_.setTexture(&textureSheet);
		selector_.setOutlineThickness(1.0f);
		selector_.setOutlineColor(sf::Color::Green);

		initText(gridWidth, gridHeight, tileWorldDim);
		initTextureSheetRect();
	}

	LevelEditor::~LevelEditor()
	{
		delete map_;
	}

	void LevelEditor::moveView(const float x, const float y, const float &dt)
	{
		view.move(x * dt, y * dt);
	}

	void LevelEditor::zoomView(float z)
	{
		view.zoom(z);
	}

	void LevelEditor::addTile(const sf::Vector2u &position, const sf::IntRect &rect)
	{
		map_->addTile(position, rect);
	}

	void LevelEditor::deleteTile(const sf::Vector2u &position)
	{
		map_->removeTile(position);
	}

	void LevelEditor::update(sf::RenderTarget &target, sf::Vector2u gridPosition)
	{
		target.setView(view);

		updateText();
		
		updateSelectorRect(gridPosition);
	}

	void LevelEditor::updateSelectorRect(const sf::Vector2u &gridPosition)
	{
		//if we are in tilemap editing bounds
		if(isInLevelBounds(gridPosition))
		{
			selector_.setPosition(sf::Vector2f(gridPosition.x * map_->getTileDimension(),
				gridPosition.y * map_->getTileDimension()));
		}


		if (isInTextureSheetBounds(gridPosition)) //if mouse over texture sheet
		{
			selector_.setPosition(sf::Vector2f(gridPosition.x * map_->getTileDimension(),
				gridPosition.y * map_->getTileDimension()));
		}
	}

	void LevelEditor::updateText()
	{
		mapSizeText_.setPosition(view.getCenter().x - view.getSize().x / 2 + mapSizeText_.getGlobalBounds().width - mapSizeText_.getGlobalBounds().width + mapSizeText_.getCharacterSize(),
			view.getCenter().y + view.getSize().y / 2 - mapSizeText_.getGlobalBounds().height - mapSizeText_.getCharacterSize());

		tileDimText_.setPosition(view.getCenter().x + view.getSize().x / 2 - tileDimText_.getGlobalBounds().width - tileDimText_.getCharacterSize(),
			view.getCenter().y + view.getSize().y/2 - tileDimText_.getGlobalBounds().height - tileDimText_.getCharacterSize() - tileDimText_.getCharacterSize()/3);
	}


	void LevelEditor::draw(sf::RenderTarget &target)
	{
		target.draw(sheetBorderRect_);
		target.draw(sheetRect_);

		map_->draw(target);

		target.draw(selector_);

		target.draw(mapSizeText_);
		target.draw(tileDimText_);
	}

	void LevelEditor::initTextureSheetRect()
	{
		sheetBorderRect_.setSize(sf::Vector2f((float)textureSheet_.getSize().x /*+ map_->getTileDimension()*/,
			(float)textureSheet_.getSize().y/* + map_->getTileDimension()*/));
		//sheetBorderRect_.setOrigin(sf::Vector2f(sheetBorderRect_.getGlobalBounds().width / 2.0f, sheetBorderRect_.getGlobalBounds().height / 2.0f));

		sheetBorderRect_.setPosition(sf::Vector2f(map_->getBorderPosition().x + map_->getBorderBounds().width + map_->getTileDimension() * 2, 
			map_->getBorderPosition().y));
		sheetBorderRect_.setFillColor(sf::Color::Transparent);
		sheetBorderRect_.setOutlineThickness(1.0f);
		sheetBorderRect_.setOutlineColor(sf::Color::Green);

		sheetRect_.setSize(sf::Vector2f((float)textureSheet_.getSize().x, (float)textureSheet_.getSize().y));
		sheetRect_.setTexture(&textureSheet_);
		sheetRect_.setOrigin(sf::Vector2f(sheetRect_.getGlobalBounds().width / 2.0f, sheetRect_.getGlobalBounds().height / 2.0f));
		sheetRect_.setPosition(sf::Vector2f(sheetBorderRect_.getPosition().x + sheetBorderRect_.getGlobalBounds().width/2.0f,
			sheetBorderRect_.getPosition().y + sheetBorderRect_.getGlobalBounds().height/2.0f));
	}

	void LevelEditor::initText(const int gridWidth, const int gridHeight, const int tileWorldDim)
	{
		mapSizeText_.setFont(ResourceManager::getFont("rubik"));
		mapSizeText_.setCharacterSize(15);
		mapSizeText_.setString(std::string("TileMap Size: ") + std::to_string(gridWidth) + " x " + std::to_string(gridHeight));
		mapSizeText_.setPosition(50.0f, (float)Game::getWindow().getSize().y - 15);

		tileDimText_.setFont(ResourceManager::getFont("rubik"));
		tileDimText_.setCharacterSize(15);
		tileDimText_.setString(std::string("Tile Dimensions: ") + std::to_string(tileWorldDim) + " x " + std::to_string(tileWorldDim));
		tileDimText_.setPosition(Game::getWindow().getSize().x - tileDimText_.getGlobalBounds().width, Game::getWindow().getSize().y);
	}

	void LevelEditor::setSelectorTexture(const sf::IntRect &rect)
	{
		selector_.setTextureRect(rect);
	}

	bool LevelEditor::isInLevelBounds(const sf::Vector2u & position)
	{
		return (position.x >= 0 && position.x < map_->getWidth()
			&& position.y >= 0 && position.y < map_->getHeight());
	}

	bool LevelEditor::isInTextureSheetBounds(const sf::Vector2u & position)
	{
		return (position.x >= sheetBorderRect_.getPosition().x / map_->getTileDimension()
			&& position.x <= sheetBorderRect_.getPosition().x / map_->getTileDimension() + sheetBorderRect_.getGlobalBounds().width / map_->getTileDimension()//check X axis
			&& position.y >= sheetBorderRect_.getPosition().y / map_->getTileDimension() //check Y axis
			&& position.y <= sheetBorderRect_.getPosition().y / map_->getTileDimension() + sheetBorderRect_.getGlobalBounds().height / map_->getTileDimension());
	}

}
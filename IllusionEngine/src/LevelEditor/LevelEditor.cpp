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
		selector_.setTextureRect(sf::IntRect(0, 0, 0, 0)); //empty rect when we start
		selector_.setOutlineThickness(1.0f);
		selector_.setOutlineColor(sf::Color::Green);

		initText(gridWidth, gridHeight, tileWorldDim);
		initTextureSelector();

		loadClock_.restart();
	}

	LevelEditor::~LevelEditor()
	{
		delete textureSelector_;
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

	void LevelEditor::handleInput(const sf::Vector2u &mousePosGrid, const float &dt)
	{
		if (loadClock_.getElapsedTime().asSeconds() >= loadTime_)
			begin_ = true;

		if (begin_)
		{
			textureSelector_->handleInput(); //handle texture selector input

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //handle view input
				moveView(0.0f, -400.0f, dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				moveView(-400.0f, 0.0f, dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				moveView(0.0f, 400.0f, dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				moveView(400.0f, 0.0f, dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //handle adding and deleting tiles
			{
				if (getCurrentSelectedTexture() == sf::IntRect(0, 0, 0 ,0)) //check if current selected rect is empty, if it is we cannot add tiles
					return;

				addTile(mousePosGrid, getCurrentSelectedTexture());
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				deleteTile(mousePosGrid);
		}
		
	}

	void LevelEditor::update(sf::RenderTarget &target, const sf::Vector2u &gridPosition, const sf::Vector2f &mouseViewPos)
	{
		target.setView(view);

		updateText();
		
		updateSelectorRect(gridPosition);

		textureSelector_->update(mouseViewPos);
	}

	void LevelEditor::updateSelectorRect(const sf::Vector2u &gridPosition)
	{
		//if we are in tilemap editing bounds
		setSelectorTexture();
		if (isInLevelBounds(gridPosition))
		{
			selector_.setPosition(sf::Vector2f((float)gridPosition.x * map_->getTileDimension(),
				(float)gridPosition.y * map_->getTileDimension()));
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

		map_->draw(target);

		target.draw(selector_);
		textureSelector_->draw(target);

		target.draw(mapSizeText_);
		target.draw(tileDimText_);
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
		tileDimText_.setPosition(float(Game::getWindow().getSize().x - tileDimText_.getGlobalBounds().width), (float)Game::getWindow().getSize().y);
	}

	void LevelEditor::initTextureSelector()
	{
		textureSelector_ = new TextureSelector(textureSheet_, sf::Vector2f(map_->getBorderPosition().x - map_->getBorderBounds().width / 1.5, map_->getBorderPosition().y),
			map_->getTileDimension());
	}

	void LevelEditor::setSelectorTexture()
	{
		selector_.setTextureRect(textureSelector_->getSelectedRect());
	}

	const sf::IntRect &LevelEditor::getCurrentSelectedTexture()const
	{
		return selector_.getTextureRect();
	}

	bool LevelEditor::isInLevelBounds(const sf::Vector2u & position)
	{
		return (position.x >= 0 && position.x < map_->getWidth()
			&& position.y >= 0 && position.y < map_->getHeight());
	}
}
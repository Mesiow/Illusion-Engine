#include "../pcHeaders.h"
#include "LevelEditor.h"
#include "../Engine.h"

namespace Illusion
{
	LevelEditor::LevelEditor(sf::Texture &textureSheet, int gridWidth, int gridHeight, int tileWorldDim)
		:textureSheet_(textureSheet)
	{
		this->activeEditor_ = true;
		camera_ = new Camera(sf::FloatRect(0.0f, 0.0f, (float)Engine::getWindow().getSize().x, (float)Engine::getWindow().getSize().y));

		map_ = new TileMap(textureSheet, gridWidth, gridHeight, tileWorldDim);

		selector_.setSize(sf::Vector2f((float)map_->getTileDimension(), (float)map_->getTileDimension()));
		selector_.setFillColor(sf::Color(100, 100, 100, 220));
		selector_.setTexture(&textureSheet);
		selector_.setTextureRect(sf::IntRect(0, 0, 0, 0)); //empty rect when we start
		selector_.setOutlineThickness(1.0f);
		selector_.setOutlineColor(sf::Color::Green);

		initGui();
		initText(gridWidth, gridHeight, tileWorldDim);
		initTextureSelector();

		loadClock_.restart();
	}

	LevelEditor::~LevelEditor()
	{
		freeGui();
		delete camera_;
		delete textureSelector_;
		delete map_;
	}

	void LevelEditor::addTile(const sf::Vector2u &position, const sf::IntRect &rect)
	{
		//add tile
		map_->addTile(position, rect, this->getActiveLayer(), this->tileCollideFlag_);
	}

	void LevelEditor::deleteTile(const sf::Vector2u &position)
	{
		map_->removeTile(position, this->getActiveLayer()); //remove tile at the active layer selected
	}

	void LevelEditor::loadLevel(const std::string &path)
	{
		if (map_->getCurrentLevelPath() == path)
			std::cerr << "Level already loaded" << std::endl;
		else if (map_->loadMap(path)) //if map was loaded
		{
			//start at layer 2 because one is already set
			 for (std::size_t i = 2; i <= map_->getLayerCount(); i++) //update the gui when loading in the map
			 {
				 listOfLayers_->addToList(std::string("Layer ") + std::to_string(i)); //load layer count to the list
				 layerCountText_.setString(std::string("Layers: ") + std::to_string(i)); //update layer count text when we add a layer
			 }
		}
	}

	void LevelEditor::saveLevel(const std::string &name, const std::string &texturePath)
	{
		map_->saveMap(name, texturePath);
	}

	void LevelEditor::handleEvents(sf::Event &e)
	{
		addLayerButton_->handleEvents(e);
		removeLayerButton_->handleEvents(e);

		listOfLayers_->handleEvents(e);
		textureSelectorButton_->handleEvents(e);
	}

	void LevelEditor::handleInput(const sf::Vector2u &mousePosGrid, const float &dt)
	{
		if (loadClock_.getElapsedTime().asSeconds() >= loadTime_)
			begin_ = true;

		if (begin_)
		{
			textureSelector_->handleInput(util::mouse::mousePositions::mousePosView); //handle texture selector input

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //handle view input
				camera_->move(0.0f, -400.0f, dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				camera_->move(-400.0f, 0.0f, dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				camera_->move(0.0f, 400.0f, dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				camera_->move(400.0f, 0.0f, dt);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && util::time::keyTime::checkKeyTime())
				tileCollideFlag_ == true ? tileCollideFlag_ = false : tileCollideFlag_ = true; //change flag for tile collision
				
			if (activeEditor_)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //handle adding and deleting tiles
				{
					if (getCurrentSelectedTexture() != sf::IntRect(0, 0, 0, 0)) //check if current selected rect is empty, if it is we cannot add tiles
						addTile(mousePosGrid, getCurrentSelectedTexture());
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					deleteTile(mousePosGrid);
			}
		}
		
	}

	void LevelEditor::update(sf::RenderTarget &target, const sf::Vector2u &gridPosition, const sf::Vector2f &mouseViewPos)
	{
		camera_->update(target);

		updateGui();

		updateText();
		
		updateSelectorRect(gridPosition);

		textureSelector_->update(mouseViewPos, sf::Vector2f(camera_->getCenter().x - camera_->getSize().x/2.2f - 50.0f,
			camera_->getCenter().y - camera_->getSize().y/2.5f));

		if (textureSelector_->isOverLapping(map_->getBorderBounds()))
			activeEditor_ = false;
		else
			activeEditor_ = true;
	}

	void LevelEditor::updateSelectorRect(const sf::Vector2u &gridPosition)
	{
		//if we are in tilemap editing bounds
		if (activeEditor_) //if the editor is active at the moment
		{
			setSelectorTexture();
			if (isInLevelBounds(gridPosition))
			{
				selector_.setPosition(sf::Vector2f((float)gridPosition.x * map_->getTileDimension(),
					(float)gridPosition.y * map_->getTileDimension()));
			}
		}
	}

	void LevelEditor::updateText()
	{
		mapSizeText_.setPosition(camera_->getCenter().x - camera_->getSize().x / 2 + mapSizeText_.getGlobalBounds().width - mapSizeText_.getGlobalBounds().width + mapSizeText_.getCharacterSize(),
			camera_->getCenter().y + camera_->getSize().y / 2 - mapSizeText_.getGlobalBounds().height - mapSizeText_.getCharacterSize());

		tileDimText_.setPosition(camera_->getCenter().x + camera_->getSize().x / 2 - tileDimText_.getGlobalBounds().width - tileDimText_.getCharacterSize(),
			camera_->getCenter().y + camera_->getSize().y/2 - tileDimText_.getGlobalBounds().height - tileDimText_.getCharacterSize() - tileDimText_.getCharacterSize()/3);

		layerCountText_.setPosition(camera_->getCenter().x - camera_->getSize().x / 2 + layerCountText_.getGlobalBounds().width - layerCountText_.getGlobalBounds().width + layerCountText_.getCharacterSize(),
			camera_->getCenter().y + camera_->getSize().y / 2 - layerCountText_.getGlobalBounds().height - layerCountText_.getCharacterSize() * 2);
	}

	void LevelEditor::drawText(sf::RenderTarget &target)
	{
		target.draw(mapSizeText_);
		target.draw(tileDimText_);
		target.draw(layerCountText_);

		util::drawToScreen(std::string("Collider: ") + std::to_string(tileCollideFlag_),
			sf::Vector2f(util::mouse::mousePositions::mousePosView.x + 30, util::mouse::mousePositions::mousePosView.y + 30));
	}


	void LevelEditor::draw(sf::RenderTarget &target)
	{
		map_->draw(target);

		if(activeEditor_)
			target.draw(selector_);

		textureSelector_->draw(target, util::mouse::mousePositions::mousePosView);

		drawText(target);
		drawGui(target);
	}

	void LevelEditor::updateGui()
	{
		//update positions of gui elements
		addLayerButton_->setPosition(sf::Vector2f(camera_->getCenter().x + camera_->getSize().x / 2.0f - addLayerButton_->getBounds().width, camera_->getCenter().y - 350));
		removeLayerButton_->setPosition(sf::Vector2f(camera_->getCenter().x + camera_->getSize().x / 2.0f - removeLayerButton_->getBounds().width, camera_->getCenter().y - 300));
		listOfLayers_->setListPosition(sf::Vector2f(camera_->getCenter().x + camera_->getSize().x / 2.0f - listOfLayers_->getActiveButton()->getBounds().width - 20, camera_->getCenter().y - 200));
		textureSelectorButton_->setPosition(sf::Vector2f(camera_->getCenter().x - camera_->getSize().x / 2.0f + 20.0f, camera_->getCenter().y - camera_->getSize().y / 2.0f + 20.0f));

		addLayerButton_->update();
		removeLayerButton_->update();

		listOfLayers_->update();
		textureSelectorButton_->update();
	}

	void LevelEditor::drawGui(sf::RenderTarget &target)
	{
		addLayerButton_->draw(target);
		removeLayerButton_->draw(target);

		listOfLayers_->draw(target);
		textureSelectorButton_->draw(target);
	}

	void LevelEditor::freeGui()const
	{
		delete listOfLayers_;
		delete addLayerButton_;
		delete removeLayerButton_;
		delete textureSelectorButton_;
	}

	void LevelEditor::initText(const int gridWidth, const int gridHeight, const int tileWorldDim)
	{
		mapSizeText_.setFont(ResourceManager::getFont("rubik"));
		mapSizeText_.setCharacterSize(15);
		mapSizeText_.setString(std::string("TileMap Size: ") + std::to_string(gridWidth) + " x " + std::to_string(gridHeight));
		mapSizeText_.setPosition(50.0f, (float)Engine::getWindow().getSize().y - 15);

		tileDimText_.setFont(ResourceManager::getFont("rubik"));
		tileDimText_.setCharacterSize(15);
		tileDimText_.setString(std::string("Tile Dimensions: ") + std::to_string(tileWorldDim) + " x " + std::to_string(tileWorldDim));
		tileDimText_.setPosition(float(Engine::getWindow().getSize().x - tileDimText_.getGlobalBounds().width), (float)Engine::getWindow().getSize().y);

		layerCountText_.setFont(ResourceManager::getFont("rubik"));
		layerCountText_.setCharacterSize(15);
		layerCountText_.setString(std::string("Layers: ") + std::to_string(map_->getLayerCount()));
		layerCountText_.setPosition(50.0f, (float)Engine::getWindow().getSize().y - 30);
	}


	void LevelEditor::initGui()
	{
		std::vector<std::string> list{ "Layer 1" };
		listOfLayers_ = new gui::DropDownList(sf::Vector2f(camera_->getCenter().x + camera_->getSize().x / 2 - 100, camera_->getCenter().y), list, gui::Size::Small, 0);

		addLayerButton_ = new gui::Button(sf::Vector2f(map_->getBorderPosition().x + 100, map_->getBorderPosition().y - 100), gui::Size::Small);

		addLayerButton_->setText(std::string("Add Layer"), ResourceManager::getFont("rubik"), 20,
			sf::Color(90, 90, 90, 150), sf::Color(140, 140, 140, 220), sf::Color(190, 190, 190, 255));

		addLayerButton_->setFunction([&]() {
			map_->addLayer(); //add layer to tilemap
			listOfLayers_->addToList(std::string("Layer ") + std::to_string(map_->getLayerCount())); //then add it to the list
			layerCountText_.setString(std::string("Layers: ") + std::to_string(map_->getLayerCount())); //update layer count text when we add a layer
			});

		removeLayerButton_ = new gui::Button(sf::Vector2f(map_->getBorderPosition().x + map_->getBorderBounds().width / 4, map_->getBorderPosition().y - 50.0f),
			gui::Size::Small);

		removeLayerButton_->setText(std::string("Remove Layer"), ResourceManager::getFont("rubik"), 20,
			sf::Color(90, 90, 90, 150), sf::Color(140, 140, 140, 220), sf::Color(190, 190, 190, 255));

		removeLayerButton_->setFunction([&]() {

			if (listOfLayers_->removeFromList(std::string("Layer ") + std::to_string(map_->getLayerCount())) == true) //removes latest layer from the list first
				map_->removeLayer(); //if we are trying to remove the active layer, prohibit that

			layerCountText_.setString(std::string("Layers: ") + std::to_string(map_->getLayerCount()));
			});

		textureSelectorButton_ = new gui::Button(sf::Vector2f(50.0f, 50.0f), gui::Size::Small,
			sf::Color(70, 70, 70, 120), sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255));

		textureSelectorButton_->setText(std::string("Texture Sheet"), ResourceManager::getFont("rubik"), 20,
			sf::Color(90, 90, 90, 150), sf::Color(140, 140, 140, 220), sf::Color(190, 190, 190, 255));

		textureSelectorButton_->setFunction([&]() {
			textureSelector_->toggle();
		});
	}

	void LevelEditor::initTextureSelector()
	{
		textureSelector_ = new TextureSelector(textureSheet_, sf::Vector2f(map_->getBorderPosition().x - map_->getBorderBounds().width / 1.5f, map_->getBorderPosition().y),
			map_->getTileDimension());
	}

	void LevelEditor::setSelectorTexture()
	{
		selector_.setTextureRect(textureSelector_->getSelectedRect());
	}

	unsigned short LevelEditor::getActiveLayer()
	{
		// extract layer number out of layer string
		std::size_t delPos = util::string::getDelimiterPos(listOfLayers_->getActiveButton()->getString(), " ");
		std::string subStr = util::string::getSubStr(listOfLayers_->getActiveButton()->getString(), " ", delPos + 1, listOfLayers_->getActiveButton()->getString().size());

		return std::stoi(subStr);
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
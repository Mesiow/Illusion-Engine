#include "../pcHeaders.h"
#include "EditorState.h"
#include "../Game.h"
#include "MenuState.h"

namespace Illusion
{
	EditorState::EditorState(Game &game)
		:State(game)
	{
	    initKeyBinds();
		initGui();
		initText();
		//editor_ = new LevelEditor(ResourceManager::getTexture("dungeon"));
	}

	EditorState::~EditorState()
	{
		delete this->editor_;

		for (auto &i : options_)
			delete i.second;

		delete createButton_;
		delete backButton_;
	}

	void EditorState::handleInput()
	{
		if (sf::Mouse::isButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//editor_->addTile(_mousePosGrid, sf::IntRect(32 * 6, 32 * 8, 32, 32));
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				//editor_->deleteTile(_mousePosGrid);
			}
		}
	}

	void EditorState::handleInput(const float &dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			editor_->moveView(0.0f, -200.0f, dt);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			editor_->moveView(-200.0f, 0.0f, dt);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			editor_->moveView(0.0f, 200.0f, dt);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			editor_->moveView(200.0f, 0.0f, dt);
	}

	void EditorState::handleEvents(sf::Event &e)
	{
		for (auto &i : options_)
			i.second->handleEvents(e); //handle gui events

		for (auto &b : buttons_)
			b.handleEvents(e);

		switch (e.type)
		{
		case sf::Event::MouseButtonReleased:
		{
			/*if (e.mouseButton.button == sf::Mouse::Right)
			{
				editor_->deleteTile(_mousePosGrid);
			}*/
		}
		break;

		case sf::Event::KeyPressed:
		{
		 if (e.key.code == Keyboard::getCurrentKeyBinds().at("BACK"))
			{
				_game->changeState<MenuState>(*_game);
			}
		}
		break;
		}
	}

	void EditorState::update(float &dt)
	{
		//ResourceManager::loadTexture("dungeon", "res/Assets/Dungeon_Tileset.png");
	}

	void EditorState::update(sf::RenderTarget &target)
	{

		//editor_->update(target, _mousePosGrid);

		updateMousePositions();
		//updateMouseGridPosition(editor_->getGridDimension());
		
		updateGui();
	}

	void EditorState::draw(sf::RenderTarget &target)
	{
	//	editor_->drawMap(target);

		for (auto &i : options_)
			i.second->draw(target); //draw options gui , drop down list

		for (auto &text : optionsTexts_)
			target.draw(text);

		for (auto &b : buttons_)
			b.draw(target);


		showMouseCoordinates();
	}

	void EditorState::initKeyBinds()
	{
			std::fstream file("res/Input/editor_state_key_binds.ini");

			if (!file.is_open())
				throw("File failed to open key binds");

			keyMapBinds map;

			std::string action;
			std::string key;

			while (!file.eof())
			{
				file >> action >> key;
				map[action] = Keyboard::getSupportedKeys().at(key); //map action to supported key at location key in supported key map
			}

			file.close();

			Keyboard::addKeyBinds(map);
			Keyboard::printBoundKeys();
	}

	void EditorState::initGui()
	{
		const std::vector<std::string> mapSizes{ "64 x 64", "48 x 48", "32 x 32" };
		options_["Map_Sizes"] = new gui::DropDownList(sf::Vector2f(150, 200), mapSizes, gui::Size::Small, 0);


		const std::vector<std::string> gridDimensions{ "32", "16" };
		options_["Grid_Dimensions"] = new gui::DropDownList
		(
			sf::Vector2f(245 + gui::getButtonSize(gui::Size::Small).x, 200),
			gridDimensions, gui::Size::Small, 0
		);


		const std::vector<std::string> sheets{ "Dungeon_Tileset.png" };
		options_["Texture_Sheets"] = new gui::DropDownList
		(
			sf::Vector2f(490 + gui::getButtonSize(gui::Size::Small).x, 200),
			sheets, gui::Size::Small, 0
		);

		createButton_ = new gui::Button(sf::Vector2f(Game::getWindow().getSize().x - 50, Game::getWindow().getSize().y - 50), gui::Size::Small);
		createButton_->setText(std::string("Create"), ResourceManager::getFont("rubik"), 20,
			sf::Color(70, 70, 70, 200), sf::Color(100, 100, 100, 230), sf::Color(150, 150, 150, 255));

		buttons_.push_back(*createButton_);

		backButton_ = new gui::Button(sf::Vector2f(50, Game::getWindow().getSize().y - 50),
			gui::Size::Small);
		backButton_->setText(std::string("Back"), ResourceManager::getFont("rubik"), 20,
			sf::Color(70, 70, 70, 200), sf::Color(100, 100, 100, 230), sf::Color(150, 150, 150, 255));

		buttons_.push_back(*backButton_);

	}

	void EditorState::initText()
	{
		//Map Size
		mapSizeText_.setFont(ResourceManager::getFont("rubik"));
		mapSizeText_.setString(std::string("Grid Size"));
		mapSizeText_.setCharacterSize(15);
		mapSizeText_.setFillColor(sf::Color(85, 85, 85, 225));

		{
			auto button = options_["Map_Sizes"]->getActiveButton();
			mapSizeText_.setPosition(sf::Vector2f(
				button->getPosition().x + button->getBounds().width / 3.2f,
				button->getPosition().y - button->getBounds().height - 25)
			);
		}
		optionsTexts_.push_back(mapSizeText_);
		
		//Tile Dim

		tileDimText_ = mapSizeText_;
		tileDimText_.setString(std::string("Tile Dimension"));

		{
			auto button = options_["Grid_Dimensions"]->getActiveButton();
			tileDimText_.setPosition(sf::Vector2f(
				button->getPosition().x + button->getBounds().width / 4.5f,
				button->getPosition().y - button->getBounds().height - 25)
			);
		}
		optionsTexts_.push_back(tileDimText_);

		//Texture

		textureLoadText_ = mapSizeText_;
		textureLoadText_.setString("Texture Sheet");
		
		{
			auto button = options_["Texture_Sheets"]->getActiveButton();
			textureLoadText_.setPosition(sf::Vector2f(
				button->getPosition().x + button->getBounds().width / 4.5f,
				button->getPosition().y - button->getBounds().height - 25)
			);
		}
		optionsTexts_.push_back(textureLoadText_);
	}

	void EditorState::updateGui()
	{
		for (auto &i : options_)
			i.second->update();

		for (auto &b : buttons_)
			b.update();
	}
}
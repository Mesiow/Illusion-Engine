#include "../../pcHeaders.h"
#include "EditorState.h"
#include "../../Engine.h"
#include "../MenuState.h"

namespace Illusion
{
	EditorState::EditorState(Engine &game, sf::Texture &sheet, int mapWidth, int mapHeight, int tileDim)
		:State(game)
	{
		initKeyBinds();
		initGui();

		editor_ = new LevelEditor(sheet, mapWidth, mapHeight, tileDim);
		this->paused_ = false;
	}

	EditorState::~EditorState()
	{
		delete this->editor_;
	}

	void EditorState::handleInput(const float &dt)
	{
		if(!paused_)
			editor_->handleInput(util::mouse::mousePositions::mousePosGrid, dt);
	}

	void EditorState::handleEvents(sf::Event &e)
	{
		if (!paused_)
			editor_->handleEvents(e);
		else
			pauseMenu_->handleEvents(e);

		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			if (e.key.code == Keyboard::getCurrentKeyBinds().at("BACK"))
			{
				
			}
			else if (e.key.code == sf::Keyboard::Escape)
			{
				paused_ == true ? paused_ = false : paused_ = true; //if paused is true unpause, else pause
			}
		}
		break;

		}
	}

	void EditorState::update(sf::RenderTarget &target)
	{
		if(!paused_)
			editor_->update(target, util::mouse::mousePositions::mousePosGrid, util::mouse::mousePositions::mousePosView);
		else
		{
			updateGui();
		}

		util::mouse::mousePositions::update();
		util::mouse::mousePositions::updateMouseGridPosition(editor_->getMapTileDimension());
	}

	void EditorState::draw(sf::RenderTarget &target)
	{
		if (!paused_)
			editor_->draw(target);
		else
			drawGui(target);

		util::mouse::mousePositions::draw();
	}

	void EditorState::drawGui(sf::RenderTarget &target)
	{
		target.draw(pauseMenuContainer_);
		pauseMenu_->draw(target);
	}

	void EditorState::updateGui()
	{
		if (paused_)
			pauseMenu_->update();
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
		pauseMenuContainer_.setFillColor(sf::Color(70, 70, 70, 80));
		pauseMenuContainer_.setSize(sf::Vector2f(Engine::getWindow().getSize().x / 3.0f, Engine::getWindow().getSize().y / 1.2f));
		pauseMenuContainer_.setOrigin(sf::Vector2f(pauseMenuContainer_.getGlobalBounds().left + pauseMenuContainer_.getGlobalBounds().width / 2.0f,
			pauseMenuContainer_.getGlobalBounds().top + pauseMenuContainer_.getGlobalBounds().height / 2.0f));
		pauseMenuContainer_.setPosition(Engine::getWindow().getSize().x / 2.0f, Engine::getWindow().getSize().y / 2.0f);

		std::string menuOptions[3] = { "Save Map", "Load Map", "Quit" };
		pauseMenu_ = new gui::StackMenu(sf::Vector2f(pauseMenuContainer_.getPosition().x, pauseMenuContainer_.getPosition().y - gui::getButtonSize(gui::Size::medium).y - 60.0f),
			menuOptions, gui::Size::medium, 3);

		pauseMenu_->setButtonFunction(std::string("Save Map"), [&]() {
			editor_->saveLevel(std::string("res/Maps/Test.txt"), ResourceManager::getTexturePath("dungeon"));
		});

		pauseMenu_->setButtonFunction(std::string("Load Map"), [&]() {
			editor_->loadLevel(std::string("res/Maps/Pacman.txt"));
		});

		pauseMenu_->setButtonFunction(std::string("Quit"), [&]() {
			_game->changeState<MenuState>(*_game);
		});
	}
}
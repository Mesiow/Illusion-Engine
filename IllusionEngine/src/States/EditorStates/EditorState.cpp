#include "../../pcHeaders.h"
#include "EditorState.h"
#include "../../Game.h"
#include "../MenuState.h"

namespace Illusion
{
	EditorState::EditorState(Game &game, sf::Texture &sheet, int mapWidth, int mapHeight, int tileDim)
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
			editor_->handleInput(_mousePosGrid, dt);
	}

	void EditorState::handleEvents(sf::Event &e)
	{
		if(!paused_)
			editor_->handleEvents(e);

		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			if (e.key.code == Keyboard::getCurrentKeyBinds().at("BACK"))
			{
				_game->changeState<MenuState>(*_game);
			}
			else if (e.key.code == sf::Keyboard::Escape)
			{
				if (paused_)
					paused_ = false;
				else
					paused_ = true;
			}
		}
		break;

		}
	}

	void EditorState::update(sf::RenderTarget &target)
	{
		if(!paused_)
			editor_->update(target, _mousePosGrid, _mousePosView);
		else
		{
			updateGui();
		}

		updateMousePositions();

		updateMouseGridPosition(editor_->getMapTileDimension());
	}

	void EditorState::draw(sf::RenderTarget &target)
	{
		if (!paused_)
			editor_->draw(target);
		else
			drawGui(target);

		showMouseCoordinates();
	}

	void EditorState::drawGui(sf::RenderTarget &target)
	{
		target.draw(pauseMenuContainer_);
	}

	void EditorState::updateGui()
	{
		//pauseMenu_->update();
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
		pauseMenuContainer_.setSize(sf::Vector2f(Game::getWindow().getSize().x / 3, Game::getWindow().getSize().y / 1.2));
		pauseMenuContainer_.setOrigin(sf::Vector2f(pauseMenuContainer_.getGlobalBounds().left + pauseMenuContainer_.getGlobalBounds().width / 2.0f,
			pauseMenuContainer_.getGlobalBounds().top + pauseMenuContainer_.getGlobalBounds().height / 2.0f));
		pauseMenuContainer_.setPosition(Game::getWindow().getSize().x / 2.0f, Game::getWindow().getSize().y / 2.0f);
	}
}
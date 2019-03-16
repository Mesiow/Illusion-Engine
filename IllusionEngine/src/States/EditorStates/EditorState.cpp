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

		editor_ = new LevelEditor(sheet, mapWidth, mapHeight, tileDim);
	}

	EditorState::~EditorState()
	{
		delete this->editor_;
	}

	void EditorState::handleInput(const float &dt)
	{
		editor_->handleInput(_mousePosGrid, dt);
	}

	void EditorState::handleEvents(sf::Event &e)
	{
		editor_->handleEvents(e);
		switch (e.type)
		{
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

	void EditorState::update(sf::RenderTarget &target)
	{
		editor_->update(target, _mousePosGrid, _mousePosView);

		updateMousePositions();

		updateMouseGridPosition(editor_->getMapTileDimension());
	}

	void EditorState::draw(sf::RenderTarget &target)
	{
		editor_->draw(target);

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
}
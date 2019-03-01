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
		editor_ = new LevelEditor(ResourceManager::getTexture("dungeon"),  32);
	}

	EditorState::~EditorState()
	{
		delete this->editor_;
	}

	void EditorState::handleInput()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			editor_->addTile(_mousePosView, sf::IntRect(32 * 6, 32 * 8, 32, 32));
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
		tileSelectionContainer_->handleEvents(e);
		switch (e.type)
		{
		case sf::Event::MouseButtonReleased:
		{
			if (e.mouseButton.button == sf::Mouse::Right)
			{
				editor_->deleteTile(_mousePosView);
			}
		}
		}
		/*case sf::Event::KeyPressed:
		{
		 if (e.key.code == Keyboard::getCurrentKeyBinds().at("BACK"))
			{
				_game->changeState<MenuState>(*_game);
		    }
		}
		break;*/

	}

	void EditorState::update(float &dt)
	{
		tileSelectionContainer_->update(dt);
	}

	void EditorState::update(sf::RenderTarget &target)
	{
		editor_->update(target);

		updateMousePositions();
		updateGui();
	}

	void EditorState::draw(sf::RenderTarget & target)
	{
		showMouseCoordinates();
		editor_->drawMap(target);

		tileSelectionContainer_->draw(target);
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
		tileSelectionContainer_ = new gui::PopUpContainer(
			sf::Vector2f(Game::getWindow().getPosition().x, Game::getWindow().getPosition().y),
			sf::Vector2f(32, Game::getWindow().getSize().y / 1.2),
			sf::Color::Transparent, sf::Color(195, 195, 195, 190));
	}

	void EditorState::updateGui()
	{
		
	}
}
#include "EditorState.h"
#include "../Game.h"
#include "MenuState.h"

namespace Illusion
{
	EditorState::EditorState(Game &game)
		:State(game)
	{
	    initKeyBinds();
		editor_ = new LevelEditor(ResourceManager::getTexture("dungeon"),  32);
	}

	EditorState::~EditorState()
	{
		delete this->editor_;
	}

	void EditorState::handleInput()
	{
		
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
		switch (e.type)
		{
		case sf::Event::MouseButtonReleased:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				editor_->addTile(_mousePosView, sf::IntRect(0, 0, 32, 32));
			}
			else if (e.mouseButton.button == sf::Mouse::Right)
			{
				
			}
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

	void EditorState::update(sf::RenderTarget &target)
	{
		editor_->update(target);

		updateMousePositions();
		updateMouseGridPositions();
		updateGui();
	}

	void EditorState::draw(sf::RenderTarget & target)
	{
		editor_->drawTiles(target);
	}

	void EditorState::initKeyBinds()
	{
	//		std::fstream file("../res/Input/editor_state_key_binds.ini");

	//		if (!file.is_open())
	//			throw("File failed to open key binds");

	//		keyMapBinds map;

	//		std::string action;
	//		std::string key;

	//		while (!file.eof())
	//		{
	//			file >> action >> key;
	//			map[action] = Keyboard::getSupportedKeys().at(key); //map action to supported key at location key in supported key map
	//		}

	//		file.close();

	//		Keyboard::addKeyBinds(map);
	//		Keyboard::printBoundKeys();
	}

	void EditorState::updateMouseGridPositions()
	{
		//std::cout << "Grid Pos: " << _mousePosGrid.x << ", " << _mousePosGrid.y << "        "<<
		std::cout<< "Mouse view Pos: " << _mousePosView.x << ", " << _mousePosView.y <<  "         "
		"Mouse window Pos: " << _mousePosWindow.x << ", " << _mousePosWindow.y << "     "
		"Mouse screen Pos: " << _mousePosScreen.x << ", " << _mousePosScreen.y << std::endl;
	}

	void EditorState::updateGui()
	{
		
	}
}
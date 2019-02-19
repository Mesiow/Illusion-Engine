#include "MenuState.h"
#include "../Game.h"
#include "EditorState.h"
#include "Settings.h"
#include "PlayingState.h"
#include <sstream>

namespace Illusion
{

	MenuState::MenuState(Game &game)
		:State(game)
	{
		font_ = nullptr;
		initKeyBinds();
	}

	MenuState::~MenuState()
	{
		
	}

	void MenuState::handleEvents(sf::Event &e)
	{
		
	}

	void MenuState::update(float &dt)
	{
		updateMousePositions();
		updateGui();
	}

	void MenuState::draw(sf::RenderTarget &target)
	{

		//DELETE LATER
		sf::Text text;
		text.setFillColor(sf::Color::White);
		text.setFont(*font_);
		text.setCharacterSize(15);
		text.setPosition(_mousePosView.x, _mousePosView.y - 50);

		std::stringstream ss;
		ss << _mousePosView.x << ", " << _mousePosView.y;
		text.setString(ss.str());

		target.draw(text);
	}

	void MenuState::updateGui()
	{
		
	}

	void MenuState::initKeyBinds()
	{
		//std::fstream file("../res/Input/game_key_binds.ini");

		//if (!file.is_open())
		//	throw("File failed to open key binds");

		//keyMapBinds map;

		//std::string action;
		//std::string key;

		//while (!file.eof())
		//{
		//	file >> action >> key;
		//	map[action] = Keyboard::getSupportedKeys().at(key); //map action to supported key at location key in supported key map
		//}

		//file.close();

		//Keyboard::addKeyBinds(map);
		//Keyboard::printBoundKeys();

	}
}
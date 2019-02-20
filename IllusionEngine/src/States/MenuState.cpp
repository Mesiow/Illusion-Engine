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
		initGui();
	}

	MenuState::~MenuState()
	{
		
	}

	void MenuState::handleEvents(sf::Event &e)
	{
		button->handleEvents(e);
	}

	void MenuState::update(float &dt)
	{
		updateMousePositions();
		updateGui();
	}

	void MenuState::draw(sf::RenderTarget &target)
	{

		button->draw(target);

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
		button->update();
	}

	void MenuState::initGui()
	{
		button = new gui::Button(sf::Vector2f(400, 200), gui::Size::small, 
			sf::Color(70, 70, 70, 100), 
			sf::Color(90, 90, 90, 100), 
			sf::Color(110, 110, 110, 150));

		button->setFunction([&]() {										  
		std::cout << "button clicked :D" << std::endl;				   
		});
	}

	void MenuState::initKeyBinds()
	{
		std::fstream file("res/Input/game_key_binds.ini");

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
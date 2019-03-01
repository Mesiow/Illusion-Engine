#include "../pcHeaders.h"
#include "MenuState.h"
#include "../Game.h"
#include "EditorState.h"
#include "Settings.h"
#include "PlayingState.h"

namespace Illusion
{

	MenuState::MenuState(Game &game)
		:State(game)
	{
		initKeyBinds();
		initGui();
	}

	MenuState::~MenuState()
	{
		delete menu;
	}

	void MenuState::handleEvents(sf::Event &e)
	{
		menu->handleEvents(e);
	}

	void MenuState::update(float &dt)
	{
		updateMousePositions();
		updateGui();
	}

	void MenuState::draw(sf::RenderTarget &target)
	{
		showMouseCoordinates();

		menu->draw(target);
	}

	void MenuState::updateGui()
	{
		menu->update();
	}

	void MenuState::initGui()
	{
		std::string names[4] = { "Start","Editor", "Settings", "Exit" };
		menu = new gui::StackMenu(sf::Vector2f(400, 200), names, gui::Size::small, 4);

		menu->setButtonFunction("Start", [&]() {
			_game->pushState<PlayingState>(*_game);
		});

		menu->setButtonFunction("Editor", [&]() {
			_game->pushState<EditorState>(*_game);
		});

		menu->setButtonFunction("Settings", [&]() {
			_game->pushState<Settings>(*_game);
		});

		menu->setButtonFunction("Exit", [&]() {
			_game->exit();
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
#include "pcHeaders.h"
#include "Game.h"
#include "States/SplashState.h"
#include "Utils/Keyboard.h"

namespace Illusion
{
	sf::RenderWindow *Game::window_ = nullptr;

	Game::Game()
		:fps()
	{
		initSupportedKeys();
		initWindow();
	}

	Game::~Game()
	{
		if (this->window_ != nullptr)
			delete this->window_;
	}


	void Game::initWindow()
	{
		std::fstream windowFile("res/Config/window_setup.ini");

		if (!windowFile.is_open())
			throw("ERROR: window_setup.ini failed to open");

		int width, height;
		std::string title;
		bool fullScreen;

		windowFile >> width; //read data from file into these variables
		windowFile >> height;
		windowFile >> title;
		windowFile >> fullScreen;

		windowFile.close();

		wData_.width = width; //save data in window struct
		wData_.height = height;
		wData_.title = title;
		wData_.fullScreen = fullScreen;

		int fullScreenFlag = 0;
		if (fullScreen)
			fullScreenFlag = sf::Style::Fullscreen;

		window_ = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default | fullScreenFlag);
		window_->setFramerateLimit(FPS_LIMIT);

		pushState<SplashState>(*this); //push the splash state
	}

	void Game::initSupportedKeys()
	{
		std::fstream file("res/Input/supported_keys.ini");

		if (!file.is_open())
			throw("File failed to open supported keys");

		supported_keyMap map;

		std::string key;
		int code;

		while (!file.eof()) //while the file has not reached the end
		{
			file >> key >> code;
			map[key] = code;
		}
		file.close();

		Keyboard::addSupportedKeys(map);
		Keyboard::printSupportedKeys();
	}

	void Game::run()
	{
		while (window_->isOpen() && !states_.empty())
		{
			updateDt();

			auto &state = getCurrentState();

			sf::Event e;
			pollEvents(e);

			state.handleInput();
			state.handleInput(dt_); //get input

			state.update(*window_);
			state.update(dt_);

			clear();

			state.draw(*window_);

			fps.update(*window_);
			fps.draw(*window_);

			display();

			checkPop(); //check if we are trying to pop a state
		}
	}

	void Game::updateDt()
	{
		//updates delta time(time it takes to update and render one frame)
		dt_ = clock_.restart().asSeconds();
	}

	void Game::pollEvents(sf::Event &e)
	{
		while (window_->pollEvent(e))
		{
			getCurrentState().handleEvents(e);
			switch (e.type)
			{
			case sf::Event::Closed:
				window_->close();

			case sf::Event::KeyPressed:
			{
				if (e.key.code == sf::Keyboard::LAlt)
				{
					if (wData_.fullScreen)//exit fullscreen only if its fullscreen
					{
						window_->create(sf::VideoMode(wData_.width, wData_.height), wData_.title, sf::Style::Default);
						window_->setFramerateLimit(60);
						wData_.fullScreen = false;
					}
				}
			}

			}
		}
	}

	void Game::display()
	{
		window_->display();
	}

	void Game::clear()
	{
		window_->clear();
	}

	void Game::pushState(statePtr newState)
	{
		states_.push_back(std::move(newState));
	}

	void Game::checkPop()
	{
		if (popState_)
		{
			popState_ = false;
			if (exitGame_)
			{
				states_.clear();
				return;
			}
			else if (changeState_)
			{
				changeState_ = false;
				states_.pop_back();
				pushState(std::move(changeStatePtr_));
				return;
			}
			states_.pop_back();

		}
	}

	void Game::pop()
	{
		popState_ = true;
	}

	void Game::exit()
	{
		popState_ = true;
		exitGame_ = true;
	}
}
#include "../pcHeaders.h"
#include "SplashState.h"
#include "MenuState.h"
#include "../Game.h"

namespace Illusion
{
	SplashState::SplashState(Game &game)
		:State(game)
	{
		loadResources();
		initSplashScreen();
	}

	SplashState::~SplashState()
	{
		freeTextures();
	}

	void SplashState::initSplashScreen()
	{
		transitionColor_ = sf::Color::Transparent;
		transition_.setFillColor(transitionColor_);
		transition_.setPosition(0, 0);
		transition_.setSize(sf::Vector2f(Game::getWindow().getSize().x,
			Game::getWindow().getSize().y));


		splashScreen_.setPosition(0, 0);
		splashScreen_.setSize(sf::Vector2f(Game::getWindow().getSize().x,
			Game::getWindow().getSize().y));
		splashScreen_.setTexture(&ResourceManager::getTexture("logo"));
	}

	void SplashState::update(float &dt)
	{
		time_ = clock_.getElapsedTime();
		float elapsed = time_.asSeconds();

		if (elapsed >= transitionTime_) //transition color
		{
			transitionColor_.a+=2; //increment alpha color value
			transition_.setFillColor(transitionColor_);
		}
		if (elapsed > waitTime_) //if the elapsed time is greater than 5 seconds lets go to the menu
		{
			_game->changeState<MenuState>(*_game);
		}

	}

	void SplashState::draw(sf::RenderTarget & target)
	{
		target.draw(splashScreen_);
		target.draw(transition_);
	}

	void SplashState::loadResources()
	{
		//Resource loading would be in the world class or menu state if making a game
		ResourceManager::loadTexture("logo", "res/Assets/splashscreen.png");
		ResourceManager::loadFont("rubik", "res/Fonts/Rubik.ttf");

		ResourceManager::loadTexture("player", "res/Assets/undead_idle_sheet.png");

		ResourceManager::loadTexture("dungeon", "res/Assets/Dungeon_Tileset.png");
	}

	void SplashState::freeTextures()
	{
		if (ResourceManager::freeTexture("logo") != Code::DELETE_SUCCESS)
			throw("logo texture failed to delete");
	}
}
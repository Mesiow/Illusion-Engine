#include "../pcHeaders.h"
#include "PlayingState.h"
#include "../Game.h"
#include "PauseState.h"

namespace Illusion
{
	PlayingState::PlayingState(Game &game)
		:State(game)
	{
		//TEST
		map_ = new TileMap();
		map_->loadMap(std::string("res/Maps/Test.txt"), &ResourceManager::getTexture("dungeon")); //load map test.txt which uses the dungeon texture
		p1_ = new Player(ResourceManager::getTexture("player"), sf::Vector2f(200, 200));
		//
	}

	PlayingState::~PlayingState()
	{
		delete map_;
		delete p1_;
	}

	void PlayingState::handleInput(const float &dt)
	{
		p1_->handleInput(dt);
	}

	void PlayingState::handleEvents(sf::Event &e)
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			if (e.key.code == sf::Keyboard::Escape)
				_game->pushState<PauseState>(*_game); //push the pause state to go into pause mode
		}

		}
	}

	void PlayingState::update(float &dt)
	{
		p1_->update(dt);
	}

	void PlayingState::draw(sf::RenderTarget &target)
	{
		map_->draw(target);
		p1_->draw(target);
	}

	void PlayingState::updateGui()
	{

	}
}
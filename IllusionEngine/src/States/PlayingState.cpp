#include "../pcHeaders.h"
#include "PlayingState.h"
#include "../Engine.h"
#include "PauseState.h"

namespace Illusion
{
	PlayingState::PlayingState(Engine &game)
		:State(game)
	{
		//TEST
		map_ = new TileMap();
		map_->loadMap(std::string("res/Maps/Pacman.txt"), &ResourceManager::getTexture("pac")); //load map test.txt which uses the dungeon texture
		p1_ = new Player(ResourceManager::getTexture("pacman"), sf::Vector2f(200, 200));
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
		map_->checkCollision(p1_);
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
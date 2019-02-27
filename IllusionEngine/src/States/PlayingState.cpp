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
		p1 = new Player(ResourceManager::getTexture("player"), sf::Vector2f(200, 200));
		//
	}

	PlayingState::~PlayingState()
	{

	}

	void PlayingState::handleInput(const float &dt)
	{
		p1->handleInput(dt);
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
		p1->update(dt);
	}

	void PlayingState::draw(sf::RenderTarget &target)
	{
		p1->draw(target);
	}

	void PlayingState::updateGui()
	{

	}
}
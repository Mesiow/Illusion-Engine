#pragma once
#include "../pcHeaders.h"
#include "PauseState.h"
#include "../Game.h"
#include "PlayingState.h"

namespace Illusion
{
	PauseState::PauseState(Game &game)
		:State(game)
	{
		
	}

	PauseState::~PauseState()
	{
	
	}

	void PauseState::handleEvents(sf::Event & e)
	{
		
	}

	void PauseState::handleInput(const float & dt)
	{

	}

	void PauseState::update(float & dt)
	{
		
	}

	void PauseState::draw(sf::RenderTarget &target)
	{
		
	}

	void PauseState::updateGui()
	{

	}
}
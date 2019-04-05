#pragma once
#include "State.h"

namespace Illusion
{
	class PauseState : public State
	{
	public:
		PauseState(Engine &game);
		~PauseState();

		void handleEvents(sf::Event &e)override;
		void handleInput(const float &dt)override;
		void update(float &dt)override;
		void draw(sf::RenderTarget &target)override;

		void updateGui();
	};
}
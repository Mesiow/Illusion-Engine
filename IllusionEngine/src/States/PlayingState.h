#pragma once
#include "State.h"
#include "../Entity/Player.h"
#include "../LevelEditor/TileMap.h"

namespace Illusion
{
	class PauseState;

	class PlayingState : public State
	{
	public:
		PlayingState(Game &game);
		~PlayingState();

	public:
		void handleInput(const float &dt)override;
		void handleEvents(sf::Event &e)override;
		void update(float &dt)override;
		void draw(sf::RenderTarget &target)override;

		void updateGui();

	private:
		Player *p1;
		TileMap *map_;
	};
}
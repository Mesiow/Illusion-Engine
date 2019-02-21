#pragma once
#include "State.h"

namespace Illusion
{
	class EditorState;
	class Settings;
	class PlayingState;

	class MenuState : public State
	{
	public:
		MenuState(Game &game);
		virtual ~MenuState();

	public:
		void handleEvents(sf::Event &e)override;
		void update(float &dt)override;
		void draw(sf::RenderTarget &target)override;

	private:
		void updateGui();
		void initGui();
		void initKeyBinds();

	private:
		gui::Button *button;
		gui::Button *button2;
		sf::Font *font_;
		sf::Text text_;

	};
}
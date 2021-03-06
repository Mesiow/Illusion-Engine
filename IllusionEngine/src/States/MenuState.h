#pragma once
#include "State.h"
#include "../Gui/StackMenu.h"
#include "../Utils/UtilityFunctions.h"

namespace Illusion
{
	class EditorState;
	class Settings;
	class PlayingState;

	class MenuState : public State
	{
	public:
		MenuState(Engine &game);
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
		gui::StackMenu *menu;
		sf::Text text_;

	};
}
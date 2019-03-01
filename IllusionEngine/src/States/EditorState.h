#pragma once
#include "State.h"
#include "../LevelEditor/LevelEditor.h"
#include "../Gui/PopUpContainer.h"

namespace Illusion
{
	class MenuState;
	class EditorState : public State
	{
	public:
		EditorState(Game &game);
		~EditorState();

	public:
		 void handleInput()override;
	     void handleInput(const float &dt)override;
	     void handleEvents(sf::Event &e)override;
		 void update(float &dt)override;
	     void update(sf::RenderTarget &target)override;
	     void draw(sf::RenderTarget &target)override;

		 void initKeyBinds();
		 void initGui();
		 void updateGui();

	private:
		LevelEditor *editor_;
		gui::PopUpContainer *tileSelectionContainer_;
		
	};
}
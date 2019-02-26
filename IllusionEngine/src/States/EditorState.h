#pragma once
#include "State.h"
#include "../LevelEditor/LevelEditor.h"

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
	     void update(sf::RenderTarget &target)override;
	     void draw(sf::RenderTarget &target)override;

		 void initKeyBinds();
		 void updateGui();

	private:
		LevelEditor *editor_;
	};
}
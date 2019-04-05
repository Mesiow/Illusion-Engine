#pragma once
#include "../State.h"
#include "../../LevelEditor/LevelEditor.h"
#include "../../Gui/StackMenu.h"
#include "../../Utils/UtilityFunctions.h"
//Add gui elements giving us info about tilemap size and tile dimension

namespace Illusion
{
	class MenuState;
	class EditorState : public State
	{
	public:
		EditorState(Engine &game, sf::Texture &sheet, int mapWidth, int mapHeight, int tileDim);
		~EditorState();

	public:
	     void handleInput(const float &dt)override;
	     void handleEvents(sf::Event &e)override;
	     void update(sf::RenderTarget &target)override;
	     void draw(sf::RenderTarget &target)override;

		 void drawGui(sf::RenderTarget &target);
		 void updateGui();

		 void initKeyBinds();
		 void initGui();

	private:
		LevelEditor *editor_;

		sf::RectangleShape pauseMenuContainer_;
		gui::StackMenu *pauseMenu_;
		bool paused_;
	};
}
#pragma once
#include "../State.h"
#include "../../LevelEditor/LevelEditor.h"

//TODO: add drop down list to choose TileMap width and height and grid dimensions
//add ability to load texture sheet for tilemap at runtime 

namespace Illusion
{
	class MenuState;
	class EditorState : public State
	{
	public:
		EditorState(Game &game, sf::Texture &sheet, int mapWidth, int mapHeight, int tileDim);
		~EditorState();

	public:
		 void handleInput()override;
	     void handleInput(const float &dt)override;
	     void handleEvents(sf::Event &e)override;
	     void update(sf::RenderTarget &target)override;
	     void draw(sf::RenderTarget &target)override;

		 void initKeyBinds();

	private:
		LevelEditor *editor_;
	};
}
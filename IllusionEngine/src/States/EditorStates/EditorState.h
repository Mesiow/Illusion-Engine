#pragma once
#include "../State.h"
#include "../../LevelEditor/LevelEditor.h"

//Add gui elements giving us info about tilemap size and tile dimension

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
		sf::IntRect textureRect_; //texture rect we have currently selected
	};
}
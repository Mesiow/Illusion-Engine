#pragma once
#include "State.h"
#include "../LevelEditor/LevelEditor.h"
#include "../Gui/PopUpContainer.h"
#include "../Gui/DropDownList.h"

//TODO: add drop down list to choose TileMap width and height and grid dimensions
//add ability to load texture sheet for tilemap at runtime 

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
		 void initText();
		 void updateGui();

	private:
		LevelEditor *editor_;

		std::map<std::string, gui::DropDownList*> options_;

		std::vector<gui::Button> buttons_;
		gui::Button *createButton_;
		gui::Button *backButton_;

		std::vector<sf::Text> optionsTexts_;
		sf::Text mapSizeText_;
		sf::Text tileDimText_;
		sf::Text textureLoadText_;
	};
}